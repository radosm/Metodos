END {
a[1]=10;
a[2]=16;
a[3]=20;
a[4]=25;
a[5]=32;
a[6]=40;
a[7]=50;
a[8]=64;
a[9]=80;
a[10]=100;
N=256
for (x=1;x<=10;x++) {
m=(N/a[x])+1
if (m==int(m)) m=m-1; else m=int(m);
print N,a[x],m,a[x]*m,((a[x]*m)-N)*100/N
}
p=50
for (x=1;x<=10;x++) {
j=int(p/(100/a[x]))
print p,a[x],100/a[x],j,j*(100/a[x]),(j+1)*(100/a[x])
}
}
