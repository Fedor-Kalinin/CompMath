import numpy as np
import matplotlib.pyplot as plt
import math
import scipy as sp
from sympy import *
import sympy as sy
x = sy.symbols('x')

f = float(sy.integrate(sin(x), (x,0,10)))
# res = f.subs(x, np.pi/2)
print(f)

plt.figure(figsize=(12, 8))  



def process_file(file_path, N):
    x_values = []
    y_values = []
    

    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(',')
            if len(parts) == 2:
                if (f - float(parts[1]) ) != 0 and math.log(float(parts[0])) <=0 :
                    x_values.append(math.log(float(parts[0])))  
                    y_values.append(math.log(abs(f- float(parts[1]))))
    print(x_values)
    print(y_values)
    return x_values, y_values
x, y = process_file("outputN3.txt",1)
x2,y2 =  process_file("outputN2.txt",1)
plt.scatter(x,y, label ='N=3')
plt.plot(x2,y2,  label ='N=2',  color = 'r' )
plt.title('Ошибка в логарифмических осях относительно ')
plt.xlabel('logh')
plt.ylabel('logE')
plt.legend()
plt.grid(True)
plt.savefig('err', dpi=300)

plt.show()
