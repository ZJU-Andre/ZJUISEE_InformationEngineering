function x=Gauss_Seidel(A,b,x0,ep,N)

%用途：用高斯迭代法解线性方程组Ax=b

%A为系数矩阵，b为右端向量，x0为初始向量（默认零向量）

%ep为精度（1e-6），N为最大迭代次数（默认500次），x返回近似解向量

n=length(b);

if nargin<5

    N=500;

end

if nargin<4

    ep=1e-6;

end

if nargin<3

    x0=zeros(n,1);

end

x=zeros(n,1);

k=0;

while k<N

    for i=1:n

        if i==1

            x(1)=(b(1)-A(1,2:n)*x0(2:n))/A(1,1);

        elseif i==n

                x(n)=(b(n)-A(n,1:n-1)*x(1:n-1))/A(n,n);

        else

                x(i)=(b(i)-A(i,1:i-1)*x(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);

        end

    end

    if norm(x-x0,inf)<ep

        break;

    end

    x0=x;

    %disp('x=');

    %disp(x);可输出中间结果

    k=k+1;

end

if k==N

    Warning('已到达迭代次数上限！');

end

disp(['k=',num2str(k)])
