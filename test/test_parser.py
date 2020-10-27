import sys
sys.path.append('bin')
import openikcape as ikc


def test_can_load_prop_dat():
    db= ikc.loadDatabase("bin/prop.dat")
    assert True

def test_can_load_component():
    db= ikc.loadDatabase("bin/prop.dat")
    comps=db.getComponentList()    
    assert len(comps)==15