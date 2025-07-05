import numpy as np

def p1(x,n):
    return x**(1/ n+2)

def p2(x,n):
    return x**(n+2)
    
def method1(n):
    differences = np.zeros(n)

    for i in range(n):
        x = np.random.random()
        p1_val = p1(x,n)
        p2_val = p2(x,n)
        differences[i] = p1_val - p2_val
    
    return np.mean(differences) # average

def method2(n):
    points = []
    points_between = []

    for i in range(n):
        x = np.random.random()
        y = np.random.random()
        points.append(y)

        if p2(x,n) <= y <= p1(x,n):
            points_between.append(y)

    return len(points_between)/len(points)

n=1 * 10**4

print("=== AREA OF A REGION ===")
print("Area of the region using Method 1:", method1(n))
print("Area of the region using Method 2:", method2(n))

# Both methods are efficient but Method 1 is simpler and more straightforward. It directly calculates the mean of the differences between the two functions.