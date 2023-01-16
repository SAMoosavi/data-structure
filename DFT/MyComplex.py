from math import cos, sin


class MyComplex:
    __a = 0
    __b = 0

    def __init__(self, a, b=None):
        if b is not None:
            self.__set_normal(a, b)
        else:
            self.__set_cis(a)

    def __set_cis(self, a):
        self.__a = cos(a)
        self.__b = sin(a)

    def __set_normal(self, a, b):
        self.__a = a
        self.__b = b

    def get(self):
        if self.__b == 0:
            return str(self.__a)
        return str(self.__a) + " " + (("+" + str(self.__b)) if self.__b > 0 else str(self.__b)) + " i"

    def mul(self, a):
        ra = self.__a * a.__a - self.__b * a.__b
        rb = self.__a * a.__b + self.__b * a.__a
        return MyComplex(ra, rb)

    def __mul(self, a, b):
        ra = self.__a * a - self.__b * b
        rb = self.__a * b + self.__b * a
        return MyComplex(ra, rb)

    def sum(self, a):
        return MyComplex(self.__a + a.__a, self.__b + a.__b)