%生成目标曲线
clear;clc;
t=[0:0.0005:1.5]';
for x= 1:length(t)
    y(x)=singal_input(4*pi,t(x));
end
simin=[t,y'];

