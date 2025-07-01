'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 9: Hidden Markov Models for Predicting Region of Coding DNA

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import os
from tkinter import filedialog


class State:
    def __init__(self, value, state_values):
        self.value = value
        self.first_state_probability = 0
        self.transition_probabilities= {}
        
        for state in state_values:
            self.transition_probabilities[state] = 0

    # Calculate transition probabilities from a given sequence
    def calculate_transition_probabilities(self, sequence, state_counts):
        for prev_state in self.transition_probabilities:
            count = count_followed_by(sequence, prev_state, self.value)
            self.transition_probabilities[prev_state] = (
                count / state_counts[prev_state] if state_counts[prev_state] else 0
            )

# Helper function to construct all possible (measurement, state) pairs
def construct_pair_values(state_values, measurement_values):
    return [(measurement, state) for state in state_values for measurement in measurement_values]

# Helper function to count occurrences where prev_char is followed by next_char in sequence
def count_followed_by(sequence, prev_char, next_char):
    return sum(
        1 for i in range(len(sequence) - 1) if sequence[i] == prev_char and sequence[i + 1] == next_char
    )

# Calculate the probability of a state given a measurement
def calculate_total_probability(state_list, target_state, measurement, iterations, pair_val_dict):
    prev_state_probilities = {state.value: state.first_state_probability for state in state_list}

    for _ in range(iterations):
        next_state_probabilities = {
            state.value: sum(
                state.transition_probabilities[prev_state] * prev_state_probilities[prev_state]
                for prev_state in state.transition_probabilities
            )
            for state in state_list
        }
        prev_state_probilities = next_state_probabilities

    measurement_probability = sum(
        prev_state_probilities[state] * float(pair_val_dict[(measurement, state)])
        for state in prev_state_probilities
    )
    return (
        float(pair_val_dict[(measurement, target_state)])
        * prev_state_probilities[target_state]
        / measurement_probability
    )

# Read and parse the input file
def parse_input_file(file_path):
    try:
        with open(file_path, "r") as file:
            lines = [line.strip() for line in file.readlines()]

        n = int(lines[0])  # Number of input sequences
        sequences = lines[1:n + 1]
        state_values = lines[n + 1].split()
        measurement_values = lines[n + 2].split()

        pair_val_dict = {}
        pair_values = construct_pair_values(state_values, measurement_values)
        pair_data_start = n + 3
        for k, pair in enumerate(pair_values):
            row = (k // len(measurement_values)) + pair_data_start
            col = k % len(measurement_values)
            pair_val_dict[pair] = lines[row].split()[col]

        num_cases = int(lines[pair_data_start + len(state_values)])
        cases_start = pair_data_start + len(state_values) + 1
        cases = [
            tuple(lines[i].split()[::2]) for i in range(cases_start, cases_start + num_cases)
        ]

        return sequences, state_values, measurement_values, pair_val_dict, cases
    except Exception as e:
        print(f"Error reading input file: {e}")
        exit()

# Prompt the user to select an input file
def select_input_file():
    return filedialog.askopenfilename(
        defaultextension=".in", filetypes=[("IN File", "*.in"), ("All Files", "*.*")]
    )

# Process each sequence and write results to the output file
def process_sequences(sequences, state_values, pair_val_dict, cases, output_file):
    with open(output_file, "w") as output:
        for sequence in sequences:
            state_counts = {state: sequence.count(state) for state in state_values}
            state_counts[sequence[-1]] -= 1  # Last state adjustment

            state_list = [State(state, state_values) for state in state_values]
            for state in state_list:
                if state.value == sequence[0]:
                    state.first_state_probability = 1
                state.calculate_transition_probabilities(sequence, state_counts)

            output.write(f"{sequence}\n")
            for case in cases:
                target_state, measurement_case = case[0][0], case[1]
                measurement, iterations = measurement_case[0], int(measurement_case[1:])
                probability = calculate_total_probability(
                    state_list, target_state, measurement, iterations, pair_val_dict
                )
                output.write(f"{case[0]} given {case[1]} = {probability}\n")
            output.write("\n")
    print(f"Results written to {output_file}")


def main():
    file_path = select_input_file()
    if not file_path:
        print("No file selected. Exiting program.")
        return

    sequences, state_values, measurement_values, pair_val_dict, cases = parse_input_file(file_path)
    output_file = "hmm.out"
    process_sequences(sequences, state_values, pair_val_dict, cases, output_file)

main()
