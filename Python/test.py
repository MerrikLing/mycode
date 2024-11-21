class Account:
    """
    >>> a=Account('John')
    >>> a.deposit(100)
    100
    >>> a.withdraw(90)
    10
    >>> a.withdraw(90)
    dreaming!
    """
    def interest():
        return 0.02
    # interest=lambda:0.03
    def __init__(self,account_holder):
        self.balance = 0
        self.holder = account_holder
    def deposit(self,money):
        self.balance += money
        return self.balance
    def withdraw(self,money):
        if money>self.balance:
            return 'dreaming!'
        self.balance-=money
        return self.balance
