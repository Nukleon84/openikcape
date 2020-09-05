import sys
sys.path.append('../bin')
sys.path.append('bin')

import openikcape as ikc
import random

res=ikc.add(1, 2)
print(res)

comp1= ikc.get_component("Water")
for i in range(100):
    T=random.uniform(273.0,373.0)
    p=random.uniform(0.1,3.0)*1e5
    k, dKdT= ikc.kvalue(comp1, T,p )
    print(f"T={T} K     P={p} Pa  K = {k}   dKdT={dKdT}")

print(f"{comp1.name} [CAS={comp1.casno}, Formula={comp1.formula}]")