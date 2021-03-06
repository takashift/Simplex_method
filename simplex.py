print("目的関数 > ")
c = raw_imput()
print(c)
print("制約条件の係数 > ")
A = raw_imput()
print(A)
print("制約条件の右辺定数 > ")
b = raw_imput()
print(b)

# c = [-1, -1, -1] # 目的関数
# A = [[1, -1, 2], [2, -3, -1]] # 決定変数の係数
# b = [8, 1]
 
# 決定変数の下限、上限
x0_bounds = (0, None)
x1_bounds = (0, None)
x2_bounds = (0, None)
 
from scipy.optimize import linprog
res = linprog(c, A_eq=A, b_eq=b, bounds=(x0_bounds, x1_bounds, x2_bounds),
              options={"disp": True})
print(res)