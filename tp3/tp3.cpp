#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <math.h>
#include "matriz.h"
#include "Coef.h"

using namespace std;

//
// MAIN
//
int main(int argc, char* argv[])
{
  if (argc<3) {
    cerr << "Error, ingrese parametros: archivo_entrada, archivo_salida\n";
    exit(1);
  }

  char *archivo_entrada=argv[1];
  char *archivo_salida=argv[2];

  clock_t inicio, fin;
 
  inicio=clock();

  //
  // Lee datos de entrada
  //
  ifstream f;
  f.open(archivo_entrada);
  assert(f);

  int n;
  Coef m0,ml,mp;
  f >> n >> m0 >> ml >> mp;
  assert(n>0 && m0>0 && ml>0 && mp>0);

  vector<Coef> k(n);
  for(int i=0;i<n;i++){
    f>>k[i];
  }
  vector<int> l(n);
  for(int i=0;i<n;i++){
    f>>l[i];
    assert(l[i]>=0);
  }
  vector<int> p(n);
  for(int i=0;i<n;i++){
    f>>p[i];
    assert(p[i]>=0);
  }
  f.close();

/*
  // Muestra datos de entrada
  cout << "n: "<<n<<" m0: "<<m0<<" ml: "<<ml<<" mp: "<<mp<<endl;
  for(int i=0;i<n;i++){
    cout << k[i] << " ";
  }
  cout << endl;
  for(int i=0;i<n;i++){
    cout << l[i] << " ";
  }
  cout << endl;
  for(int i=0;i<n;i++){
    cout << p[i] << " ";
  }
  cout << endl;
*/

	
/*
	
  //Para test 10
  p[7]+=p[8]+p[9];
  p[8]=0;
  p[9]=0;
  l[7]+=l[8]+l[9];
  l[8]=0;
  l[9]=0;
  p[6]-=6;
  p[7]+=6;


*/
/*
  //para test3:
  for (int i=0;i<50;i++){	
    p[1]--;
    p[0]++;
  }

  for (int i=0;i<50;i++){	
    l[1]--;
    l[0]++;
  }
*/


/*
  // para test 5
p[3]+=p[4];
p[3]=0;
l[3]+=l[4];
l[3]=0;
p[1]=0;
p[2]+=50;
p[1]-=5;
p[2]+=5;
*/


  //Para prueba 20
p[9]+=p[10];
p[10]=0;
l[9]+=l[10];
l[10]=0;
p[9]+=p[11];
p[11]=0;
l[9]+=l[11];
l[11]=0;
p[9]+=p[12];
p[12]=0;
l[9]+=l[12];
l[12]=0;
p[9]+=p[13];
p[13]=0;
l[9]+=l[13];
l[13]=0;
p[9]+=p[14];
p[14]=0;
l[9]+=l[14];
l[14]=0;
p[9]+=p[15];
p[15]=0;
l[9]+=l[15];
l[15]=0;
p[9]+=p[16];
p[16]=0;
l[9]+=l[16];
l[16]=0;
p[9]+=p[17];
p[17]=0;
l[9]+=l[17];
l[17]=0;
p[9]+=p[18];
p[18]=0;
l[9]+=l[18];
l[18]=0;
p[9]+=p[19];
p[19]=0;
l[9]+=l[19];
l[19]=0;
p[9]+=p[20];
p[20]=0;
l[9]+=l[20];
l[20]=0;


  //
  // Arma matriz MK=inv(M)*K
  //
  Matriz MK(n,n);

  for(int i=0;i<n;i++){
    float div=(m0+l[i]*ml+p[i]*mp); // div es el coeficiente de M (M es diagonal)

    // Dividir cada fila de K por div es equivalente a multiplicarla a izq por inv(M)
    if (i>0) {
      MK.sub(i,i-1)=k[i]/div;  
    }
    if (i<n-1) {
      MK.sub(i,i)=(-k[i]-k[i+1])/div;
      MK.sub(i,i+1)=k[i+1]/div;
    } else {
      MK.sub(i,i)=-k[i]/div;
    }
  }

  Matriz Qac;
  Matriz Dant;
  MK.autoval_autovect(Qac,Dant);

/*
  cout << endl;

  cout << MK << endl;

  cout << Qac << endl;

  cout << Dant << endl;
*/
  cout << endl;

  vector<Coef> w(Dant.cantFilas());
  for (int i=0;i<Dant.cantFilas();i++) w[i]=sqrt(-Dant.sub(i,i));
  for (int i=0;i<Dant.cantFilas();i++) cout << "lambda[" << i << "]=" << Dant.sub(i,i) << " / w[" << i << "]=" << w[i] << endl;
  for (int i=0;i<n;i++) cout << "l_fin[" << i << "]=" << l[i] << " / p_fin[" << i << "]=" << p[i] << endl;


  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << endl;
  cout << "Tiempo ejecucion: " << segundos << " segundos." << endl;

  return 0;
}
