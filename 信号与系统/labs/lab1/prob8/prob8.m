% prob8.m
clc;
clear;

x=str2sym('exp(i*2*pi*t/16)+exp(i*2*pi*t/8)');
xr=sreal(x); % get the real component of x
xi=simag(x); % get the imaginary component of x

% plot of the real part
ezplot(xr,0,32);

% 画虚部把下面这行注释取消
% ezplot(xi,0,32);