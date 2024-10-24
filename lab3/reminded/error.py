import numpy as np
import matplotlib.pyplot as plt

filenames = ['N5.txt']  
colors = ['r']  
labels = ['N=5 ошибка 0.0284']  # ошибка 0.8   ошибка 0.162  ошибка 0.0255 в дугом случае

plt.figure(figsize=(12, 8))  

x =[0.7, 1, 1.3, 1.6, 1.9, 2.2]
y = [4.3386, 4.1237, 3.99, 3.7326, 3.449, 3.16435]

x = np.array(x)  
y = np.array(y)  

m, b = np.polyfit(x, y, 1)

y_fit = m * x + b

plt.scatter(x, y, color='blue', label='Данные')
plt.plot(x, y_fit, color='red', label=m)

plt.title('Ошибка в логарифмических осях от N')
plt.xlabel('logN')
plt.ylabel('logE')
plt.legend()
plt.savefig('err', dpi=300)
plt.grid()
plt.show()
