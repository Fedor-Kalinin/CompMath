import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

def read_data(filename):
    data = np.loadtxt(filename)
    return data[:, 0], data[:, 1]

file_names = ['data3.txt', 'data4.txt', 'data5.txt']
words = ['шаблон -1 1', 'шаблон -1 1 2', 'шаблон - 2 -1 1 2']  


plt.figure(figsize=(10, 8))

for i, file_name in enumerate(file_names):

    x, y = read_data(file_name)


    log_x = x
    log_y = y


    mask = log_x < 0 
    mask = log_x > -10
    if np.any(mask):  
        model = LinearRegression()
        model.fit(log_x[mask].reshape(-1, 1), log_y[mask])
        y_pred = model.predict(log_x[mask].reshape(-1, 1))



        slope = model.coef_[0]  
        legend_label = f'{file_name} (Наклон: {slope:.4f},{words[i]})'
       
        plt.plot(log_x[mask], y_pred, color='r', linestyle='--',  label=legend_label)

    plt.plot(log_x, log_y, marker='o')


plt.xscale('linear')
plt.yscale('linear')
plt.xlabel('Логарифм h')
plt.ylabel('Логарифм E')
plt.title('График E от h с логарифмическими осями')
plt.legend()
plt.grid(True)

plt.savefig('logarithmic_plot.png', dpi=300)
plt.show()