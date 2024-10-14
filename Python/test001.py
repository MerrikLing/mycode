def multiadder(n):
    # """Return a function that takes N arguments, one at a time, and adds them.
    # >>> f = multiadder(3)
    # >>> f(5)(6)(7) # 5 + 6 + 7
    # 18
    # >>> multiadder(1)(5)
    # 5
    # >>> multiadder(2)(5)(6) # 5 + 6
    # 11
    # >>> multiadder(4)(5)(6)(7)(8) # 5 + 6 + 7 + 8
    # 26
    # >>> from construct_check import check
    # >>> # Make sure multiadder is a pure function.
    # >>> check(HW_SOURCE_FILE, 'multiadder',
    # ...       ['Nonlocal', 'Global'])
    # True
    # """
    "*** YOUR CODE HERE ***"
    list=[0]#
    def helper(n):
        def storeANDreturn(b,n):
            list.append(b)
            return helper(n-1)
        if n==1:
            a=0
            for i in list:
                a+=i
            return lambda x:x+a
        return  lambda b:storeANDreturn(b,n) 
    return helper(n)
# print(multiadder(3)(5)(6)(7))
# print(multiadder(1)(5))
# print(multiadder(2)(5)(6))
# print(multiadder(4)(5)(6)(7)(8))
f=multiadder(7)
print(f(1)(2)(3)(4)(5)(6)(7))


