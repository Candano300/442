
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os
import uncertainties as unc

# Fit resonance outputs
p0                        =     0.155577  # +/-   0.000425433 #B
p1                        =     0.040129  # +/-   4.08818e-05 #w_0
p2                        =     -50.2601  # +/-   0.0798149   
p3                        =    -0.328023  # +/-   0.000293776  #A
# Fit damping outputs
Chi2                      =    0.0203322
NDf                       =          996
Edm                       =   0.00309676
NCalls                    =         1635
p0                        =      5.33174  # +/-   0.114759    
p1                        =   0.00166714  # +/-   7.04352e-06 #beta 
p2                        =    0.0407494  # +/-   2.50321e-05 #w_d 
p3                        =      2210.44  # +/-   0.0669713   
p4                        =    -0.328483  # +/-   0.000141877 # C 

#Known parameters 
I = 1.43e-4
m_s = 0.014573
m_l = 1.0385
b = 0.0461025
d = 0.066653
beta = 0.001182
deltax = unc.ufloat(2.7,0.6) #cm
L = unc.ufloat(53.1,0.3) #cm


#Fit output parameters
B = unc.ufloat(0.155577,0.000425433)
w_d = unc.ufloat(0.0407494,2.50321e-05)
beta = unc.ufloat(0.00166714,7.04352e-06)
A =unc.ufloat(0.328023,0.000293776)
C = unc.ufloat(0.328483,0.000141877)
w_0 = 0.040129 

# Calculations
deltaphi = ((deltax)/ (2*L * 2*B) ) * (C-A) 
G = ((b**2)/(m_l*m_s*2*d))*I*(w_d**2 + beta**2)*deltaphi
print("Calculated G = " , G )
#with the correction factor for G, we use that; 
fcor = (1 - (b / np.sqrt(b**2 + 4*d**2))**3)**(-1)
G = G*fcor
print('corrected G',G)

#Error calculation 
G_accepted = 6.673 * 10**(-11) #m^3 kg^-1 s^-2
uncertainty_of_G = 7e-12
print("Accepted G =" , G_accepted)

error = np.abs(G_accepted - G)/uncertainty_of_G
print("Error",error)

