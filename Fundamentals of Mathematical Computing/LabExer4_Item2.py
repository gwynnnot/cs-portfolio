# -*- coding: utf-8 -*-
"""
Created on Mon Mar  4 08:30:53 2024

@author: Acer
"""

num1 = float(input("Enter a natural number: "))
while num1 <= 0 or num1 != int(num1):
    num1 = float(input("Please enter a positive integer: "))
    
num2 = float(input("Enter another natural number: "))
while num2 <= 0 or num2 != int(num2):
    num2 = float(input("Please enter a positive integer: "))

if num1<num2:
    factor = int(num1)
else: factor = int(num2)

print("")
print("The common factors of",int(num1),"and",int(num2),"are:")
for factor in range(1, factor + 1):
    if int(num1) % factor == 0 and int(num2) % factor == 0:
        print(factor)