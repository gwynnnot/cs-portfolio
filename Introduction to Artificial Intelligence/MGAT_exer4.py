'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 4: Spam Filtering using Naïve Bayes Classifier

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import os                            
import re                            
import tkinter as tk                
from tkinter import filedialog, ttk, messagebox     
from decimal import Decimal, getcontext  

class B_O_W_App:

    # What's inside?
    def __init__(self, root):
            self.root = root
            self.root.title("Bag-of-Words")
            self.root.geometry("400x500")
            self.root.config(bg="lightblue")

            # Initialize data structures for counting words
            self.ham_dict = dict()                    
            self.spam_dict = dict()                  
            self.ham_bow = []                         
            self.spam_bow = []                        
            # for storing the list of files
            self.ham_file_list = []                  
            self.spam_file_list = []                  

            # Create and display widgets
            self.create_widgets()

    # Render the elements in the GUI
    def create_widgets(self):
        # create the title label
        title_label = tk.Label(self.root, text="Naïve Bayes Classifier", font=("Arial", 18, "bold"), bg="lightblue")
        title_label.grid(row=0, column=0, columnspan=4, pady=10) 

        # subtitle label
        subtitle_label = tk.Label(self.root, text="CMSC 170 GH5L\nMary Gwyneth Tolentino", font=("Arial", 12), bg="lightblue")
        subtitle_label.grid(row=1, column=0, columnspan=4, pady=5)

        # button to select spam and ham folders
        select_folder_btn = tk.Button(self.root, text="Select Folders", command=self.select_folders)
        select_folder_btn.grid(row=2, column=0, pady=10)

        # button to select spam and ham folders
        classify_btn = tk.Button(self.root, text="CLASSIFY", command=self.classify_messages)
        classify_btn.grid(row=2, column=1, pady=10)

        # label for the smoothing factor input
        smoothing_label = tk.Label(self.root, text="Smoothing Factor, k:", bg="lightblue", font=("Arial", 12))
        smoothing_label.grid(row=2, column=2, pady=5)
        self.smoothing_entry = tk.Entry(self.root)
        self.smoothing_entry.grid(row=2, column=3, pady=5)

        # label for displaying spam information
        spam_label = tk.Label(self.root, text="SPAM", bg="lightblue", font=("Arial", 12, "bold"))
        spam_label.grid(row=3, column=0, pady=5)

        self.spam_dict_size = tk.StringVar(value="Dictionary Size: ")
        self.spam_total_words = tk.StringVar(value="Total Word Count: ") 
        tk.Label(self.root, textvariable=self.spam_dict_size, bg="lightblue", font=("Arial", 12)).grid(row=4, column=0, pady=5) 
        tk.Label(self.root, textvariable=self.spam_total_words, bg="lightblue", font=("Arial", 12)).grid(row=5, column=0, pady=5) 

        # table for displaying spam word frequencies
        spam_table_frame = tk.Frame(self.root) 
        spam_table_frame.grid(row=6, column=0, padx=10, pady=5) 
        self.spam_table = ttk.Treeview(spam_table_frame, columns=("Word", "Frequency"), show="headings", height=10)
        self.spam_table.heading("Word", text="Word")  
        self.spam_table.heading("Frequency", text="Frequency")  
        self.spam_table.pack(side="left") 
        scrollbar_spam = ttk.Scrollbar(spam_table_frame, orient="vertical", command=self.spam_table.yview) 
        self.spam_table.configure(yscrollcommand=scrollbar_spam.set) 
        scrollbar_spam.pack(side="right", fill="y") 

        # label for displaying ham information
        ham_label = tk.Label(self.root, text="HAM", bg="lightblue", font=("Arial", 12, "bold"))
        ham_label.grid(row=3, column=1, pady=5)

        self.ham_dict_size = tk.StringVar(value="Dictionary Size: ")
        self.ham_total_words = tk.StringVar(value="Total Word Count: ")
        tk.Label(self.root, textvariable=self.ham_dict_size, bg="lightblue", font=("Arial", 12)).grid(row=4, column=1, pady=5)
        tk.Label(self.root, textvariable=self.ham_total_words, bg="lightblue", font=("Arial", 12)).grid(row=5, column=1, pady=5)

        # table for displaying ham word frequencies
        ham_table_frame = tk.Frame(self.root)
        ham_table_frame.grid(row=6, column=1, padx=10, pady=5)
        self.ham_table = ttk.Treeview(ham_table_frame, columns=("Word", "Frequency"), show="headings", height=10)
        self.ham_table.heading("Word", text="Word")
        self.ham_table.heading("Frequency", text="Frequency")
        self.ham_table.pack(side="left")
        scrollbar_ham = ttk.Scrollbar(ham_table_frame, orient="vertical", command=self.ham_table.yview)
        self.ham_table.configure(yscrollcommand=scrollbar_ham.set)
        scrollbar_ham.pack(side="right", fill="y")

        # label for the output section
        output_label = tk.Label(self.root, text="OUTPUT", bg="lightblue", font=("Arial", 12, "bold"))
        output_label.grid(row=3, column=2, columnspan=2, padx=10, pady=5)
        
        # self.output_dict_size = tk.StringVar(value="Dictionary Size: ")
        # self.output_total_words = tk.StringVar(value="Total Word Count: ")
        # tk.Label(self.root, textvariable=self.output_dict_size, bg="lightblue", font=("Arial", 12)).grid(row=4, column=1, pady=5)
        # tk.Label(self.root, textvariable=self.output_total_words, bg="lightblue", font=("Arial", 12)).grid(row=5, column=1, pady=5)

        # frame for the output table
        output_frame = tk.Frame(self.root)
        output_frame.grid(row=6, column=2, padx=10, pady=5, columnspan=2)
        self.output_table = ttk.Treeview(output_frame, columns=("Filename", "Class", "P(Spam)"), show="headings", height=10)
        self.output_table.heading("Filename", text="Filename")
        self.output_table.heading("Class", text="Class")
        self.output_table.heading("P(Spam)", text="P(Spam)")
        self.output_table.pack(side="left")
        scrollbar_output = ttk.Scrollbar(output_frame, orient="vertical", command=self.output_table.yview)
        self.output_table.configure(yscrollcommand=scrollbar_output.set)
        scrollbar_output.pack(side="right", fill="y")
        
        self.root.update()
        self.root.geometry('')  # Resize window to fit content


    def select_folders(self):
        for main in range(2):                
            # Loop twice to select "ham" and "spam" directories
            file_path = filedialog.askdirectory(title="Select Spam or Ham Folder") 
            selected_dir = file_path.split("/")[-1] # selected directory name
            selected_dir2 = file_path.split("/")[-2]# parent directory name
            file_list = os.listdir(file_path)      

            b_o_w = []                  # empty list for storing words
            total_words = dict()        # empty dictionary for word frequencies

            for file in file_list:            
                # Loop over each file in the selected directory
                f = open(f"{selected_dir2}/{selected_dir}/{file}", "r", encoding='latin-1')  
                file_content = f.readlines()  # read all lines from the file

                # Loop over each line in the file
                for i in file_content:  
                    messages = i.split()    
                    for word in messages:    
                        # Remove non-alphabetic characters
                        cleaned = re.sub(r'[^a-zA-Z]', "", word)  # to keep only letters

                        if len(cleaned) != 0:               # check if the cleaned word is not empty
                            b_o_w.append(cleaned.lower())   # add the cleaned word in lowercase to b_o_w

            sorted_bag = sorted(b_o_w)  # Sort the list of words alphabetically

            # Loop over each cleaned word in sorted_bag
            for cw in sorted_bag:      
                if cw in total_words:
                    total_words[cw] = total_words[cw] + 1   # increment if the word already exists in total_words
                else:
                    total_words[cw] = 1 #add the word to total_words

            # Check if the selected directory is "ham"
            if selected_dir == "ham":   
                self.ham_dict = total_words.copy()      # copy total_words to ham_dict
                self.ham_dict_size.set(f"Dictionary Size: {len(self.ham_dict)}") # Update dictionary size label

                self.ham_bow = sorted_bag.copy()        # copy sorted_bag to ham_bow
                self.ham_total_words.set(f"Total Word Count: {len(self.ham_bow)}") # Update total words label
                self.ham_file_list = file_list.copy()   # copy file_list to ham_file_list

                # Populate the ham table with word frequencies
                for row in self.ham_table.get_children():
                    self.ham_table.delete(row)          # clear existing entries
                for word, freq in sorted(self.ham_dict.items()): # sort and insert new entries
                    self.ham_table.insert("", tk.END, values=(word, freq))

            # Else if the selected directory is "spam"
            elif selected_dir == "spam":     
                self.spam_dict = total_words.copy()     # copy total_words to spam_dict
                self.spam_dict_size.set(f"Dictionary Size: {len(self.spam_dict)}")  # Update dictionary size label

                self.spam_bow = sorted_bag.copy()       # copy sorted_bag to spam_bow.
                self.spam_total_words.set(f"Total Word Count: {len(self.spam_bow)}")# Update total words label
                self.spam_file_list = file_list.copy()  # copy file_list to spam_file_list.

                # Populate the spam table with word frequencies
                for row in self.spam_table.get_children():
                    self.spam_table.delete(row)         # clear existing entries
                for word, freq in sorted(self.spam_dict.items()): # sort and insert new entries
                    self.spam_table.insert("", tk.END, values=(word, freq))
            else:
                messagebox.showwarning("Invalid Folder", "Please select a 'spam' or 'ham' folder.")
                exit()

    def classify_messages(self):
        # Clear existing entries
        for row in self.output_table.get_children():
            self.output_table.delete(row) 

        # to classify new messages
        file_path = filedialog.askdirectory(title="Select Classify Folder")
        selected_dir = file_path.split("/")[-1]
        selected_dir2 = file_path.split("/")[-2]
        file_list = sorted(os.listdir(file_path))

        b_o_w = []                            # Reinitializes b_o_w
        total_words = dict()                  # Reinitializes total_words
        new_words_dict = dict()               # empty dictionary for new words
        classify_dict = dict()                # empty dictionary for words in files to classify

        # Loop over each file in the classify directory
        for file in file_list:                
            temp_bag = []                     # temporary list to store words in the current file
            new_word_list = []                # list to store new words not in ham or spam

            f = open(f"{selected_dir2}/{selected_dir}/{file}", "r", encoding='latin-1')
            file_content = f.readlines()

            # Loops over each line in the file
            for i in file_content:        
                messages = i.split()          # split each line into words
                for word in messages:
                    cleaned = re.sub(r'[^a-zA-Z]', "", word)  # clean the word

                    if len(cleaned) != 0:
                        b_o_w.append(cleaned.lower())
                        temp_bag.append(cleaned.lower())

            classify_dict[file] = temp_bag      # add temp_bag to classify_dict for the file
            # self.output_dict_size.set(f"Dictionary Size: {len(self.classify_dict)}")
            # Loop over words in temp_bag
            for word in temp_bag:             
                if (word not in self.spam_dict) and (word not in self.ham_dict):
                    new_word_list.append(word)  # appends new words to new_word_list

                new_words_dict[file] = new_word_list  # store new words for each file in new_words_dict


        with open("classify.out", "w", encoding="utf-8") as classify:
            classify.write("SPAM\n")
            classify.write(f"Total Words: {len(self.spam_bow)}\n")
            classify.write(f"Dictionary Size: {len(self.spam_dict)}\n\n")

            classify.write("HAM\n")
            classify.write(f"Total Words: {len(self.ham_bow)}\n")
            classify.write(f"Dictionary Size: {len(self.ham_dict)}\n\n")

            # Create a union of spam and ham dictionaries
            spam_ham_dict_union = self.spam_dict | self.ham_dict  
            dict_size = len(spam_ham_dict_union)    # count unique words in the union

            k = Decimal(self.smoothing_entry.get()) # get user input for smoothing factor k
            classify.write(f"k = {k}\n\n")

            # Prior Probabilities of Ham and Spam
            p_ham = ((Decimal(str(len(self.ham_file_list))) + k) /
                    (Decimal(str(len(self.ham_file_list))) +
                    Decimal(str(len(self.spam_file_list))) +
                    (Decimal('2') * k)))
            p_spam = ((Decimal(str(len(self.spam_file_list))) + k) /
                    (Decimal(str(len(self.ham_file_list))) +
                    Decimal(str(len(self.spam_file_list))) +
                    (Decimal('2') * k)))

            for files in classify_dict:
                print(new_words_dict[files])
                p_msg_ham = Decimal('1')
                p_msg_spam = Decimal('1')

                # Check each word in the message from classify
                for words in classify_dict[files]:
                    # Probability of Words in Ham 
                    if words in self.ham_dict:
                        p_word_ham = ((Decimal(str(self.ham_dict[words])) + k) /
                                    (Decimal(str(len(self.ham_bow))) +
                                    k * (Decimal(str(dict_size)) +
                                            Decimal(str(len(new_words_dict[files]))))))
                    else:
                        p_word_ham = (k /
                                    (Decimal(str(len(self.ham_bow))) +
                                    k * (Decimal(str(dict_size)) +
                                            Decimal(str(len(new_words_dict[files]))))))

                    p_msg_ham *= Decimal(str(p_word_ham))

                    # Probability of Words in Spam
                    if words in self.spam_dict:
                        p_word_spam = ((Decimal(str(self.spam_dict[words])) + k) /
                                    (Decimal(str(len(self.spam_bow))) +
                                        k * (Decimal(str(dict_size)) +
                                            Decimal(str(len(new_words_dict[files]))))))
                    else:
                        p_word_spam = (k /
                                    (Decimal(str(len(self.spam_bow))) +
                                        k * (Decimal(str(dict_size)) +
                                            Decimal(str(len(new_words_dict[files]))))))

                    p_msg_spam *= Decimal(str(p_word_spam))

                # Total Message Probability
                p_msg = (Decimal(str(p_msg_spam)) * Decimal(str(p_spam)) +
                        Decimal(str(p_msg_ham)) * Decimal(str(p_ham)))

                # Posterior Probability for Spam 
                p_spam_msg = (Decimal(str(p_msg_spam)) * Decimal(str(p_spam))) / Decimal(str(p_msg))

                # CLASSIFICATION
                if p_spam_msg > p_ham:
                    classify.write(f"{files}\t Spam\t {Decimal(str(p_spam_msg))}\n")

                    # Populate the output table
                    self.output_table.insert("", tk.END, values=(f"{files}", "Spam", f"{p_spam_msg}"))
                else:
                    classify.write(f"{files}\t Ham\t {Decimal(str(p_spam_msg))}\n")
                    self.output_table.insert("", tk.END, values=(f"{files}", "Ham", f"{p_spam_msg}"))
                    
# Create and run the app
root = tk.Tk()
app = B_O_W_App(root)
root.mainloop()