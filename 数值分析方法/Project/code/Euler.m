function sys=Euler()
    clear,clc
    y1=10;
    x1=1;
    x2=4;% 其实就是迭代次数，第一问换成7
    h=1;
    N=abs(x2-x1)/h; 
    y=zeros(N+1,1);
    x=zeros(N+1,1);
    y(1)=y1;
    x(1)=x1;
    for i=1: N
        x(i+1)=x1+i*h;
        y(i+1)=y(i)+h*dy( x(i) ,y(i) );
        
    end
    sys(:,1)=x;
    sys(:,2)=y;
    
    draw(x,y)
end
 
function sys=dy(x, y)
    sys=0.592451*y*(1-0.0005*y);%第一问换成0.8
    
 
end
 
function draw(x,y)
    plot(x, y, '-o' , 'linewidth',3)
    xlabel('X')
    ylabel('Y')
    title('The Euler Solution Chart')
end