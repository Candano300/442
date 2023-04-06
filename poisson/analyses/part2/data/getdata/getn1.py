import numpy as np

second_data = np.genfromtxt('/Users/Hazal/Desktop/2nd_data.tsv', delimiter='\t')

# Now let's get our array for n_1's, using a recursive function;
# Define a new empty list: 

n1 = np.array([])
for i in range(len(second_data) - 2):
	n1 = np.append(n1, 10*(second_data[i+2] - second_data[i]))



print(len(np.around(n1,decimals=2)))

np.savetxt('/Users/Hazal/Desktop/n1.tsv', n1 , delimiter='\t', fmt='%d')

