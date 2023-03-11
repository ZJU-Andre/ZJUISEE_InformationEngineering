clear;
clc;
x=[1 0 1];%nx=0:2
h=[2 0 -2];%nh=-1:1
ny=-1:3;
y=conv(x,h);
stem(ny,y);
%y的时间线是其卷积因子的（上限+上限）~（下限+下限）
