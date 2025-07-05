# -*- coding: utf-8 -*-
"""
Created on Mon Feb 26 08:07:59 2024

@author: Acer
"""
import numpy as np

a1 = float(input("1st component of A: "))
a2 = float(input("2nd component of A: "))
a3 = float(input("3rd component of A: "))
print()
b1 = float(input("1st component of B: "))
b2 = float(input("2nd component of B: "))
b3 = float(input("3rd component of B: "))
print()

print("Vector A = <", a1, a2, a3,">")
print("Vector B = <", b1, b2, b3,">")

magnitude = np.sqrt(b1**2 + b2**2 + b3**2)

print("Magnitude of B =", magnitude)

print("Unit Vector in the direction of B is <",b1/magnitude, b2/magnitude, b3/magnitude,">")

dot = a1*b1 + a2*b2 + a3*b3

print("Dot product of A and B =", dot)

print("Are A and B orthogonal?", dot == 0)
