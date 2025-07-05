import numpy as np 
import numpy.polynomial.polynomial as p 

roots = [1,3,5,7,9,11,13,15,17,19]
P=p.polyfromroots(roots)

hatP=p.polyadd(P,np.poly1d([1,0,0,0,0,0]))

print("=====Roots of P========")
for i in roots:
    print(i, end=", ")

print("")
print("=====Roots of Phat=====")
for i in p.polyroots(hatP):
    print(i, end=", ")

print("""\n
There are only small pertubations introduced to the coefficient of x^6 and it introduced a "Proportionate" small error in the roots. We can intuitively say that the problem is well conditioned.
""")