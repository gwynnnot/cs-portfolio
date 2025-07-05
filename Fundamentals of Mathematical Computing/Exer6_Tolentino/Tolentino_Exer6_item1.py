import random

print("")
print("Rock-Paper-Scissors Game")
print("")

print("The rules are as follows:")
print("[1] ROCK VS SCISSORS   --->  Rock smashes the scissors") 
print("[2] SCISSORS VS PAPER  --->  Scissor cuts paper")
print("[3] PAPER VS ROCK      --->  Paper wraps rock")
print("[4] If both players select the same, then it is a tie.")

Actions = ["rock", "paper", "scissors"]

print("Let's play!\n")

while True:
    computer_choice = random.randint(0, 2)
    computer = Actions[computer_choice]

    player = input("Please enter your choice (rock, paper, or scissors): ").lower()  # Convert input to lowercase
    
    if player not in Actions:
            print("Invalid input! Please enter either 'rock', 'paper', or 'scissors'.\n")
            continue
    
    print("Computer's choice:", computer)
    print("")

    if player == "rock":
        if computer == "rock":
            print("You selected rock and the computer selected rock. It's a tie!\nLet's play again.\n")
            continue
        elif computer == "paper":
            print("You selected rock and the computer selected paper. You lose.\n")
        elif computer == "scissors":
            print("You selected rock and the computer selected scissors. You win!\n")
    elif player == "paper":
        if computer == "rock":
            print("You selected paper and the computer selected rock. You win!\n")
        elif computer == "paper":
            print("You selected paper and the computer selected paper. It's a tie!\nLet's play again.\n")
            continue
        elif computer == "scissors":
            print("You selected paper and the computer selected scissors. You lose!\n")
    elif player == "scissors":
        if computer == "rock":
            print("You selected scissors and the computer selected rock. You lose!\n")
        elif computer == "paper":
            print("You selected scissors and the computer selected paper. You win!\n")
        elif computer == "scissors":
            print("You selected scissors and the computer selected scissors. It's a tie!\nLet's play again.\n")
            continue
    
    break