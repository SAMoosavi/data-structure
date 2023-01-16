from MyComplex import MyComplex


class PolynomialMyComplex:
    __a: list[MyComplex] = []

    def __init__(self, a: list[MyComplex]):
        for i in a:
            self.__a.append(i)

    def P(self, a: MyComplex):
        b = a.mul(self.__a[0])
        for i in range(1, len(self.__a)):
            b = b.sum(self.__a[i])
            if i != len(self.__a) - 1:
                b = b.mul(a)
        return b
