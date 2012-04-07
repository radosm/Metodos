#include <stdio.h>
#include <iostream>

using namespace std;

void modifica(int& x){
x=1;
}

int main(){
int x=0;
modifica(x);
cout << "X=" << x <<"\n";
}
