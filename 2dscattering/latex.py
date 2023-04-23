import pandas as pd
import numpy as np

def s(x):
    return np.sqrt(x)

data = [
    ('i','Degree', 'Count', 'Uncertainty'),
    (1,(10,30), 38 , s(38) ),
    (2,(30,50), 19 , s(19)),
    (3,(50,70), 30 , s(30)),
    (4,(70,90), 35 , s(35)),
    (5,(90,110), 40 , s(40)),
    (6,(110,130), 46 , s(46)),
    (7,(130,150), 50 , s(50)),
    (8,(150,170), 56 , s(56)),
]



df = pd.DataFrame(data[1:], columns=data[0])

print(df.to_latex(index=False))
