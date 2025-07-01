'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 1: Solving the 8-Puzzle Game using BFS and DFS

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''
import tkinter as tk
from tkinter import filedialog, messagebox
from collections import deque

class Node:
    def __init__(self, state, empty_tile, action=None, parent=None, path_cost=0):
        self.state = state
        self.empty_tile = empty_tile
        self.action = action
        self.parent = parent        #points to previous state, dapat node
        self.path_cost = path_cost  #path_cost of parent + 1

class PuzzleApp:
    def __init__(self, root):
        self.root = root
        self.root.title("8-Puzzle Game")
        self.goal_tiles = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 0]
        ]
        self.initial_node = None  # Will store the initial node of the puzzle
        self.saved_node = None    # Will store the saved initial state as a Node
        self.create_widgets()
        self.initialize_game()

    # -----------------------------------------------------------------------------------------
    # Rendering the elements in the GUI
    # -----------------------------------------------------------------------------------------
    def create_widgets(self):
        header_frame = tk.Frame(self.root)
        header_frame.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)
        
        title_label = tk.Label(header_frame, text="8-Puzzle Game", font=('Helvetica', 20, 'bold'))
        title_label.pack()
        
        course_label = tk.Label(header_frame, text="CMSC 170 GH5L", font=('Helvetica', 14))
        course_label.pack()
        
        # CHANGE TO YOUR NAME
        author_label = tk.Label(header_frame, text="Mary Gwyneth Tolentino", font=('Helvetica', 14))
        author_label.pack()
        
        self.canvas = tk.Canvas(self.root, width=300, height=300, bg='white', borderwidth=0, highlightthickness=0, relief=tk.SOLID)
        self.canvas.pack(side=tk.TOP, padx=(2,0), pady=(2,0))
        self.canvas.bind("<Button-1>", self.click)

        self.import_button = tk.Button(self.root, text="Import Configuration", command=self.import_configuration)
        self.import_button.pack(side=tk.TOP, padx=10, pady=5)

        self.method_var = tk.StringVar(value="BFS")
        self.heuristic_var = tk.StringVar(value="Manhattan Distance")

        self.method_frame = tk.Frame(self.root)
        self.method_frame.pack(side=tk.TOP, padx=10, pady=5)
        
        self.bfs_rb = tk.Radiobutton(self.method_frame, text="BFS", variable=self.method_var, value="BFS")
        self.bfs_rb.pack(side=tk.LEFT)
        self.dfs_rb = tk.Radiobutton(self.method_frame, text="DFS", variable=self.method_var, value="DFS")
        self.dfs_rb.pack(side=tk.LEFT)

        self.button_frame = tk.Frame(self.root)
        self.button_frame.pack(side=tk.TOP, padx=10, pady=5)

        self.solve_button = tk.Button(self.button_frame, text="Solve", command=self.solve_puzzle)
        self.solve_button.pack(side=tk.LEFT, padx=5)

        self.reset_button = tk.Button(self.button_frame, text="Reset", command=self.reset_puzzle)
        self.reset_button.pack(side=tk.LEFT, padx=5)

        self.text_frame = tk.Frame(self.root)
        self.text_frame.pack(side=tk.TOP, fill=tk.BOTH, padx=10, pady=10)

        self.solution_label = tk.Label(self.text_frame, text="Puzzle is Solvable", font=('Helvetica', 14, 'bold'))
        self.solution_label.pack(side=tk.TOP, fill=tk.X, padx=10, pady=5)

        self.scrollbar = tk.Scrollbar(self.text_frame, orient=tk.VERTICAL)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.directions_text = tk.Text(self.text_frame, height=3, width=40, yscrollcommand=self.scrollbar.set, wrap=tk.WORD, font=('Helvetica', 16))
        self.directions_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.scrollbar.config(command=self.directions_text.yview)
        self.directions_text.config(state=tk.DISABLED)

    # -----------------------------------------------------------------------------------------
    # Initializes the game; default initial state is set here
    # -----------------------------------------------------------------------------------------
    def initialize_game(self):
        default_initial_tiles = [
            [2, 3, 0],
            [1, 5, 6],
            [4, 7, 8]
        ]
        self.initial_node = Node(default_initial_tiles, self.find_empty_spot(default_initial_tiles))
        self.saved_node = Node([row[:] for row in default_initial_tiles], self.find_empty_spot(default_initial_tiles))
        self.load_tiles(self.initial_node.state)
        self.check_solvability(self.initial_node.state)

    # -----------------------------------------------------------------------------------------
    # Finding the empty tile
    # @params:
    #	tiles - puzzle state
    # -----------------------------------------------------------------------------------------
    def find_empty_spot(self, tiles):
        return next((i, j) for i, row in enumerate(tiles) for j, tile in enumerate(row) if tile == 0)

    # -----------------------------------------------------------------------------------------
    # Loads the current state by drawing the elements in the GUI
    # @params:
    #	tiles - puzzle state
    # -----------------------------------------------------------------------------------------
    def load_tiles(self, tiles):
        self.draw_tiles(tiles)

    # -----------------------------------------------------------------------------------------
    # Updates the game board given the current state
    # @params:
    #	tiles - puzzle state
    # -----------------------------------------------------------------------------------------
    def draw_tiles(self, tiles):
        self.canvas.delete("all")
        for i, row in enumerate(tiles):
            for j, tile in enumerate(row):
                if tile != 0:
                    x0, y0 = j * 100, i * 100
                    x1, y1 = x0 + 100, y0 + 100
                    self.canvas.create_rectangle(x0, y0, x1, y1, fill='#3566d5', activefill="#2d55b1", width=2)
                    self.canvas.create_text((x0 + 50, y0 + 50), text=str(tile), font=('Helvetica', 24), fill='white')

    # -----------------------------------------------------------------------------------------
    # Performs swapping of the tiles when an event (click) is detected
    # @params:
    #	event - triggers (e.g., mouse click)
    # -----------------------------------------------------------------------------------------
    def click(self, event):
        col, row = event.x // 100, event.y // 100
        if self.is_adjacent((row, col), self.initial_node.empty_tile):
            self.swap_tiles(self.initial_node.state, (row, col), self.initial_node.empty_tile)
            self.initial_node.empty_tile = (row, col)
            self.draw_tiles(self.initial_node.state)
            if self.check_victory():
                messagebox.showinfo("8-Puzzle", "Congratulations! You solved the puzzle!")

    # -----------------------------------------------------------------------------------------
    # Checks adjacency to make sure swapping of tile is valid
    # @params:
    #	pos1 - tuple of x,y coordinates of the clicked tile
    #   pos2 - tuple of x,y coordinates of the empty tile
    # -----------------------------------------------------------------------------------------
    def is_adjacent(self, pos1, pos2):
        return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]) == 1

    # -----------------------------------------------------------------------------------------
    # Swaps tiles given the position
    # @params:
    #	tiles - puzzle state
    #	pos1 - tuple of x,y coordinates of the clicked tile
    #   pos2 - tuple of x,y coordinates of the empty tile
    # -----------------------------------------------------------------------------------------
    def swap_tiles(self, tiles, pos1, pos2):
        tiles[pos1[0]][pos1[1]], tiles[pos2[0]][pos2[1]] = tiles[pos2[0]][pos2[1]], tiles[pos1[0]][pos1[1]]

    # -----------------------------------------------------------------------------------------
    # Check if the player has won
    # -----------------------------------------------------------------------------------------
    def check_victory(self):
        return self.initial_node.state == self.goal_tiles
    
    # -----------------------------------------------------------------------------------------
    # Makes sure that the imported file is a valid puzzle configuration
    # @params:
    #	tiles - puzzle state
    # -----------------------------------------------------------------------------------------
    def validate_tiles(self, tiles):
        flattened = [num for row in tiles for num in row]
        return sorted(flattened) == list(range(9))

    # -----------------------------------------------------------------------------------------
    # Resets the puzzle to its initial state
    # -----------------------------------------------------------------------------------------
    def reset_puzzle(self):
        self.initial_node = Node([row[:] for row in self.saved_node.state], self.saved_node.empty_tile)
        self.load_tiles(self.initial_node.state)
        self.check_solvability(self.initial_node.state)
        self.clear_directions()

    # -----------------------------------------------------------------------------------------
    # Clears the directions rendered in the GUI
    # -----------------------------------------------------------------------------------------
    def clear_directions(self):
        self.directions_text.config(state=tk.NORMAL)
        self.directions_text.delete('1.0', tk.END)
        self.directions_text.config(state=tk.DISABLED)

    # -----------------------------------------------------------------------------------------
    # Animation of the given solution
    # @params
    #   solution - list of states from the initial to the goal state
    #   directions - list of actions taken from initial to goal state
    # -----------------------------------------------------------------------------------------
    def animate_solution(self, solution, directions):
        for state, direction in zip(solution, directions):
            self.directions_text.config(state=tk.NORMAL)
            self.directions_text.insert(tk.END, direction + " ")
            self.directions_text.config(state=tk.DISABLED)
            self.draw_tiles(state)
            self.root.update()
            self.root.after(500)

    # -----------------------------------------------------------------------------------------
    # Lets the user choose an AI agent and animates the given solution
    # -----------------------------------------------------------------------------------------
    def solve_puzzle(self):
        self.solution_label.config(text="Solving...")
        self.root.update()

        search_method = self.method_var.get()
        solution = None
        directions = []
        path_cost = 0
        explored_count = 0

        if search_method == "BFS":
            solution, directions, path_cost, explored_count = self.bfs_search()
        elif search_method == "DFS":
            solution, directions, path_cost, explored_count = self.dfs_search()

        if solution:
            self.animate_solution(solution, directions)
            self.solution_label.config(text=f"Path Cost: {path_cost}   |   Explored States: {explored_count}")
        else:
            messagebox.showinfo("No Solution", "No solution was found using the selected method.")
            self.solution_label.config(text=f"No solution")




    # -----------------------------------------------------------------------------------------
    # TODO: Function for importing puzzle.in file
    # >>> Insert the function you made in the pre-lab activity 1
    # -----------------------------------------------------------------------------------------
    def import_configuration(self):
        # Open a file dialog to select the puzzle configuration file
        file_path = filedialog.askopenfilename(
            title="Open Puzzle Configuration", 
            filetypes=(("Text files", "*.in"), ("All files", "*.*"))
        )
        
        if file_path:
            try:
                # Read the file and load the tiles
                tiles = []
                with open(file_path, 'r') as file:
                    for line in file.readlines():
                        row = list(map(int, line.split()))  # Split the line into numbers and map them to integers
                        tiles.append(row)
                
                # Validate the imported tiles
                if self.validate_tiles(tiles):
                    # If valid, set the initial node and save the state
                    self.initial_node = Node(tiles, self.find_empty_spot(tiles))
                    self.saved_node = Node([row[:] for row in tiles], self.find_empty_spot(tiles))
                    self.load_tiles(self.initial_node.state)        # Loads the tiles into the GUI
                    self.check_solvability(self.initial_node.state) # Checks solvability
                else:
                    messagebox.showerror("Invalid Configuration", "The imported puzzle configuration is invalid.")
            except Exception as e:
                messagebox.showerror("Error", f"An error occurred while importing the configuration: {e}")


    # -----------------------------------------------------------------------------------------
    # TODO: Checks the number of inversion; whether the tile is solvable or not
    # @params:
    #	tiles - puzzle state
    # >>> Insert the function you made in the pre-lab activity 1
    # -----------------------------------------------------------------------------------------
    def check_solvability(self, tiles):
        temp = []
        inversion_num = 0

        # Transfer tiles values to a single array
        for row in range(3):                        
            for col in range(3):
                # Ignore the empty tile 
                if tiles[row][col] != 0:
                    temp.append(tiles[row][col])
        
        # Count inversions
        for i in range(len(temp)):
            for j in range(i + 1, len(temp)):
                if temp[i] > temp[j]:
                    inversion_num += 1

        # Puzzle is solvable if the number of inversions is even
        if inversion_num % 2 == 0:
            self.solution_label.config(text="Puzzle is Solvable", fg="green")
        else:
            self.solution_label.config(text="Puzzle is Not Solvable", fg="red")


    # -----------------------------------------------------------------------------------------
    # TODO: Applies all legal actions and gets the resulting states
    # @params
    #   node - data structure of a state
    # @return
    #   neighbors - a list of nodes (data structures) of resulting states given a legal action (move)
    # Note:
    #   To match the test cases, follow the U D R L sequence of action search
    # -----------------------------------------------------------------------------------------
    def get_neighbors(self, node): #resulting state after previous action
    # action, current state, result

        neighbors = []
        row, col = node.empty_tile

        moves = {
            "U": (row -1, col),
            "D": (row +1, col),
            "R": (row, col +1),
            "L": (row, col -1)
        }

        # Apply all legal actions
        for action, (new_row, new_col) in moves.items():
            if 0 <=new_row < 3 and 0 <= new_col < 3:
                new_state = [row[:] for row in node.state]
                new_state[row][col], new_state[new_row][new_col] = new_state[new_row][new_col], new_state[row][col] # swap tiles
                neighbors.append((Node(new_state, (new_row, new_col), action, node, node.path_cost +1), action))    # new node with updated state and action

        return neighbors

    # -----------------------------------------------------------------------------------------
    # Returns the path (a list of states), directions (a list of actions), and path cost
    # @params:
    #	node - data structure representing a state
    # @return
    #   * path - an array of states from the given node up to its predecessors
    #   * directions - an array of actions taken from the current state up to its predecessors
    #   * path_cost - distance from the initial state to the current state
    # -----------------------------------------------------------------------------------------
    def get_path(self, node):

        path = []       # List of 2d arrays [[1,2],[3,4]]
        directions = [] # List of actions to reach the goal state
        path_cost = node.path_cost

        # Traverse back from current node to its initial 
        while node.parent: 
            path.append(node.state)
            directions.append(node.action)
            node = node.parent
        path.append(node.state)    
        path.reverse()
        directions.reverse()   # reverse to go from initial to goal state
        return path, directions, path_cost

    # -----------------------------------------------------------------------------------------
    # TODO: Implements Breadth-First Search
    # @return
    #   * solution - an array of the states from initial to goal state
    #   * directions - array of actions taken from initial to goal state
    #   * path_cost - distance from initial to goal
    #   * explored_count - number of states put in explored (closed) list
    # -----------------------------------------------------------------------------------------
    def bfs_search(self):
        frontier = deque([self.initial_node])   
        explored = set()
        # explored_count = 0

        while frontier:
            node = frontier.popleft()

            # Check if the current state is the goal state
            if node.state == self.goal_tiles:
                solution, directions, path_cost = self.get_path(node)
                # explored_count += 1     # count the goal state as explored
                explored_count = len(explored) + 1
                return solution, directions, path_cost, explored_count
            
            # Mark the current state as explored
            explored.add(tuple(map(tuple, node.state))) # add node's state to the explored set    
            # explored_count += 1         # increment the explored counter
            explored_count = len(explored) + 1

            for neighbor, action in self.get_neighbors(node):
                # Add the neighbor to the frontier if it's not explored yet
                if tuple(map(tuple, neighbor.state)) not in explored and neighbor not in frontier:
                    frontier.append(neighbor)

        explored_count = len(explored)
        return None, [], 0, explored_count

    # -----------------------------------------------------------------------------------------
    # TODO: Implements Depth-First Search
    # @return
    #   * solution - an array of the states from initial to goal state
    #   * directions - array of actions taken from initial to goal state
    #   * path_cost - distance from initial to goal
    #   * explored_count - number of states put in explored (closed) list
    # -----------------------------------------------------------------------------------------
    def dfs_search(self):
        frontier = [self.initial_node]
        explored = set()
        # explored_count = 0

        while frontier:
            node = frontier.pop()  # LIFO for DFS

            # Check if the current state is the goal state
            if node.state == self.goal_tiles:
                solution, directions, path_cost = self.get_path(node)
                # explored_count += 1
                explored_count = len(explored) + 1
                return solution, directions, path_cost, explored_count
            
            # Mark the current as explored
            explored.add(tuple(map(tuple, node.state))) 
            # explored_count += 1
            explored_count = len(explored) + 1
            
            for neighbor, action in self.get_neighbors(node):
                # Add the neighbor to the frontier if it's not explored yet
                if tuple(map(tuple, neighbor.state)) not in explored and neighbor not in frontier:
                    frontier.append(neighbor)

        explored_count = len(explored)
        return None, [], 0, explored_count
            # solution
            # directions
            # path_cost 
            # explored_count


# Create and run the app
root = tk.Tk()
app = PuzzleApp(root)
root.mainloop()
