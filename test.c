

int b;
void h(int c){
  b=b+c;
}
int f( int a1){
  a1=a1+1;
  h(a1);
  a1=2;
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
  
