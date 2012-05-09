function martin2(imagen,l)

I=imread(imagen);
##I=B(1:7,1:7);

n=size(I)(1);

for iii = 1:12
  for ii = 1:12
    I(iii*10,ii*10)=0;
  end
end

K = spalloc(n^2,n^2,5*n^2);
b = zeros(n^2,1);

##h = 1/(n-1);
h = 1;
l4=4+l;
tic
for f = 2:n-1
    for c = 2:n-1
        K((f-1)*n+c,(f-1)*n+c)   =  l4;     % centro
        K((f-1)*n+c,(f-2)*n+c)   = -1;      % arriba
        K((f-1)*n+c,(f)*n+c)     = -1;      % abajo
        K((f-1)*n+c,(f-1)*n+c-1) = -1;      % izquierda
        K((f-1)*n+c,(f-1)*n+c+1) = -1;      % derecha
        b((f-1)*n+c)             = l*I(f,c);
    end
end
toc

for c = 1:n
    K(c,c) = 1; % borde arriba
    b(c) = I(1,c);
    
    K((n-1)*n+c,(n-1)*n+c) = 1; % borde abajo
    b((n-1)*n+c) = I(n,c);
end

for f = 2:n-1
    K((f-1)*n+1,(f-1)*n+1) = 1; % borde izquierdo
    b((f-1)*n+1) = I(f,1);
    
    K((f-1)*n+n,(f-1)*n+n) = 1; % borde derecho
    b((f-1)*n+n) = I(f,n);
end

figure(3)
spy(K)

tic
T = K\b;
toc

size(T)

B=reshape(T,n,n)';

size(B)

figure(1)
imagesc(I);
colormap(gray)

figure(2)
imagesc(B);
colormap(gray)

% Con lambda=1
%%l=1
%%tic
%%for f = 2:n-1
    %%for c = 2:n-1
        %%K((f-1)*n+c,(f-1)*n+c)   = 4/h^2 + l;     % centro
        %%b((f-1)*n+c)             = l*I(f,c);
    %%end
%%end
%%toc
%%
%%T = K\b;
%%B=reshape(T,n,n)';
%%
%%figure(3)
%%imagesc(B);
%%colormap(gray)
%%
view(3)
