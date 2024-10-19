import numpy as np
import sys
def load_from_file(filename):
    f = open(filename, "r")
    lines = f.readlines()
    f.close()
    oupt = np.zeros((len(lines),3), dtype=np.float64)
    count = 0
    for line in lines:
        nl = line.split()
        for i in range(3):
            oupt[count][i] = float(nl[i])
        count +=1 
    return(oupt)
def RMSE(new, old,n):
    oupt = 0.
    for i in range(n):
        row = old[i]- new[i]
        row1 = np.array([np.square(xi) for xi in row])
        row2 = np.sum(row1)
        oupt += np.sqrt(row2)
    return(oupt/n)


def main():
    print("Changed vectors")
    for i in range(4):
        origional = f"src/ptcl_{i}_99.plt"
        new = f"src_Vector_Class/ptcl_{i}_99.plt"
        orig = load_from_file(origional)
        new = load_from_file(new)
        n = new.shape[0]
        rmse1 = RMSE(new, orig,n)
        print(f"RMSE between ptcl_{i}_99.plt: "+ str(rmse1))
    print("changed Equation")
    for i in range(4):
        origional = f"src/ptcl_{i}_99.plt"
        new = f"src_equ_Vec1/ptcl_{i}_99.plt"
        orig = load_from_file(origional)
        new = load_from_file(new)
        n = new.shape[0]
        rmse1 = RMSE(new, orig,n)
        print(f"RMSE between ptcl_{i}_99.plt: "+ str(rmse1))

    

main()