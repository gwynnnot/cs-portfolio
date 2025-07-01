'''
CMSC 170: Introduction to Artificial Intelligence
Pre-Lab Activity 1: The 8-Puzzle Game


MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''
import tkinter as tk
from tkinter import filedialog, messagebox

class Node:
    def __init__(self, state, empty_tile):
        self.state = state
        self.empty_tile = empty_tile # Position of the empty tile (tuple)

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
        self.saved_node = None    # Will store the saved initial state as a Node; will be used when file is imported
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
        
        course_label = tk.Label(header_frame, text="CMSC 170", font=('Helvetica', 14))
        course_label.pack()
        
        # CHANGE TO YOUR NAME
        author_label = tk.Label(header_frame, text="Mary Gwyneth Tolentino", font=('Helvetica', 14))
        author_label.pack()
        
        self.canvas = tk.Canvas(self.root, width=300, height=300, bg='white', borderwidth=0, highlightthickness=0, relief=tk.SOLID)
        self.canvas.pack(side=tk.TOP, padx=(2,0), pady=(2,0))
        self.canvas.bind("<Button-1>", self.click)

        self.import_button = tk.Button(self.root, text="Import Configuration", command=self.import_configuration)
        self.import_button.pack(side=tk.TOP, padx=10, pady=5)

        self.button_frame = tk.Frame(self.root)
        self.button_frame.pack(side=tk.TOP, padx=10, pady=5)

        self.reset_button = tk.Button(self.button_frame, text="Reset", command=self.reset_puzzle)
        self.reset_button.pack(side=tk.LEFT, padx=5)

        self.text_frame = tk.Frame(self.root)
        self.text_frame.pack(side=tk.TOP, fill=tk.BOTH, padx=10, pady=10)

        self.solution_label = tk.Label(self.text_frame, text="Puzzle is Solvable", font=('Helvetica', 14, 'bold'))
        self.solution_label.pack(side=tk.TOP, fill=tk.X, padx=10, pady=5)

        self.scrollbar = tk.Scrollbar(self.text_frame, orient=tk.VERTICAL)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

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





    # -----------------------------------------------------------------------------------------
    # TODO: Function for importing puzzle.in file
    # Notes:
    #   Do not forget to set the values of:
    #       * self.initial_node # data structure to store the initial node of the puzzle
    #       * self.saved_node = # data stucture to store the saved initial state as a Node
    #       These will have the same values since your are importing a new puzzle configuration
    #   Utilize the functions declared above (e.g., im validating the imported file, rendering to GUI, etc.)
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
    # Notes:
    #   * Configure the text in self.solution_label if the puzzle is solvable or not
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
    

# Create and run the app
root = tk.Tk()
app = PuzzleApp(root)
root.mainloop()
