import sys
sys.path.append('bin')

import openikcape as ikc



def test_add():
    assert ikc.add(2,3) == 5
    assert ikc.add(5,-2) == 3