clear; 
A=input('请输入线性方程组的系数矩阵:'); 
b=input('请输入线性方程组的常向量:'); 
x1=input('请输入解向量的初始值:'); 
n=numel(b); 
 
e_max=1e6;       %%前一次和后一次之差
while e_max>=1e-6 
    e_max=0; 
    for i=1:n 
        s=0;           %%初始化变量
        for j=1:n 
            if j~=i 

                s=s+A(i,j)*x1(j); 
            end 
        end 
        x2(i) = (b(i)-s)/A(i,i); 
        e = abs(x2(i)-x1(i));     
        if e > e_max  
            e_max = e; 
        end 
    end 
    x1=x2      %%不带分号，观察每步迭代结果 
end 