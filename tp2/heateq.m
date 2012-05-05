function [T,x,y] = heateq(n,Tu,Td,Tl,Tr)

K = spalloc(n^2,n^2,5*n^2);
b = zeros(n^2,1);

h = 1/(n-1);
tic
for f = 2:n-1
    for c = 2:n-1
        K((f-1)*n+c,(f-1)*n+c) = -4/h^2; % centro
        K((f-1)*n+c,(f-2)*n+c) = 1/h^2; % arriba
        K((f-1)*n+c,(f)*n+c) = 1/h^2; % abajo
        K((f-1)*n+c,(f-1)*n+c-1) = 1/h^2; % izquierda
        K((f-1)*n+c,(f-1)*n+c+1) = 1/h^2; % derecha
    end
end
toc

for c = 1:n
    K(c,c) = 1; % borde arriba
    b(c) = Tu;
    
    K((n-1)*n+c,(n-1)*n+c) = 1; % borde abajo
    b((n-1)*n+c) = Td;
end

for f = 2:n-1
    K((f-1)*n+1,(f-1)*n+1) = 1; % borde izquierdo
    b((f-1)*n+1) = Tl;
    
    K((f-1)*n+n,(f-1)*n+n) = 1; % borde derecho
    b((f-1)*n+n) = Tr;
end

figure(1)
spy(K)

tic
T = K\b;
toc

figure(2)
x = linspace(0,1,n);
y = fliplr(linspace(0,1,n));
surf(x,y,reshape(T,n,n)')
view(2)
shading interp
axis image
colorbar

