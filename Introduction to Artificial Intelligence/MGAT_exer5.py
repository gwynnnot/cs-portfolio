'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 5: Naïve Bayes Classifier Validation

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import math
import operator
import re
import os
import shutil
from decimal import Decimal, getcontext
from tkinter import *
from tkinter import filedialog
import numpy as np

getcontext().prec = 50

class B_O_W:
    def __init__(self, dict_size, words_count, occurences, occurences_dict, num_of_messages):
        self.dict_size = dict_size
        self.words_count = words_count
        self.occurences = occurences
        self.occurences_dict = occurences_dict,
        self.num_of_messages = num_of_messages

class Naive_Bayes:
    def __init__(self, spam : B_O_W, ham : B_O_W, messages : B_O_W, k : float):
        self.spam = spam
        self.ham = ham
        self.messages = messages
        self.k = k
        self.spam_ham_dict_union = self.spam.occurences_dict | self.ham.occurences_dict
        self.new_words_dict = {key: self.messages.occurences_dict[key] for key in self.messages.occurences_dict if key not in self.spam.occurences_dict}
        self.new_words_length = 0
        for key in self.new_words_dict.keys():
            self.new_words_length += self.new_words_dict[key]

    def p_msg_spam(self):
        result = 1
        for occurence in self.messages.occurences:
            occurence_in_spam = 0 + self.k
            if occurence[0] in self.spam.occurences_dict.keys():
                occurence_in_spam = self.spam.occurences_dict[occurence[0]] + self.k
                
            word_count_in_spam = self.spam.words_count + ( self.k * (len(self.spam_ham_dict_union) + self.new_words_length) )
            result *= Decimal(occurence_in_spam/ word_count_in_spam)
        return result
    
    def p_spam(self):
        return Decimal((self.spam.num_of_messages + self.k) / (self.spam.num_of_messages + self.ham.num_of_messages + 2 * self.k))
    
    def p_msg_ham(self):
        result = 1
        for occurence in self.messages.occurences:
            occurence_in_ham = 0 + self.k
            if occurence[0] in self.ham.occurences_dict.keys():
                occurence_in_ham = self.ham.occurences_dict[occurence[0]] + self.k
                
            word_count_in_ham = self.ham.words_count + ( self.k * (len(self.spam_ham_dict_union) + self.new_words_length) )
            result *= Decimal(occurence_in_ham/ word_count_in_ham)
        return result
    
    def p_ham(self):
        return Decimal((self.ham.num_of_messages + self.k) / (self.spam.num_of_messages + self.ham.num_of_messages + 2 * self.k))
    
    def calculate_p(self):
        p_msg = Decimal(self.p_msg_spam()) * Decimal(self.p_spam()) + Decimal(self.p_msg_ham()) * Decimal(self.p_ham())

        p_spam_msg = Decimal(self.p_msg_spam()) * Decimal(self.p_spam()) / Decimal(p_msg)
        
        classification = "Spam" if p_spam_msg > 0.5 else "\tHam\t"
        return classification, p_spam_msg

