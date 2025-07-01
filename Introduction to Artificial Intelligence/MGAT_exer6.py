'''
CMSC 170: Introduction to Artificial Intelligence
Exercise 6: Linear Classification using Perceptrons

MARY GWYNETH A. TOLENTINO
2021-02990
CMSC 170 GH-5L
'''

# Compute perceptron value a
def computeA(row,n):
    a = 0
    for i in range(0,n-1):
        keyx = "x" + str(i)     # feature key
        keyw = "w" + str(i)     # weight key
        a = a + (row[keyx]*row[keyw])   #update a by multiplying feature and weight
    #Add weighted bias value to a
    a = a + (row['wb']*row['b'])    
    row['a'] = round(a,1)
    
    return row  # return updated row with a

# Determine classification y
def computeY(threshold,row):
    return 1 if row['a'] >= threshold else 0

def adjustWeights(rate, currentRow, nextRow,n):
    #Adjust weight values for next row
    for i in range(0,n-1):
        keyx = "x" + str(i)
        keyw = "w" + str(i)
        nextRow[keyw] = round(currentRow[keyw] + (rate*currentRow[keyx])*(currentRow['z']-currentRow['y']),1)
    #Update weight using the formula
    nextRow['wb'] = round(currentRow['wb'] + (rate*currentRow['b'])*(currentRow['z']-currentRow['y']),1)

    return nextRow  # return updated next row with adjusted weights

# Check if all weights are the same across all rows to stop the loop
def checker(dict,rcount,xcount):
    result = True
    #Loop through each row pair to compare weights
    for r in range(1,rcount-1):
        currentR = "row"+str(r)
        nextR = "row"+str(r+1)
        for w in range(0,xcount-1):
            keyw = "w" + str(w)
            if (dict[currentR][keyw] != dict[nextR][keyw]) or dict[currentR]['wb'] != dict[nextR]['wb']:
                result = False  #if any weight is different between rows

    return result   # True if all weights are the sam
    
def write_output(iterationList,rcount,xcount):
    f = open("output.txt", "w")
    count = 1
    
    for i in iterationList:
        f.write("\nIteration "+str(count)+":\n")
        for n in range(0,xcount-1):
            f.write("\t"+"x"+str(n)+"\t\t")
        f.write("b\t\t")
        for n in range(0,xcount-1):
            f.write("w"+str(n)+"\t\t")
        f.write("wb\t\t\t")
        f.write("a\t\t")
        f.write("y\t\t")
        f.write("z\n")

        #Write each row's values for the current iteration
        for r in range(1,rcount+1):
            row = 'row'+str(r)
            for n in range(0,xcount-1):
                f.write("\t"+str(i[row]["x"+str(n)])+"\t\t")
            f.write(str(i[row]['b'])+"\t\t")
            for n in range(0,xcount-1):
                f.write(str(i[row]["w"+str(n)])+"\t\t")
            f.write(str(i[row]['wb'])+"\t\t")
            f.write(str(i[row]['a'])+"\t\t")
            f.write(str(i[row]['y'])+"\t\t")
            f.write(str(i[row]['z'])+"\n")
            
        count+=1

    f.close()

    
def main():
    file = open('input.txt','r')
    lines  = file.read().splitlines()
    total_count = 1
    rcount = 0
    dict = {}

    #Input data into dictionary
    for line in lines:
        if total_count == 1:
            dict['r'] = float(line)         # learning rate r 
        elif total_count == 2:
            dict['t'] = float(line)         # threshold t
        elif total_count == 3:
            dict['b'] = float(line)         # bias b
        else:#Store data in rows
            rcount+=1
            row = line.split()
            xcount = 0
            row_key = "row"+ str(rcount)
            row_data = {}   # dictionary to store row data

            #Loop through the row to assign feature values
            for s in row:
                if xcount == len(row) - 1:
                    #z
                    row_data['wb'] = float(0)
                    row_data['b'] = dict['b']
                    row_data['a'] = float(0)
                    row_data['y'] = float(0)
                    row_data['z'] = float(s)
                else:
                    #x
                    keyx = "x" + str(xcount)
                    keyw = "w" + str(xcount)
                    row_data[keyx] = float(s)
                    row_data[keyw] = float(0)
                xcount+=1
            dict[row_key] = row_data
        total_count+=1

    loop = True
    iteration = 0
    iterationList = []

    #Perceptron learning algorithm
    while(loop):
        for i in range(1,rcount+1):
            currentR = "row"+str(i)
            nextR = "row"+str(i+1)

            dict[currentR] = computeA(dict[currentR],xcount)            # compute for A
            dict[currentR]['y'] = computeY(dict['t'],dict[currentR])    # compute for Y

            if i<(rcount):
                dict[nextR]=adjustWeights(dict['r'],dict[currentR],dict[nextR],xcount)
            elif i == rcount:
                dict[nextR] = {}
                dict[nextR]=adjustWeights(dict['r'],dict[currentR],dict[nextR],xcount)

        print('\nIteration '+ str(iteration+1)+":")
        for i in range(rcount):
            r = "row"+str(i+1)
            print(dict[r])

        #Save iteration in list
        iterationList.append(dict)
        iteration+=1

        #Update table for next iteration
        dict['row1']['wb'] = dict[nextR]['wb']
        for i in range(0,xcount-1):
            keyw = "w" + str(i)
            dict['row1'][keyw] = dict[nextR][keyw]

        #Check if all weights are the same to end loop
        if checker(dict, rcount, xcount):
            loop = False
            write_output(iterationList,rcount,xcount)

main()