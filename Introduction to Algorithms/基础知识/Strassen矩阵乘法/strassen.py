def MergeMatrix(A,B):
    #横向合并
    return [x+y for x,y in zip(A,B)]
def SubMatrix(A,B):
    c1=len(A[0])
    return [[x[i]-y[i] for i in range(c1)] for x,y in zip(A,B)]
def AddMatrix(A,B):
    c1=len(A[0])
    return [[x[i]+y[i] for i in range(c1)] for x,y in zip(A,B)]
def StrassenMatrixMultiply(A,B):
    r1=len(A);c1=len(A[0])
    r2=len(B);c2=len(B[0])
    #递归终止条件
    if r1==1 and c1==1:
        return [[A[0][0]*i for i in x]for x in B]
    if r2==1 and c2==1:
        return [[B[0][0]*i for i in x]for x in A]
    #
    if r1>c1:
        #A按行分块
        A1=[A[i] for i in range(c1)]
        A2=[A[i] for i in range(c1,r1)]
        if r2==c1:#B是方阵则不用分块
            C1=StrassenMatrixMultiply(A1,B)
            C2=StrassenMatrixMultiply(A2,B)
            #拼成一个类似1*2的矩阵
            return C1+C2
        else:#B要按列分块
            B1=[[x[i] for i in range(c1)] for x in B]        
            B2=[[x[i] for i in range(c1,c2)] for x in B]
            C11=StrassenMatrixMultiply(A1,B1)        
            C12=StrassenMatrixMultiply(A1,B2)
            C21=StrassenMatrixMultiply(A2,B1)        
            C22=StrassenMatrixMultiply(A2,B2) 
            #拼成一个类似2*2的矩阵
            return MergeMatrix(C11,C12) + MergeMatrix(C21,C22)
       
    if r1<c1:
        #A按列分块,则B必须分块，且按行分块
        A1=[[x[i] for i in range(r1)] for x in A]        
        A2=[[x[i] for i in range(r1,c1)] for x in A]
        B1=[B[i] for i in range(r1)]
        B2=[B[i] for i in range(r1,r2)]
        C1=StrassenMatrixMultiply(A1,B1)        
        C2=StrassenMatrixMultiply(A2,B2)
        #拼成一个1*1的矩阵,矩阵加法
        return AddMatrix(C1,C2)
    if r1==c1:
        if c2 != r2 or c1%2==1:
            #B按行分块，      因为行数必定大于列数 狗屁！
        #     B1=[B[i] for i in range(c1)]
        #     B2=[B[i] for i in range(c1,r2)]
        #     return StrassenMatrixMultiply(A,B1)+StrassenMatrixMultiply(A,B2)
        # if c2
        #现在B终于也是方阵！距离实现Srassen核心算法还有一步，行数必须变成偶数
        # if c1%2==1:
            #其实是有相应的strassen算法，但这里我懒得实现。
            #使用分块，A分成四块，B分为两块
            A1=[[A[x][i] for i in range(r1-1)]for x in range(r1-1)]
            A2=[[x[r1-1]] for x in A]
            A3=[[A[r1-1][i] for i in range(r1-1)]]
            A4=[[A[r1-1][r1-1]]]
            B1=B[:r1-1];B2=[B[r1-1]]
            M1=StrassenMatrixMultiply(A1,B1)
            M2=StrassenMatrixMultiply(A2,B2)
            M3=StrassenMatrixMultiply(A3,B1)
            M4=StrassenMatrixMultiply(A4,B2)
            C1=AddMatrix(M1,M2)
            C2=AddMatrix(M3,M4)
            return C1+C2
        #Now,Strassen Start!!
        A11=[[A[x][i] for i in range(r1//2)]for x in range(r1//2)]
        A12=[[A[x][i] for i in range(r1//2,r1)]for x in range(r1//2)]
        A21=[[A[x][i] for i in range(r1//2)]for x in range(r1//2,r1)]
        A22=[[A[x][i] for i in range(r1//2,r1)]for x in range(r1//2,r1)]
        B11=[[B[x][i] for i in range(r1//2)]for x in range(r1//2)]
        B12=[[B[x][i] for i in range(r1//2,r1)]for x in range(r1//2)]
        B21=[[B[x][i] for i in range(r1//2)]for x in range(r1//2,r1)]
        B22=[[B[x][i] for i in range(r1//2,r1)]for x in range(r1//2,r1)]
        S1=SubMatrix(B12,B22);S2=AddMatrix(A11,A12);S3=AddMatrix(A21,A22)
        S4=SubMatrix(B21,B11);S5=AddMatrix(A11,A22);S6=AddMatrix(B11,B22)
        S7=SubMatrix(A12,A22);S8=AddMatrix(B21,B22)
        S9=SubMatrix(A11,A21);S10=AddMatrix(B11,B12)
        P1=StrassenMatrixMultiply(A11,S1)
        P2=StrassenMatrixMultiply(S2,B22)
        P3=StrassenMatrixMultiply(S3,B11)
        P4=StrassenMatrixMultiply(A22,S4)
        P5=StrassenMatrixMultiply(S5,S6)
        P6=StrassenMatrixMultiply(S7,S8)
        P7=StrassenMatrixMultiply(S9,S10)
        C11=AddMatrix(SubMatrix(AddMatrix(P5,P4),P2),P6)#C11=P5+P4-P2+P6
        C12=AddMatrix(P1,P2)
        C21=AddMatrix(P3,P4)
        C22=SubMatrix(SubMatrix(AddMatrix(P5,P1),P3),P7)#C22=P5+P1-P3-P7
        return MergeMatrix(C11,C12) + MergeMatrix(C21,C22)
    #方阵

def display(x):
    for i in x:
        print(i)
    print('\n')   
def main():
    while(1):
        input_list=input("请输入第一个矩阵大小（先行后列，空格隔开）：").split()
        input_list2=input("请输入第二个矩阵大小（先行后列，空格隔开）：").split()
        r1=int(input_list[0]);c1=int(input_list[1])
        r2=int(input_list2[0]);c2=int(input_list2[1])
        if c1==r2:break
        else: 
            print("输入错误！第一个矩阵列数不等于第二个矩阵行数\n\n请重新输入")
    matrix1=[];matrix2=[]
    for i in range(r1):
        # print("请输入第一个矩阵第{}行元素".format(i))
        matrix1.append([int(x) for x in \
            input("请输入第一个矩阵第{}行{}个元素".format(i+1,c1)).split()])
    for i in range(r2):
        matrix2.append([int(x) for x in \
            input("请输入第二个矩阵第{}行{}个元素".format(i+1,c2)).split()])
    print("相乘结果为：")
    display(StrassenMatrixMultiply(matrix1,matrix2))
    # display(matrix1);display(matrix2)
    # print(r1,c1,r2,c2)
main()
# str=float(input("输入一个浮点数: "))
# print(str)