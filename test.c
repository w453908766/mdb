

int b;
void h(int c){
  b=b+c;
}
void g(int* aa){
  *aa = 10;
}
int f( int a1){
  a1=a1+1;
  g(&a1);
  
  return a1;
}
int main(){
  int a0;
  a0=f(5);
  a0 =5;
  h(a0);
  b = a0;
  return a0;
}
  
