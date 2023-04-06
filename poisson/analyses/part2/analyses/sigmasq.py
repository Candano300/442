import numpy as np
#Calculate 1/sigma^2 first, get the sigma's from our output; 
sigma = np.array([0.011, 0.007])
a = np.sum(1/(sigma**2))
#To calculate the weighted alpha now, get the alpha datas from the ROOT graphs; 
alpha = np.array([0.088, 0.111 ])
b = np.sum(alpha/(sigma**2))
print(b/a)
#Calculate the error in terms of sigma now; 
print(1/a)
print(1/np.sqrt(a))
print(abs((b/a) - 0.108) * np.sqrt(a))