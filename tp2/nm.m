function nm(imagen,l)

I=imread(imagen);
##I=B(1:7,1:7);

n=size(I)(1);
m=size(I)(2);

for iii = 1:n/10
  for ii = 1:m/10
    I(iii*10,ii*10)=0;
  end
end

K = spalloc(n*m,n*m,5*n*m);
b = zeros(n*m,1);

tic
for f = 2:n-1
    for c = 2:m-1
        K((f-1)*m+c,(f-1)*m+c)   =  4+l;    % centro
        K((f-1)*m+c,(f-2)*m+c)   = -1;      % arriba
        K((f-1)*m+c,(f)*m+c)     = -1;      % abajo
        K((f-1)*m+c,(f-1)*m+c-1) = -1;      % izquierda
        K((f-1)*m+c,(f-1)*m+c+1) = -1;      % derecha
        b((f-1)*m+c)             = l*I(f,c);
    end
end
toc

size(K)
size(b)

for c = 1:m
    K(c,c) = 1; % borde arriba
    b(c) = I(1,c);
    
    K((n-1)*m+c,(n-1)*m+c) = 1; % borde abajo
    b((n-1)*m+c) = I(n,c);
end

size(K)
size(b)

for f = 2:n-1
    K((f-1)*m+1,(f-1)*m+1) = 1; % borde izquierdo
    b((f-1)*m+1) = I(f,1);
    
    K((f-1)*m+m,(f-1)*m+m) = 1; % borde derecho
    b((f-1)*m+m) = I(f,m);
end

size(K)
size(b)

##figure(3)
##spy(K)

tic
T = K\b;
toc

size(T)

B=reshape(T,m,n)';

size(B)

figure(1)
imagesc(I);
colormap(gray)

figure(2)
imagesc(B);
colormap(gray)

view(3)
