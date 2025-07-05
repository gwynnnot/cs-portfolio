# -*- coding: utf-8 -*-
"""
Created on Mon Mar  4 08:10:57 2024

@author: Acer
"""

num = float(input("Enter a real number: "))

print("")
print("[1] Absolute Value")
print("[2] Greatest Integer Value")

choice = int(input("\nPlease enter your choice: "))
if choice == 1:
    if num >=0:
        abs = num 
    else: 
        abs = -num
    print("\n\tThe absolute value of",num,"is",int(abs))
    
elif choice == 2:
    if num >= 0 or int(num) == num:
        result = int(num)
    else: 
        result = int(num) - 1
        
    print("\n\tThe greatest integer function of",num,"is",result)
else: print("Invalid choice! Please choose between 1 or 2.")
        
    

    
    