% prob5b.m
clc;
clear;

n1=-5:9;
n2=-6:9; % the range

z=inline('n>=0'); 
x=z(n1);
y=z(n2)+z(n2+1);

% the input signal
subplot(2,1,1);
stem(n1,x);
xlabel('n');
ylabel('x[n]');
axis([-5 9 -inf inf]);

% the output
subplot(2,1,2);
stem(n2,y);
xlabel('n');
ylabel('y[n]');
axis([-6 9 -inf inf]);