
# class Link:
#     empty=() #仅是标志，可共用
#     def __init__(self,first,rest=empty):
#         assert rest is Link.empty or isinstance(rest,Link)
#         self.first=first
#         self.rest=rest


# def sum_Link(l):
#     # if l.rest==Link.empty: ——Link可以是空！
#     #     return l.first
#     if l is Link.empty:
#         return 0
#     return l.first + sum_Link(l.rest)

# def display_Link(l):
#     str_num=''
#     while l is not Link.empty:
#         if isinstance(l.first,Link):
#             str_num+=display_Link(l.first)
#         else:
#             str_num+=' '+str(l.first)
#         l=l.rest
#     return '<'+str_num+'>'

# def map_Link(l,f):
#     # #递归版本
#     # if l is Link.empty:
#     #     return l
#     # else:
#     #     a=map_Link(l.rest,f)  
#     # return Link(f(l.first),a)

#     #循环版本
#     while l is not Link.empty:
#         l.first=f(l.first)
#         l=l.rest


# l1=Link(1,Link(2,Link(3)))
# map_Link(l1,lambda x: x * x)
# # print(display_Link(l1))

# # a=5
# # sub2=l1
# # while sub2.rest is not Link.empty:
# #     sub2=sub2.rest     #找到最后一个,是空
# # print(sub2)
# # sub2.rest=Link(a) #sub2相当于指针，要改sub2对应的东西
# # # l1.rest=l1.rest.rest
# # print(sub2)
# # print(display_Link(l1))


# l2=Link(19,Link(1,Link(2,Link(3))))
# # map_Link(l2,lambda x:2*x)
# # l=Link(l1,Link(l2))
# # l=Link(l1,l2)
# # print(display_Link(l1))


# def reverse(lnk):
#     """ Reverse a linked list.

#     >>> a = Link(1, Link(2, Link(3)))
#     >>> # Disallow the use of making new Links before calling reverse
#     >>> Link.__init__, hold = lambda *args: print("Do not steal chicken!"), Link.__init__
#     >>> try:
#     ...     r = reverse(a)
#     ... finally:
#     ...     Link.__init__ = hold
#     >>> print(r)
#     <3 2 1>
#     >>> a.first # Make sure you do not change first
#     1
#     """
#     "*** YOUR CODE HERE ***"
#     if lnk is Link.empty or lnk.rest is Link.empty:
#         return lnk
#     p=lnk.rest  
#     p=reverse(p)
#     pointer=p
#     while p.rest is not Link.empty:
#         p=p.rest
#     lnk.rest = Link.empty
#     p.rest= lnk
#     return pointer


# l=Link(1, Link(2, Link(3, Link(4, Link(5)))))
# # r=l.rest
# # l.rest=Link.empty

# # l=Link(1, Link(2, Link(1, Link(1,Link(2,Link(9,Link(10)))))))
# r = reverse(l)
# # print(display_Link(r))
# # print(display_Link(l))
# # print(display_Link(Link(1)))
# # print(display_Link(Link(1,Link(2))))

# class Tree:
#     """
#     >>> t = Tree(3, [Tree(2, [Tree(5)]), Tree(4)])
#     >>> t.label
#     3
#     >>> t.branches[0].label
#     2
#     >>> t.branches[1].is_leaf()
#     True
#     """

#     def __init__(self, label, branches=[]):
#         for b in branches:
#             assert isinstance(b, Tree)
#         self.label = label
#         self.branches = list(branches)

#     def is_leaf(self):
#         return not self.branches

#     def __repr__(self):
#         if self.branches:
#             branch_str = ', ' + repr(self.branches)
#         else:
#             branch_str = ''
#         return 'Tree({0}{1})'.format(self.label, branch_str)

#     def __str__(self):
#         def print_tree(t, indent=0):
#             tree_str = '  ' * indent + str(t.label) + "\n"
#             for b in t.branches:
#                 tree_str += print_tree(b, indent + 1)
#             return tree_str

#         return print_tree(self).rstrip()


# def is_bst(t):
#     """Returns True if the Tree t has the structure of a valid BST.

#     >>> t1 = Tree(6, [Tree(2, [Tree(1), Tree(4)]), Tree(7, [Tree(7), Tree(8)])])
#     >>> is_bst(t1)
#     True
#     >>> t2 = Tree(8, [Tree(2, [Tree(9), Tree(1)]), Tree(3, [Tree(6)]), Tree(5)])
#     >>> is_bst(t2)
#     False
#     >>> t3 = Tree(6, [Tree(2, [Tree(4), Tree(1)]), Tree(7, [Tree(7), Tree(8)])])
#     >>> is_bst(t3)
#     False
#     >>> t4 = Tree(1, [Tree(2, [Tree(3, [Tree(4)])])])
#     >>> is_bst(t4)
#     True
#     >>> t5 = Tree(1, [Tree(0, [Tree(-1, [Tree(-2)])])])
#     >>> is_bst(t5)
#     True
#     >>> t6 = Tree(1, [Tree(4, [Tree(2, [Tree(3)])])])
#     >>> is_bst(t6)
#     True
#     >>> t7 = Tree(2, [Tree(1, [Tree(5)]), Tree(4)])
#     >>> is_bst(t7)
#     False
#     """
#     "*** YOUR CODE HERE ***"
#     def bst_max(b):
#         if b.branches == []:
#             return b.label
#         else:
#             return bst_max(b.branches[-1])

#     def bst_min(b):
#         if b.branches == []:
#             return b.label
#         else:
#             return bst_min(b.branches[0])

#     for b in t.branches:
#         if not is_bst(b):
#             return False
#     if len(t.branches)==0:
#         return True

#     if len(t.branches)==1:                 
#         b=t.branches[0]
#         if  is_bst(b):
#             if b.label >= t.label and bst_min(b)>= t.label:
#                 return True
#             if b.label < t.label and bst_max(b)<=t.label:
#                 return True
#             # if bst_max(b)<=t.label or bst_min(b)>= t.label:
#             #     return True
#         return False

#     else:
#         if bst_max(t.branches[0]) <= t.label and bst_min(t.branches[1]) >= t.label:
#             return True
#         return False

# is_bst(Tree(1,[Tree(6,[Tree(0)])]))
# is_bst(Tree(1, [Tree(2, [Tree(3, [Tree(4)])])]))
class pet:
    n=1
class dog(pet):
    n=2
class doggy(dog):
    def __init__(self):
        pet.__init__(self)
print(doggy().n)