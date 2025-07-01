'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 3: Creating Bag-of-Words model

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import os 
import re
import unicodedata
import tkinter as tk
from tkinter import filedialog, ttk     # https://www.pythontutorial.net/tkinter/tkinter-treeview/#:~:text=Introduction%20to%20the%20Tkinter%20Treeview,has%20one%20or%20more%20columns.
from collections import Counter         # https://www.geeksforgeeks.org/python-counter-update-method/
# GUI
class B_O_W_App:

    # what's inside?
    def __init__(self, root):
            self.root = root
            self.root.title("Bag-of-Words")
            self.root.geometry("400x500")
            self.root.config(bg="lightblue")

            # create and display widgets
            self.create_widgets()

    # render the elements in the GUI
    def create_widgets(self):
        header_frame = tk.Frame(self.root, bg='lightblue')
        header_frame.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)
        
        title_label = tk.Label(header_frame, text="Bag of Words",  bg="lightblue", font=('Helvetica', 20, 'bold'))
        title_label.pack()
        
        course_label = tk.Label(header_frame, text="CMSC 170 GH5L",  bg="lightblue", font=('Helvetica', 14))
        course_label.pack()
        
        # CHANGE TO YOUR NAME
        author_label = tk.Label(header_frame, text="Mary Gwyneth Tolentino",  bg="lightblue", font=('Helvetica', 14))
        author_label.pack()

        self.import_button = tk.Button(self.root, text="Select Folder", command=self.select_folder)
        self.import_button.pack(side=tk.TOP, padx=10, pady=5)

        self.total_words = tk.StringVar(value="Total Word Count: ")
        self.dictionary_size = tk.StringVar(value="Dictionary Size: ")

        dict_size_label = tk.Label(self.root, textvariable=self.dictionary_size, bg="lightblue", font=("Arial", 12))
        dict_size_label.pack(pady=5)
        total_words_label = tk.Label(self.root, textvariable=self.total_words, bg="lightblue", font=("Arial", 12))
        total_words_label.pack(pady=5)

        table_frame = tk.Frame(self.root)
        table_frame.pack(pady=10)

        self.table = ttk.Treeview(table_frame, columns=("Word", "Frequency"), show="headings", height=10)
        self.table.heading("Word", text="Word")
        self.table.heading("Frequency", text="Frequency")
        self.table.pack(side="left")

        # https://stackoverflow.com/questions/41877848/python-treeview-scrollbar
        scrollbar = ttk.Scrollbar(table_frame, orient="vertical", command=self.table.yview)
        self.table.configure(yscrollcommand=scrollbar.set)
        scrollbar.pack(side="right", fill="y")
        
    def clean(self, message):
        # https://stackoverflow.com/questions/517923/what-is-the-best-way-to-remove-accents-normalize-in-a-python-unicode-string/517974#517974
        text = unicodedata.normalize('NFKD', message)   # Accented characters should be removed (ñ, ü).
        text = text.encode('ascii', 'ignore')
        text = text.decode("ascii")
        # print("Naked: ", text)
        # for i in range(len(message)):
        #     message[i] = re.sub("[^a-zA-Z0-9]", '', message[i])

        # remove non-alphabetic characters
        cleaned = re.sub(r'[^a-zA-Z\s]', '', text).lower()
        words = cleaned.split()
        # print("Cleaned Words: ", words)

        return words

    # Read all files in the selected folder
    def read_folder(self, folder_path):
        b_o_w = Counter()
        total_words = 0

        for filename in os.listdir(folder_path):
            file_path = os.path.join(folder_path, filename)
            if os.path.isfile(file_path):
                with open(file_path, 'r', encoding='latin-1') as file:
                    message = file.read()
                    words = self.clean(message)

                    # update bag of words with the current file's words
                    b_o_w.update(words)         
                    total_words += len(words)
        
        return b_o_w, total_words

    # Select a folder that contains files with messages
    def select_folder(self):
        folder_path = filedialog.askdirectory()
        if folder_path:
            b_o_w, total_words = self.read_folder(folder_path)
            self.dictionary_size.set(f"Dictionary Size: {len(b_o_w)}")
            self.total_words.set(f"Total Word Count: {total_words}")

            # clear previous table entries
            for row in self.table.get_children():
                self.table.delete(row)
            
            # populate table with words and their frequencies
            for word, freq in sorted(b_o_w.items()):
                self.table.insert("", tk.END, values=(word, freq))

            self.write_output(b_o_w, total_words)

    def write_output(self, b_o_w, total_words):
        with open("bow.out", "w", encoding="utf-8") as file:
            file.write(f"Total Word Count: {total_words}\n")
            file.write(f"Dictionary Size: {len(b_o_w)}\n")
            for word, freq in sorted(b_o_w.items()):
                # Output should be sorted alphabetically
                file.write(f"{word} {freq}\n")
             


        

        

# Read all files in the selected folder
# Each input file in the folder has one message (can be multiple sentences)
# Read files in Latin-1 encoding
# Create bag-of-words
# Clean the messages by removing all non-alphanumeric characters. For example,
# “can’t” becomes “cant”.
# Use whitespace as the delimiter.
# Accented characters should be removed (ñ, ü).


# Create and run the app
root = tk.Tk()
app = B_O_W_App(root)
root.mainloop()









