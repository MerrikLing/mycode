# import this
# print("Hello,the rest of world,ready for my coming?\n")
# a=[1,2,3,4,5,6,7,8,9,10]
# print(a[-1::-1])
def number_of_nine(n):
    """
    >>>number_of_nine(99)
    2
    >>>number_of_nine(919)
    2
    """
    i=0
    while n>0:
        if 9==n%10:
            i=i+1
        n//=10
    return i
print(number_of_nine(99))