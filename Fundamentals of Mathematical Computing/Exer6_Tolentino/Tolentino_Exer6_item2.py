import numpy as np

def function(x,y):
    return 2 * x**2 - y**2

def approximation(num_iterations):
    x_initial = np.random.uniform(-1, 1)
    y_initial = np.random.uniform(-1, 1)
    
    max_val = function(x_initial, y_initial)
    min_val = max_val
    max_point = (x_initial, y_initial)
    min_point = max_point
    
    for i in range(num_iterations):
        x = np.random.uniform(-1, 1)
        y = np.random.uniform(-1, 1)
        value = function(x, y)
        
        if value > max_val:
            max_val = value
            max_point = (x, y)
        
        if value < min_val:
            min_val = value
            min_point = (x, y)
    
    return max_val, max_point, min_val, min_point

num_iterations = int(input("Enter number of random samples: "))
while num_iterations <=0:
    num_iterations = int(input("Enter number of random samples: "))

max_val, max_point, min_val, min_point = approximation(num_iterations)

print("\n=== APPROXIMATE MAXIMUM VALUE ===")
print("Maximum value:", max_val)
print("Occurs at point:", max_point)
print("\n=== APPROXIMATE MINIMUM VALUE ===")
print("Minimum value:", min_val)
print("Occurs at point:", min_point)