'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 7: Predicting Sign Language using KNN

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import os
import csv
import numpy as np
from collections import Counter


# Load training data from a CSV file
def load_data(path):
    dataset = []

    # Open the CSV file and read each line
    with open(path, mode='r', encoding='utf-8-sig') as file:
        csv_file = csv.reader(file)
        for line in csv_file:
            dataset.append([float(value) for value in line]) 
    return np.array(dataset)

# Minkowski distance between two points
def calculate_minkowski(x, y, p):
    absolute_diff = np.abs(x - y)
    powered_diff = absolute_diff ** p
    distance = np.sum(powered_diff) ** (1 / p) 
    
    # Return minkowski distance
    return distance

# Quick Sort for sorting distances
def quick_sort(arr):
    # Base case for recursion
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[0]  # first element as the pivot
        # Partition array into elements less than or equal to and greater than the pivot
        left = [x for x in arr[1:] if x[0] <= pivot[0]]
        right = [x for x in arr[1:] if x[0] > pivot[0]]
        # Recursively sort and combine
        return quick_sort(left) + [pivot] + quick_sort(right)
        
# To classify a single test point
def classify_point(test_point, training_data, k, p):
    distances = []
    
    for train_points in training_data:
        features = train_points[:-1]    # extract features (all columns except last)
        label = train_points[-1]        # last column is the label/class
        
        # Calculate distance of minkowski
        distance = calculate_minkowski(features, test_point, p)
        distances.append((distance, label))
    
    sorted_distances = quick_sort(distances)
    nearest_neighbors = sorted_distances[:k]
    
    # Count labels of the nearest neighbors
    labels = [neighbor[1] for neighbor in nearest_neighbors]# extract labels from nearest neighbors
    label_count = Counter(labels)  

    # Find the most common label
    most_common_label = label_count.most_common(1)[0][0]    # get the label with the highest count
    return most_common_label  

def classify_test_data(test_data, training_data, k, p):
    predictions = []

    # Process each test point in the loaded test data
    for test_point in test_data:
    # Classify each test point
        predicted_label = classify_point(test_point, training_data, k, p)
        predictions.append(test_point.tolist() + [predicted_label]) # convert to list because it's an np.array
    return predictions


def main():
    os.system('cls')

    # Train_SL Path
    train_csv_path = r"C:\Users\Gwy\Downloads\Exercise 7\train\train_SL.csv"
    training_data = load_data(train_csv_path)

    # Test_SL Path
    test_csv_path = r"C:\Users\Gwy\Downloads\Exercise 7\test\test_SL.csv"
    test_data = load_data(test_csv_path)

    # Ask the user for the values of k and p
    k = int(input("Input k value: "))       # number of nearest neighbors
    p = int(input("Input p value: "))       # minkowski distance parameter
    predictions = classify_test_data(test_data, training_data, k, p)

    # Write the output on output.txt
    with open("output.txt", 'w') as file:
        file.write("K-Nearest Neighbor Output from data/test/test_SL.csv\n")
        file.write(f"k = {k}\t")
        file.write(f"p = {p}\n")
        file.write("\nx00             y00             z00             x01             y01             z01             label\n")
        
        for result in predictions:
            line = " ".join(f"{value:<15}" for value in result)
            file.write(line + "\n")


    # TERMINAL
    print("")
    print("x00             y00              z00            x01             y01             z01             label")

    # Print each result in the table
    for result in predictions:
        print(" ".join(f"{value:<15}" for value in result))

main()