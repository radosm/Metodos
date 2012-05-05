END {
  n=9
  l=0.1

  for(f=2;f<n;f++){
    for(c=2;c<n;c++){
        printf("K %d %d %f\n",(f-1)*n+c,(f-1)*n+c  ,4+l);     # centro
        printf("K %d %d %f\n",(f-1)*n+c,(f-2)*n+c  ,-1);       # arriba
        printf("K %d %d %f\n",(f-1)*n+c,(f)*n+c    ,-1);       # abajo
        printf("K %d %d %f\n",(f-1)*n+c,(f-1)*n+c-1,-1);       # izquierda
        printf("K %d %d %f\n",(f-1)*n+c,(f-1)*n+c+1,-1);       # derecha
    }
  }

##  for(c=1;c<=n;c++){
    ##printf("K %d %d %f\n",c,c,1);                     # borde arriba
    ##printf("K %d %d %f\n",(n-1)*n+c,(n-1)*n+c  ,1);   # borde abajo
  ##}
##
  ##for(f=2;f<n;f++){
    ##printf("K %d %d %f\n",(f-1)*n+1,(f-1)*n+1,1);     # borde izquierdo
    ##printf("K %d %d %f\n",(n-1)*n+n,(n-1)*n+n,1);     # borde derecho
  ##}
}
