function acc=singal_input3(omega_d,t)
t_a=0.2; %加速时间0.2s
a=omega_d*2/t_a;
if t<0.1
    acc=0;
end

if t>=0.1 && t<(0.1+t_a) %加速段
    acc=a/t_a*(0.1+t_a)-a/t_a*t;
end

if t>=(0.1+t_a) && t<=(0.9-t_a) %匀速段
    acc=0;
end

if t>=(0.9-t_a) && t<=0.9 %减速段
    acc=a/t_a*(0.9-t_a)-a/t_a*t;
end

if t>0.9
    acc=0;
end