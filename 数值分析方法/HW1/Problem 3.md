## Problem 3

### a.

```matlab
function [r, n] = mul_Newton(x0, eps)
% 牛顿法求解非线性方程组
% 输入参数说明：
% 初始迭代向量：x0
% 迭代精度：eps
%  输出参数说明：
% 解向量：r
% 迭代次数：n
r = x0- myfun(x0)/dmyfun(x0);
n = 1;
tol = 1;
while tol > eps
    x0 = r;
    r = x0 - myfun(x0)/dmyfun(x0);
    tol = norm(r - x0);
    n = n + 1;
    if(n > 100000)
        disp('迭代步数太多，可能不收敛！');
        return;
    end
end
 
function f = myfun(x)
x1 = x(1);
x2 = x(2);
x3 = x(3);
f(1) = 3*x1 - cos(x2*x3) -1/2;
f(2) = x1^2 - 81*(x2 + 0.1) + sin(x3) + 1.06;
f(3) = exp(-x1*x2) + 20*x3 + 1/3*(10*pi - 3);
 
function df =dmyfun(x)
x1 = x(1);
x2 = x(2);
x3 = x(3);
df=[3, x3*sin(x2*x3), x2*sin(x2*x3); 2*x1, -81, cos(x3); -x2*exp(-x1*x2), -x1*exp(-x1*x2), 20];
```

