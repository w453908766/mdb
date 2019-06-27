

/*
define i8 @fact(i8 %a, i8 %n){
  %cmp = cmp eq i8 %n, 0
  %mul = mul i8 %a, %n
  %sub = sub i8 %n, 1
  %call = call i8 @fact(i8 %mul, i8 %sub)
  %ret = select i1 %cmp, i8 %a, i8 %call
  ret i8 %ret
}

int fact(int n){
  int result = 1;
  for(int i=0;i<n;i++)
    result=result*(i+1);
  return result;
}
*/




int fact(int n){
  if(n==0)return 1;
  else return n*fact(n-1);
}

int main(int argc, char** argv){
  int f = fact(argc);
  return f;
}

