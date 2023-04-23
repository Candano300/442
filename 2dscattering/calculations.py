import numpy as np 
import uncertainties as unc



#Calculate I and its uncertainty 
gun_distance = unc.ufloat(6.50, 0.1) # cm
gun_turns = 51 
number_of_shots_per_turn = 20
I = number_of_shots_per_turn / (gun_distance/gun_turns) 

#CALCULATION OF R VIA LINEFIT  

# Prepare the data for linefit
data = np.loadtxt('/Users/Hazal/Desktop/analysis/data.txt')
N_i= data[:]

print(len(N_i))
print(N_i)
thetadegrees = np.array([20*i for i in range(1,len(N_i)+1)])
thetadegrees = np.array([ 40 , 60 , 80, 100, 120 ,140 ,160,200 ,220 ,240, 260, 280 ,310])

thetas = np.deg2rad(thetadegrees)
print(thetas)
print(len(thetas))

thetasdegrees = [40,60,80,100,120,140,160,200,220,240,260,280,300,320]
shots =         [4 ,18,23,25 ,36 ,35 ,84 ,78 ,29,38,37,34,37,27]
N_i = shots
thetas = np.deg2rad(thetasdegrees)

x  = np.array(np.sin(thetas/2))
y  = np.array(N_i)
sx = np.array([0] * len(N_i))
sy = np.array(np.sqrt(N_i))


linefit_data = np.column_stack((x,y,sx,sy))
np.savetxt('linefit_data.txt', linefit_data, delimiter='\t')

''' 
Processing linefit.c...
 FCN=15.6832 FROM MIGRAD    STATUS=CONVERGED      33 CALLS          34 TOTAL
                     EDM=1.35669e-21    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  p0           4.68302e+01   5.81408e+00   4.55976e-03   1.55829e-11
   2  p1          -1.09075e+01   3.37070e+00   2.64351e-03   1.34394e-11


 FCN=43.9728 FROM MIGRAD    STATUS=CONVERGED      31 CALLS          32 TOTAL
                     EDM=4.16898e-22    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  p0           4.28650e+01   4.28373e+00   6.29136e-03   1.12940e-11
   2  p1          -3.30755e+00   2.53078e+00   3.71686e-03   9.55837e-12
'''
# Okay. Now we have the parameters of the linefit. Since p0 was the slope we were
# looking for and the uncertainty is also calculated in ROOT, we can safely say that
 
S =    6.05142e+01 
sigma_S = 5.27909e+00 

S = unc.ufloat(S, sigma_S)

# Calculation of r via the formula r / 2 = S / I delta(theta)
print(I)
r_cal =  (2 * S )/ ( I* np.deg2rad(20) )
print(r_cal)

# CALCULATION OF R DIRECTLY
r_dir = np.sum(N_i)/(I*2)
print(r_dir)


#ERROR CALCULATIONS

#Error of r_fit
error = (2.7 - 2.21) / 0.20
print(error)

#Error of r_direct
error = (2.7 - 1.609) / 0.2
print(error)