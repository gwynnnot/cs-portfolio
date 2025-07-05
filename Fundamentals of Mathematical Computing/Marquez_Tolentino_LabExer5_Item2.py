def set_intersection(a,b):
    intersection = []
    for x in a:
        for y in b:
            if x==y:
                intersection = intersection + [x]
    return intersection
def set_union(a,b):
    union = []
    for x in (a+b):
        valid = True
        for z in union:
            if x == z:
                valid = False
                break
        if valid:
            union = union + [x]
    return union
a = int(input("Enter how many number of elements on Set A: "))
b = int(input("Enter how many number of elements on Set B: "))

aArr = []
bArr = []
aCounter = 0
bCounter = 0

while aCounter != a:
    inAArr = True
    new = float(input("Enter element " + str(aCounter + 1) + " of Set A: "))
    for element in range(0,len(aArr)):
        if aArr[element] == new:
            inAArr = False
            break
    if inAArr == True:
        aArr = aArr + [new]
        aCounter = aCounter + 1
    else:
        print("Duplicate element.")

while bCounter != b:
    inBArr = True
    new = float(input("Enter element " + str(bCounter + 1) + " of Set B: "))
    for element in range(0,len(bArr)):
        if bArr[element] == new:
            inBArr = False
            break
    if inBArr == True:
        bArr = bArr + [new]
        bCounter = bCounter + 1
    else:
        print("Duplicate element.")

print("\nSet Intersection: ", set_intersection(aArr,bArr))
print("Set Union: ", set_union(aArr,bArr))


