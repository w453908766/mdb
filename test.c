

int b;
void fff(int c){
  b=b+c;
}
void g(int aa){
  b = 3;
  aa = 10;
  fff(aa);
}
int f( int a1){
  a1=a1+1;
  g(a1);
  b = 90;
  return a1;
}


int main(){
  int a0;
  a0=f(5);
  a0 =5;
  fff(a0);
  b = a0;
  return 5;
}
  
