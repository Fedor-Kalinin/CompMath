import numpy as np
import matplotlib.pyplot as plt

filenames = ['N5.txt']  
colors = ['r']  
labels = ['N=5 ошибка 0.0284']  # ошибка 0.8   ошибка 0.162  ошибка 0.0255 в дугом случае

plt.figure(figsize=(12, 8))  

for filename, color, label in zip(filenames, colors, labels):
    x_values = []
    y_values = []
    with open(filename, 'r') as file:
        data = file.readlines()
        
        for line in data:
            line = line.strip()
            if line:
                try:
                    x_str, y_str = line.split(',')
                    x = float(x_str.strip())
                    y = float(y_str.strip())
                    x_values.append(x)
                    y_values.append(y)
                except ValueError:
                    print(f"Ошибка преобразования строки: {line}")
    
        yest = np.exp(x_values)
    
    max_diff = float('-inf')  
    for i in range(len(yest)):
            diff = abs(yest[i] -  y_values[i]) 
            if diff > max_diff:
                max_diff = diff  

    plt.scatter(x_values, y_values, color=color, marker='.', label=label)
    plt.scatter(x_values, yest,marker='.' ) 

    print( max_diff)

plt.title('График экспоненты')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.savefig('exp5_1', dpi=300)
plt.grid()
plt.show()

