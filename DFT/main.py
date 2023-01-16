from math import pi
from MyComplex import MyComplex
from PolynomialMyComplex import PolynomialMyComplex

a = [MyComplex(1, 5), MyComplex(1, 10), MyComplex(50, 0)]
b = []
c = PolynomialMyComplex(a)
for i in range(0, len(a)):
    bi = MyComplex(2 * pi * i / len(a))
    b.append(c.P(bi))

# ------------------

for i  in b:
    print(i.get())