import data
import numpy as np
r1,r2,r3,r4 = data.r1 , data.r2 , data.r3 , data.r4
sigmaqm = []
# I will use this function to get the data I will use to line-fit
def x_y_data_points(list):
 V,I,r = list[0],list[1],list[2]
 c = (125 * (0.2) ** 2) / (64 * ((1.26 * 10 ** (-6)) ** 2) * 154 ** 2) #constant of my equation
 print('c',"{:e}".format(c))
 ls1 , ls2, ls3, ls4= [],[],[],[]
 for i in range(5):
  rhs = ((r) ** 2) / (2 * V[i]) #right hand side of the equation
  lhs = c / I[i] ** 2 #left hand side of the equation
  var = (c * (2) * (0.01)) / (I[i] ** 3) #sigma of the right hand side
  ls1.append("{:e}".format(rhs)) , ls2.append("{:e}".format(lhs)) , ls3.append(var), ls4.append(lhs/rhs)

 sigmaqm.append(np.std(ls4))
 print('rhs:', ls1)
 print('lhs:', ls2)
 print('var:', ls3)
 print('q/m:', ls4)
 print('q/m sigma:', np.std(ls4))

 return()

print('----------------------------r = 2.00 cm -------------------------------')
x_y_data_points(r1)
print('----------------------------r = 3.00 cm -------------------------------')
x_y_data_points(r2)
print('----------------------------r = 4.00 cm -------------------------------')
x_y_data_points(r3)
print('----------------------------r = 5.00 cm -------------------------------')
x_y_data_points(r4)
print('-----------------------------------------------------------------------')


#Line-fit data:
qoverm = np.array([2.012e+11 , 1.804e+11,1.871e+11,1.951e+11])
sigmaqm = np.array([4.194e+09,2.533e+09,8.222e+09,7.78e+09])


#weight equations:
weightedmeans = np.sum(qoverm/sigmaqm**2) / np.sum(1/sigmaqm**2)
weightedsigmaqm = 1/np.sum(sigmaqm**(-2))

#finding the error:
realqm = (1.76)*(10**11)
error = (weightedmeans - realqm) / (weightedsigmaqm) * 100

print('weighted sigma q/m:', "{:e}".format(weightedsigmaqm))
print('weighted q/m:',"{:e}".format(weightedmeans))
print('error:',error)