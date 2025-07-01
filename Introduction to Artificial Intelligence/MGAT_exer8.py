'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 8: Classifying Basketball Positions using K-Means

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# Calculate the distance
def calculate_distance(x, y):
    x = np.array(x)     # current feature vector being classified
    c = np.array(y)     # current centroid
    squared_diff = (x-c) ** 2
    sum_of_diff = np.sum(squared_diff)
    distance = np.sqrt(sum_of_diff)

    return distance
    # np.sqrt(np.sum((np.array(x) - np.array(y)) ** 2))


# Write the output on output.txt
def write_output(df, initial_centroids, centroids, k, iterations):
    with open("output.txt", "w") as f:
        f.write("K-Means Clustering Output from data/players_stat.csv\n")
        f.write(f"k = {k}\n\n")
        
        # Initial Centroids
        f.write("Initial Centroids\n")
        for each_centroid in initial_centroids:
            f.write(f"({each_centroid[0]}, {each_centroid[1]}, {each_centroid[2]})\n")
        
        # Final Centroids
        f.write("\nFinal Centroids\n")
        for each_centroid in centroids:
            f.write(f"({each_centroid[0]:.7f}, {each_centroid[1]:.7f}, {each_centroid[2]:.7f})\n")
        
        # Iteration count
        f.write(f"\nIterations: {iterations}\n")
        
        # Labeled Dataset
        f.write("\nLabeled Dataset:\n")
        for _, row in df.iterrows():
            f.write(f"{int(row['Cluster'])} : {int(row['Player_ID'])} - {row['Name']}\t\t\t{row[['PTS', 'AST', 'REB']].values.tolist()}\n")

def main():
    # Load data
    p_stat = pd.read_csv(r'C:\Users\Gwy\Downloads\Exercise 8 - dataset\data\players_stat.csv', header=None)
    p_stat.columns = ['Player_ID', 'PTS', 'AST', 'REB']
    
    p_id = pd.read_csv(r'C:\Users\Gwy\Downloads\Exercise 8 - dataset\data\players_id.csv', header=None)
    p_id.columns = ['Player_ID', 'Name']
    
    # Merge player ID and name data
    df = pd.merge(p_stat, p_id, on='Player_ID')
    
    # Set parameters for K-means
    k = 6
    iterations = 21
    X = df[['PTS', 'AST', 'REB']].values        #for clustering
    
    # Initial centroids
    initial_centroids = np.array([
        [367.0, 249.0, 799.0],
        [89.0, 145.0, 251.0],
        [83.0, 25.0, 94.0],
        [19.0, 25.0, 31.0],
        [60.0, 24.0, 222.0],
        [554.0, 55.0, 545.0]
    ])
    
    centroids = np.copy(initial_centroids)
    label = np.zeros(len(X))    #for storing labels
    
    # K-means algorithm
    for count in range(iterations):
        prev_centroids = np.copy(centroids)
        
        # Assign each point to the nearest centroid
        for i in range(len(X)):
            distances = np.array([calculate_distance(X[i], centroids[j]) for j in range(k)])
            label[i] = np.argmin(distances)
        
        # Recalculate centroids
        for j in range(k):
            cluster_points = X[label == j]
            if len(cluster_points) > 0:
                centroids[j] = np.mean(cluster_points, axis=0)
    
    # Add cluster label to the dataframe
    df['Cluster'] = label.astype(int)
    
    # Write the output to a file
    write_output(df, initial_centroids, centroids, k, iterations)
    
    # Plot the clusters
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    scatter = ax.scatter(df['PTS'], df['AST'], df['REB'], c=df['Cluster'], cmap='viridis')
    
    ax.set_xlabel('(PTS) Points per Game')
    ax.set_ylabel('(AST) Assists per Game')
    ax.set_zlabel('(REB) Rebounds per Game')
    ax.set_title('Clustering of NBA players')
    
    # Show and save plot
    plt.colorbar(scatter, ax=ax)
    plt.savefig('plot.png')
    plt.show()


main()