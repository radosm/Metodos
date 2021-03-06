END {
  n=256
  l=0.1

  for(c=1;c<=n;c++){
    printf("K %d %d %f\n",c,c,1);                     # borde arriba
    printf("K %d %d %f\n",(n-1)*n+c,(n-1)*n+c  ,1);   # borde abajo
  }

  for(f=2;f<n;f++){
    printf("K %d %d %f\n",(f-1)*n+1,(f-1)*n+1,1);     # borde izquierdo
    printf("K %d %d %f\n",(n-1)*n+n,(n-1)*n+n,1);     # borde derecho
  }

  for(f=2;f<n;f++){
    for(c=2;c<n;c++){
        printf("KCEN %d %d %f\n",(f-1)*n+c,(f-1)*n+c  ,4+l);     # centro
        printf("KARR %d %d %f\n",(f-1)*n+c,(f-2)*n+c  ,-1);       # arriba
        printf("KABA %d %d %f\n",(f-1)*n+c,(f)*n+c    ,-1);       # abajo
        printf("KIZQ %d %d %f\n",(f-1)*n+c,(f-1)*n+c-1,-1);       # izquierda
        printf("KDER %d %d %f\n",(f-1)*n+c,(f-1)*n+c+1,-1);       # derecha
    }
  }
}
