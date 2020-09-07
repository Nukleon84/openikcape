import sys
sys.path.append('../bin')
sys.path.append('bin')

import openikcape as ikc
import random

res=ikc.add(1, 2)
print(res)

db= ikc.loadDatabase("bin/prop.dat")
sys=ikc.createSystem("test",db,["Ethanol","Water"])
calc=ikc.createCalculator(sys)
for i in range(20):
    T=273.15+10*i
    plV=calc.getPureProperty("VP", 0, T)
    print(f"T={T} PlV={plV}")