class B_O_W_App:
    def __init__(self, root):
        self.root = root
        self.root.title("Bag-of-Words")
        self.root.config(bg="lightblue")
        self.words_count = []
        self.data = {
            "spam": B_O_W(0, 0, [], {}, 0),
            "ham": B_O_W(0, 0, [], {}, 0),
            "messages": B_O_W(0, 0, [], {}, 0),
        }
        self.k = ""
        self.k_parameters = [0.005, 0.01, 0.5, 1.0, 2.0]
        self.output = []
        self.current_folder = ""
        self.models =  {0: { "TP": 0, "FN": 0, "FP": 0, "TN": 0, "accuracy": 0, "precision": 0, "recall": 0 }}

        title_label = Label(root, text="Naïve Bayes Classifier Validation", font=("Arial", 18, "bold"), bg="lightblue")
        title_label.grid(row=0, columnspan=2)
        subtitle_label = Label(self.root, text="CMSC 170 GH5L\nMary Gwyneth Tolentino", font=("Arial", 12), bg="lightblue")
        subtitle_label.grid(row=2, columnspan=2)

        select = Button(root, text="Select folder", command=self.import_dataset)
        select.grid(row=3, columnspan=2)

        k_label = Label(root, text="Enter k value:", bg="lightblue")
        k_label.grid(row=4, columnspan=2)

        self.k_entry = Entry(root)
        self.k_entry.grid(row=5, columnspan=2)
        self.k_entry.insert(0, str(self.k))  
        self.root.geometry("")  # Resize window to fit content

        set_k_btn = Button(root, text="Set k", command=self.set_k)
        set_k_btn.grid(row=6, columnspan=2)

        classify_btn = Button(root, text="Classify", command=self.classify)
        classify_btn.grid(row=7, columnspan=2)

    # Update smoothing parameter
    def set_k(self):
        try:
            self.k = float(self.k_entry.get())
            print(f"Value of k set to: {self.k}")
        except ValueError:
            print("Please enter a valid float value for k.")

    def clean_word(self, messages):
        result = ""
        for word in messages:
            if re.search("[a-zA-Z]", word):
                result += word.lower()
        
        if result == "":
            return None
        
        return result

    # Extract word counts
    def get_words_from_file(self, filename):
        words_count = {}
        with open(filename, "r",encoding="latin-1") as file:
            lines = file.readlines()
            for line in lines:
                words = re.split("\s+",line)
                for word in words:
                    cleaned_word = self.clean_word(word)
                    if cleaned_word == None:
                        continue

                    if cleaned_word in words_count.keys():
                        words_count[cleaned_word] += 1
                    else:
                        words_count[cleaned_word] = 1
        return words_count
    
    def analyze_file(self, file_path, output_name, type):
        words_count = {}
        file_words_count = self.get_words_from_file(file_path)
        for word in file_words_count.keys():
            if word in words_count.keys():
                words_count[word] += file_words_count[word]
            else:
                words_count[word] = file_words_count[word]
        
        sorted_words_count = sorted(words_count.items(), key=operator.itemgetter(0))
        size = len(sorted_words_count)

        total_word_count = 0
        for word_count in words_count.values():
            total_word_count += word_count
        
        self.data[type].dict_size = size
        self.data[type].words_count = total_word_count
        self.data[type].occurences = sorted_words_count
        self.data[type].occurences_dict = words_count
        self.data[type].num_of_messages = 1

        with open(output_name, "w") as file:
            output = [
                "Dictionary Size: " + str(size) + "\n",
                "Total Word Count: " + str(total_word_count) + "\n",
                ""
            ]
            for word_count in sorted_words_count:
                output.append("{x} {y}\n".format(x=word_count[0], y=word_count[1]))
            file.writelines(output)

    def analyze_folder(self, directory, output_name, type):
        files = os.listdir(directory)

        words_count = {}
        for file_name in files:
            file_words_count = self.get_words_from_file(directory + "/" + file_name)
            for word in file_words_count.keys():
                if word in words_count.keys():
                    words_count[word] += file_words_count[word]
                else:
                    words_count[word] = file_words_count[word]
        
        sorted_words_count = sorted(words_count.items(), key=operator.itemgetter(0))
        size = len(sorted_words_count)

        total_word_count = 0
        for word_count in words_count.values():
            total_word_count += word_count
        
        self.data[type].dict_size = size
        self.data[type].words_count = total_word_count
        self.data[type].occurences = sorted_words_count
        self.data[type].occurences_dict = words_count
        self.data[type].num_of_messages = len(files)

        with open(output_name, "w") as file:
            output = [
                "Dictionary Size: " + str(size) + "\n",
                "Total Word Count: " + str(total_word_count) + "\n",
                ""
            ]
            for word_count in sorted_words_count:
                output.append("{x} {y}\n".format(x=word_count[0], y=word_count[1]))
            file.writelines(output)
      
    def import_dataset(self):
        folder_name = filedialog.askdirectory()
        self.current_folder = folder_name

        self.partition_dataset(folder_name)
        self.train_dataset(os.path.join(folder_name,"pipeline","training"))
        print("Start Validation")
        self.validate_dataset(os.path.join(folder_name,"pipeline","validation"))
        print("Start Testing")
        self.current_folder = os.path.join(folder_name,"pipeline","test")


    # Classify test files and compute metrics
    def classify(self):
        testing_folder = self.current_folder
        current_k = self.k
        self.output = []

        print("Evaluating k={k}....".format(k=current_k))

        # For confusion matrix
        TP = 0      # Spam correctly classified as spam
        TN = 0      # Ham correctly classified as ham
        FP = 0      # Ham incorrectly classified as spam
        FN = 0      # Spam incorrectly classified as ham

        spam_dir = os.path.join(testing_folder, "spam")
        ham_dir = os.path.join(testing_folder, "ham")

        # test spam folder first
        self.output.append("SPAM\n")
        self.output.append("Total Words: {total}\n".format(total=self.data["spam"].words_count))
        self.output.append("Dictionary Size: {size}\n".format(size=self.data["spam"].dict_size))
        self.output.append("\n")

        file_names = os.listdir(spam_dir)
        for file_name in file_names:
            self.analyze_file(spam_dir + "/" + file_name, "messages.out", "messages")
            classification, probability = Naive_Bayes(self.data["spam"], self.data["ham"], self.data["messages"], current_k).calculate_p()
            self.output.append("{filename}\t{classification}\t{probability}\n".format(filename=file_name[:-4], classification=classification, probability=probability))
            if classification == "Spam":
                TP += 1     # Spam correctly classified as spam
            else:
                FN += 1     # Spam incorrectly classified as ham

        # test ham folder
        self.output.append("HAM\n")
        self.output.append("Total Words: {total}\n".format(total=self.data["ham"].words_count))
        self.output.append("Dictionary Size: {size}\n".format(size=self.data["ham"].dict_size))
        self.output.append("\n")

        file_names = os.listdir(ham_dir)
        for file_name in file_names:
            self.analyze_file(ham_dir + "/" + file_name, "messages.out", "messages")
            classification, probability = Naive_Bayes(self.data["spam"], self.data["ham"], self.data["messages"], current_k).calculate_p()
            self.output.append("{filename}\t{classification}\t{probability}\n".format(filename=file_name[:-4], classification=classification, probability=probability))
            if classification == "Spam":
                FP += 1     # Ham incorrectly classified as spam
            else:
                TN += 1     # Ham correctly classified as ham
        
        self.output.append("k = {k}\n".format(k=self.k))
        self.output.append("\n")
        with open("{k}-testing.out".format(k=current_k),"w") as file:
            file.writelines(self.output)
        
        accuracy = (TP+TN)/(TP+TN+FN+FP)
        precision = (TP)/(TP+FP)
        recall = (TP)/(TP+FN)

        self.models[current_k] = { "TP": TP, "FN": FN, "FP": FP, "TN": TN, "accuracy": accuracy, "precision": precision, "recall": recall }
        print("Accuracy: {accuracy}".format(accuracy=accuracy))
        print("Precision: {precision}".format(precision=precision))
        print("Recall: {recall}".format(recall=recall))
        print(self.confusion_dict_to_matrix(self.models[current_k]))
        print("\n")

    # Split dataset into training, validation, and test sets
    def partition_dataset(self, directory):
        pipeline_dir = os.path.join(directory, "pipeline")
        files = os.listdir(directory)
        sub_folders = ["ham", "spam"]
        partition_sizes = {
            "training_size": 0,
            "validation_size": 0,
            "test_size": 0,
        }
         
        if os.path.exists(pipeline_dir):
            print("\nDeleting pipeline folder...")
            shutil.rmtree(pipeline_dir)

        print("\nCreating pipeline folder...")
        os.mkdir(pipeline_dir)
        os.mkdir(os.path.join(pipeline_dir,"training"))
        os.mkdir(os.path.join(pipeline_dir,"training","spam"))
        os.mkdir(os.path.join(pipeline_dir,"training","ham"))
        os.mkdir(os.path.join(pipeline_dir,"validation"))
        os.mkdir(os.path.join(pipeline_dir,"validation","spam"))
        os.mkdir(os.path.join(pipeline_dir,"validation","ham"))
        os.mkdir(os.path.join(pipeline_dir,"test"))
        os.mkdir(os.path.join(pipeline_dir,"test","spam"))
        os.mkdir(os.path.join(pipeline_dir,"test","ham"))

        for sub_folder in sub_folders:
            print("\n")
            files = os.listdir(os.path.join(directory, sub_folder))

            # split by 50%, 25%, 25%
            split_indices = [len(files) // 2, (len(files) * 3) // 4]
            partitions = {
                "training": files[0:split_indices[0]],
                "validation": files[split_indices[0]:split_indices[1]],
                "test": files[split_indices[1]:]
            }

            for key in partitions.keys():
                print("Transferring {key} files from {sub_folder} to pipeline...".format(key=key, sub_folder=sub_folder))
                for file in partitions[key]:
                    source = os.path.join(directory, sub_folder, file)
                    destination = os.path.join(directory, "pipeline", key, sub_folder, file)
                    if os.path.isfile(source):
                        shutil.copy(source, destination)
                partition_sizes["{key}_size".format(key=key)] += len(partitions[key])
        
            print(sub_folder)
            print("training", len(partitions["training"]))
            print("validation", len(partitions["validation"]))
            print("test", len(partitions["test"]))

        print(partition_sizes)
    
    # Analyze training data
    def train_dataset(self, directory):
        sub_folders = os.listdir(directory)
        for sub_folder in sub_folders:
            print("Analyzing " + directory + "/" + sub_folder)
            if sub_folder == "ham":
                self.analyze_folder(directory + "/" + sub_folder, "ham.out", "ham")
            if sub_folder == "spam":
                self.analyze_folder(directory + "/" + sub_folder, "spam.out", "spam")
    
    # Evaluate model with different k values
    def validate_dataset(self, validation_folder):
        for current_k in self.k_parameters:
            self.output = []
            print("Evaluating k={k}....".format(k=current_k))

            # For confusion matrix
            TP = 0  
            TN = 0
            FP = 0
            FN = 0

            spam_dir = os.path.join(validation_folder, "spam")
            ham_dir = os.path.join(validation_folder, "ham")

            # test spam folder first
            self.output.append("SPAM\n")
            self.output.append("Total Words: {total}\n".format(total=self.data["spam"].words_count))
            self.output.append("Dictionary Size: {size}\n".format(size=self.data["spam"].dict_size))
            self.output.append("\n")

            file_names = os.listdir(spam_dir)
            for file_name in file_names:
                self.analyze_file(spam_dir + "/" + file_name, "messages.out", "messages")
                classification, probability = Naive_Bayes(self.data["spam"], self.data["ham"], self.data["messages"], current_k).calculate_p()
                self.output.append("{filename}\t{classification}\t{probability}\n".format(filename=file_name[:-4], classification=classification, probability=probability))
                if classification == "Spam":
                    TP += 1
                else:
                    FN += 1

            # test ham folder
            self.output.append("HAM\n")
            self.output.append("Total Words: {total}\n".format(total=self.data["ham"].words_count))
            self.output.append("Dictionary Size: {size}\n".format(size=self.data["ham"].dict_size))
            self.output.append("\n")

            file_names = os.listdir(ham_dir)
            for file_name in file_names:
                self.analyze_file(ham_dir + "/" + file_name, "messages.out", "messages")
                classification, probability = Naive_Bayes(self.data["spam"], self.data["ham"], self.data["messages"], current_k).calculate_p()
                self.output.append("{filename}\t{classification}\t{probability}\n".format(filename=file_name[:-4], classification=classification, probability=probability))
                if classification == "Spam":
                    FP += 1
                else:
                    TN += 1
            
            self.output.append("k = {k}\n".format(k=self.k))
            self.output.append("\n")
            with open("{k}-validation.out".format(k=current_k),"w") as file:
                file.writelines(self.output)
            
            accuracy = (TP+TN)/(TP+TN+FN+FP) # overall proportion of correct predictions out of the total number of cases
            precision = (TP)/(TP+FP)# proportion of positive predictions that were actually correct
            recall = (TP)/(TP+FN)   # proportion of actual positive cases that are correctly identified as positive

            self.models[current_k] = { "TP": TP, "FN": FN, "FP": FP, "TN": TN, "accuracy": accuracy, "precision": precision, "recall": recall }
            print("Accuracy: {accuracy}".format(accuracy=accuracy))
            print("Precision: {precision}".format(precision=precision))
            print("Recall: {recall}".format(recall=recall))
            print(self.confusion_dict_to_matrix(self.models[current_k]))
            print("\n")

        
        # print(self.models)
        print("\n")
        most_accurate_model_key = 0
        for key in self.models.keys():
            if self.models[key]["accuracy"] > self.models[most_accurate_model_key]["accuracy"]:
                most_accurate_model_key = key
        
        self.k = most_accurate_model_key
        print("Most accurate k:",self.k)

    # Format confusion matrix 
    def confusion_dict_to_matrix(self, confusion_dict):
        matrix = [[confusion_dict["TP"], confusion_dict["FN"]], [confusion_dict["FP"], confusion_dict["TN"]]]
        return np.matrix(matrix)


# Create and run the app
root = Tk()
app = B_O_W_App(root)
root.mainloop()