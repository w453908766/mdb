; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@b = common global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define void @h(i32 %c) #0 {
entry:
  %c.addr = alloca i32, align 4
  store i32 %c, i32* %c.addr, align 4
  %0 = load i32, i32* @b, align 4
  %1 = load i32, i32* %c.addr, align 4
  %add = add nsw i32 %0, %1
  store i32 %add, i32* @b, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define void @g(i32* %aa) #0 {
entry:
  %aa.addr = alloca i32*, align 8
  store i32* %aa, i32** %aa.addr, align 8
  %0 = load i32*, i32** %aa.addr, align 8
  store i32 10, i32* %0, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @f(i32 %a1) #0 {
entry:
  %a1.addr = alloca i32, align 4
  store i32 %a1, i32* %a1.addr, align 4
  %0 = load i32, i32* %a1.addr, align 4
  %add = add nsw i32 %0, 1
  store i32 %add, i32* %a1.addr, align 4
  call void @g(i32* %a1.addr)
  %1 = load i32, i32* %a1.addr, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a0 = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  %call = call i32 @f(i32 5)
  store i32 %call, i32* %a0, align 4
  store i32 5, i32* %a0, align 4
  %0 = load i32, i32* %a0, align 4
  call void @h(i32 %0)
  %1 = load i32, i32* %a0, align 4
  store i32 %1, i32* @b, align 4
  %2 = load i32, i32* %a0, align 4
  ret i32 %2
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 5.0.0 (tags/RELEASE_500/final)"}
