function resuelve

tic
d=load("dimensiones");
K=load("K.matriz");
b=load("b.vector");
toc

d
n=d(1)
m=d(2)

size(K)

tic
T = K\b;
toc

size(T)

B=reshape(T,m,n)';

size(B)

figure(1)
imagesc(B);
colormap(gray)

%view(2)
