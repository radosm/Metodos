#include <stdio.h>

main(){
  FILE *f;
  int c,d,i,j,cant_tok,width,height,maxval;
  char token[1000];
  char I[64][64];
  f=fopen("blond.pgm", "r");

  i=0;
  cant_tok=0;
  while ((c=fgetc(f))!=EOF && cant_tok<4){

    if (c==' ' || c=='\t' || c=='\n' || c=='\r') {  /* Blancos */

      if (i>0) {  /* token != "" */
        cant_tok++;
        if (cant_tok==2) width=atoi(token);
        if (cant_tok==3) height=atoi(token);
        if (cant_tok==4) maxval=atoi(token);
        i=0;
        token[i]='\0';
      }
      continue;
    }

    if (c=='#') { /* Comentario */

      while ((d=fgetc(f))!='\n' && d!= '\r' && d!=EOF);
      if (d==EOF) break;
      continue;
    }
    /* 
     *  ni blanco ni comentario
     */
    token[i++]=c; token[i]='\0';
  }

/*  printf("width=%d height=%d maxval=%d\n",width,height,maxval); 

  i=0;
  while (i<height) {
    fgets(I[i],width,f);
    i++;
  } 
*/

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      I[i][j]=fgetc(f);
    }
  }

  fclose(f);

  printf("P5\n");
  printf("%d\n",width);
  printf("%d\n",height);
  printf("%d\n",maxval);

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      if (j%2) {
        printf("%c",I[i][j]);
      } else {
        printf("%c",0);
      }
    }
  }
  
}

