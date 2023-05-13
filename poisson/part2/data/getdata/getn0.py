import numpy as np

second_data = np.genfromtxt('/Users/Hazal/Desktop/2nd_data.tsv', delimiter='\t')

# Now, let's get our array for n_0's, using a recursive function; 
# Define a new empty list: 

n0 = np.array([])
for i in range(len(second_data) - 1):
	n0 = np.append(n0, 10*(second_data[i+1] - second_data[i]))



print(np.around(n0,decimals=2))

np.savetxt('n0.tsv', n0 , delimiter='\t', fmt='%d')

	
