from fractions import Fraction
x.numerator   #分子
x.denominator #分母
Fraction(4,3)     #传入分子分母构造
Fraction(3.5)     #传入浮点数
Fraction('11/13') #传入字符串
#支持各种运算符，与int运算得Fraction，与float运算得float
#能够自动约分
#常数大，能用整数算出来的先用整数算再转分数