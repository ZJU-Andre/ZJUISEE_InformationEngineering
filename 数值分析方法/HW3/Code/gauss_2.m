clear

A=input('输入系数矩阵A：');
b=input('输入b向量（按行向量）：');
B=[A b']; 
n=length(b);
RA=rank(A);
RB=rank(B);
zhica=RB-RA;
if zhica>0,
   disp('请注意：因为RA~=RB，所以此方程组无解.\n')
    return
end

if RA==RB
    if RA==n
       fprintf('请注意：因为RA=RB=%d，所以此方程组有唯一解.\n',n)
       X=zeros(n,1);
       for p=1:n-1
           t=find(abs(B(p:end,p))==max(abs(B(p:end,p))))+p-1;
            if abs(B(t,p))~=abs(B(p,p))
                 l=B(t,:);
                 B(t,:)=B(p,:);
                 B(p,:)=l;
            end  %列主元判断
          
            for k=p+1:n    
                 m= B(k,p)/ B(p,p);
                 B(k,p:n+1)= B(k,p:n+1)-m* B(p,p:n+1);
            end
       end
       %把方程组系数矩阵A化为同解的上三角矩阵
       
       b=B(1:n,n+1);
       A=B(1:n,1:n); 
       X(n)=b(n)/A(n,n);
       for q=n-1:-1:1
          X(q)=(b(q)-sum(A(q,q+1:n)*X(q+1:n)))/A(q,q);
       end
       %从xn至x1逐个求解上三角方程组
      
    else
      disp('请注意：因为RA=RB<n，所以此方程组有无穷多解.')
       return
    end
end
 
disp('方程组的解为：');X