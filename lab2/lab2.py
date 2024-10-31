import numpy as np
import matplotlib.pyplot as plt
import math

filenames = ['N5.txt']  
colors = ['r']  
labels = ['N=5 ошибка 0.0284']  # ошибка 0.8   ошибка 0.162  ошибка 0.0255 в дугом случае

plt.figure(figsize=(12, 8))  



def process_file(file_path, N):
    x_values = []
    y_values = []
    

    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(',')
            if len(parts) == 2:
                x_values.append(float(parts[0]))  
                y_values.append(float(parts[1]))  
    

    exponential_values = np.exp(np.array(x_values))
    

    max_diff = float('-inf')  
    y_diff_value = 0
    for i in range(len(exponential_values)):
            diff = abs(exponential_values[i] -  y_values[i]) 
            if diff > max_diff:
                y_diff_value = (y_values[i])
                max_diff = np.log(diff) 
    if N == 0: 
        xxx = math.log(2)
    else:
        xxx = math.log(1 / N )
    # result = np.log(y_diff_value)      
    # print(result)
    # print(y_diff_value)
    # print(math.log(2))
    return max_diff, xxx

def fit_line_least_squares(x, y):
    
    x = np.array(x)
    y = np.array(y)
    
    x_mean = np.mean(x)
    y_mean = np.mean(y)

    numerator = np.sum((x - x_mean) * (y - y_mean))
    denominator = np.sum((x - x_mean) ** 2)
    
    a = numerator / denominator
    b = y_mean - a * x_mean
    
    return a, b


max_differences = []
x_ydifval_values = []
for i in range(16):
    file_name = f'output_{i}.txt'
    max_diff, x_ydifval = process_file(file_name, i)
    max_differences.append(max_diff)
    x_ydifval_values.append(x_ydifval)
    print(f'Максимальная разность для файла {file_name}: {max_diff}, соответствующее x: {x_ydifval}')

a,b = fit_line_least_squares(x_ydifval_values, max_differences)
y1= a * np.array(x_ydifval_values) +b
plt.plot(x_ydifval_values, y1, 'r', label=f'Линия МНК: {a}')

print(f'Коэффициент наклона: {a}')
# AAAAy = np.array([-3.5598618082100555, -10.975489813813308, -12.82169220615152,-16.153227738882006])
# AAAAx = np.array([0.6931471805599453, 0, -0.6931471805599453, -2.3025850929940455])


# k, b1 = fit_line_least_squares(AAAAx, AAAAy)
plt.scatter(x_ydifval_values, max_differences, label='Данные')
# plt.plot(AAAAx, k*AAAAx + b1, 'r', label=f'Линия МНК: {k}')
plt.xlabel('log(len(x))')
plt.ylabel('logERR')
plt.title('Логорифм ошибки от логорифма длины отрезка')
plt.legend()
plt.grid()
plt.savefig('N5', dpi=300)
plt.show()





