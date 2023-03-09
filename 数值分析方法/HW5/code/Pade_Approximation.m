function PadeApprox=Pade_Approximation(G,r)
error(nargchk(2,2,nargin));
error(nargoutchk(1,1,nargout));
if ~isa(G,'tf') || ~isscalar(G)
    error('Input needs to be a SISO transfer function');
end
if ~isreal(r) || (fix(r)~=r) || (r<1) || (r>n)
    error('Invalid value of reduced model order')
end
[num,den]=tfdata(G,'v');
D_fact=num(1)/den(1);
num=num-D_fact*den;
num1=num(end:-1:1)/den(1);
den1=den(end:-1:1)/den(1);
n=length(den1)-1;
c(1)=num1(1)/den1(1);
for i=2:min(n,2*r)
    c(i)=(num1(i)-sum(den1(2:(i)).*c(end:-1:1)))/den1(1);
end
if (2*r)>n
    for i=n+1:(2*r)
        c(i)=-sum(den1(2:n+1).*c(end:-1:(end-n+1)))/den1(1);
    end
end
%Finding Coefficients
C1=c(repmat((r+1:-1:2),r,1)+repmat((0:(r-1))',1,r));
b=-inv(C1)*c(1:r)';
a(r)=0;
for i=1:r
    a(i)=c(i:-1:1)*b(1:i);
end
b=[1 b(end:-1:1)'];
a=a(end:-1:1);
[a,b]=tfdata(tf(a,b)+D_fact,'v');
b=b.*(abs(b)>1e-6);
a=a.*(abs(a)>1e-6);
PadeApprox=tf(a,b);