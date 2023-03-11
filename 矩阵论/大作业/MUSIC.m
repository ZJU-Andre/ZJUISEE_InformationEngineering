close all;
dd = 0.5;           %阵元间距
N = 8;              %传感器个数
nn = 512;           %快拍数
n = 0:1:nn-1;
fs = 120;           %采样频率
M = 1;              %信源数
snr = 20;           %信噪比
derad = pi/180;     %角度->弧度
radeg = 180/pi;     %弧度->角度
d = 0:dd:(N-1)*dd;

theta = -30 ;
A = exp(-1i*2*pi*d.'*sin(theta*derad));      %方向矢量
S = sin(100*pi*n/fs);
X1 = A*S;                                    %接受矩阵
X = awgn(X1, snr, 'measured');               %加入高斯白噪声
Rxx = 1/nn*(X*X');                           %计算协方差矩阵

%特征值分解 
[V,D] = eig(Rxx);      %计算Rxx的特征值对应的对角阵D和特征向量构成的矩阵EV
EVA = diag(D)';        %diag抽取矩阵对角线元素
[EVA,I] = sort(EVA);   %特征值从小到大排序
EVA = fliplr(EVA);     %特征值左右翻转，从大到小序
V = fliplr(V(:,I));    %对应特征向量排序

%构造MUSIC谱函数
for iang = 1:361
        angle(iang) = (iang-181)/2;
        phim = derad*angle(iang);
        a = exp(-1i*2*pi*d*sin(phim)).';   
        Ew = V(:,M+1:N);                   %取M+1列到N列得到噪声子空间
        P(iang) = 1/(a'*Ew*Ew'*a);
end

%作图
P = abs(P);
Pmax = max(P);
P = 10*log10(P/Pmax);
h = plot(angle,P);
set(h,'Linewidth',2)
xlabel('入射角 (degree)')
ylabel('空间谱 (dB)')
axis([-90 90 -60 0])
set(gca, 'XTick',(-90:10:90))
grid on  
