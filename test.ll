; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@b = common global i32 0, align 4, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define void @fff(i32 %c) #0 !dbg !11 {
entry:
  %c.addr = alloca i32, align 4
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !14, metadata !15), !dbg !16
  %0 = load i32, i32* @b, align 4, !dbg !17
  %1 = load i32, i32* %c.addr, align 4, !dbg !18
  %add = add nsw i32 %0, %1, !dbg !19
  store i32 %add, i32* @b, align 4, !dbg !20
  ret void, !dbg !21
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define void @g(i32 %aa) #0 !dbg !22 {
entry:
  %aa.addr = alloca i32, align 4
  store i32 %aa, i32* %aa.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %aa.addr, metadata !23, metadata !15), !dbg !24
  store i32 3, i32* @b, align 4, !dbg !25
  store i32 10, i32* %aa.addr, align 4, !dbg !26
  %0 = load i32, i32* %aa.addr, align 4, !dbg !27
  call void @fff(i32 %0), !dbg !28
  ret void, !dbg !29
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @f(i32 %a1) #0 !dbg !30 {
entry:
  %a1.addr = alloca i32, align 4
  store i32 %a1, i32* %a1.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %a1.addr, metadata !33, metadata !15), !dbg !34
  %0 = load i32, i32* %a1.addr, align 4, !dbg !35
  %add = add nsw i32 %0, 1, !dbg !36
  store i32 %add, i32* %a1.addr, align 4, !dbg !37
  %1 = load i32, i32* %a1.addr, align 4, !dbg !38
  call void @g(i32 %1), !dbg !39
  store i32 90, i32* @b, align 4, !dbg !40
  %2 = load i32, i32* %a1.addr, align 4, !dbg !41
  ret i32 %2, !dbg !42
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 !dbg !43 {
entry:
  %retval = alloca i32, align 4
  %a0 = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %a0, metadata !46, metadata !15), !dbg !47
  %call = call i32 @f(i32 5), !dbg !48
  store i32 %call, i32* %a0, align 4, !dbg !49
  store i32 5, i32* %a0, align 4, !dbg !50
  %0 = load i32, i32* %a0, align 4, !dbg !51
  call void @fff(i32 %0), !dbg !52
  %1 = load i32, i32* %a0, align 4, !dbg !53
  store i32 %1, i32* @b, align 4, !dbg !54
  ret i32 5, !dbg !55
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!7, !8, !9}
!llvm.ident = !{!10}

!0 = !DIGlobalVariableExpression(var: !1)
!1 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 3, type: !6, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 5.0.0 (tags/RELEASE_500/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5)
!3 = !DIFile(filename: "test.c", directory: "/home/wang/Music/mdb")
!4 = !{}
!5 = !{!0}
!6 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!7 = !{i32 2, !"Dwarf Version", i32 4}
!8 = !{i32 2, !"Debug Info Version", i32 3}
!9 = !{i32 1, !"wchar_size", i32 4}
!10 = !{!"clang version 5.0.0 (tags/RELEASE_500/final)"}
!11 = distinct !DISubprogram(name: "fff", scope: !3, file: !3, line: 4, type: !12, isLocal: false, isDefinition: true, scopeLine: 4, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!12 = !DISubroutineType(types: !13)
!13 = !{null, !6}
!14 = !DILocalVariable(name: "c", arg: 1, scope: !11, file: !3, line: 4, type: !6)
!15 = !DIExpression()
!16 = !DILocation(line: 4, column: 14, scope: !11)
!17 = !DILocation(line: 5, column: 5, scope: !11)
!18 = !DILocation(line: 5, column: 7, scope: !11)
!19 = !DILocation(line: 5, column: 6, scope: !11)
!20 = !DILocation(line: 5, column: 4, scope: !11)
!21 = !DILocation(line: 6, column: 1, scope: !11)
!22 = distinct !DISubprogram(name: "g", scope: !3, file: !3, line: 7, type: !12, isLocal: false, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!23 = !DILocalVariable(name: "aa", arg: 1, scope: !22, file: !3, line: 7, type: !6)
!24 = !DILocation(line: 7, column: 12, scope: !22)
!25 = !DILocation(line: 8, column: 5, scope: !22)
!26 = !DILocation(line: 9, column: 6, scope: !22)
!27 = !DILocation(line: 10, column: 7, scope: !22)
!28 = !DILocation(line: 10, column: 3, scope: !22)
!29 = !DILocation(line: 11, column: 1, scope: !22)
!30 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 12, type: !31, isLocal: false, isDefinition: true, scopeLine: 12, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!31 = !DISubroutineType(types: !32)
!32 = !{!6, !6}
!33 = !DILocalVariable(name: "a1", arg: 1, scope: !30, file: !3, line: 12, type: !6)
!34 = !DILocation(line: 12, column: 12, scope: !30)
!35 = !DILocation(line: 13, column: 6, scope: !30)
!36 = !DILocation(line: 13, column: 8, scope: !30)
!37 = !DILocation(line: 13, column: 5, scope: !30)
!38 = !DILocation(line: 14, column: 5, scope: !30)
!39 = !DILocation(line: 14, column: 3, scope: !30)
!40 = !DILocation(line: 15, column: 5, scope: !30)
!41 = !DILocation(line: 16, column: 10, scope: !30)
!42 = !DILocation(line: 16, column: 3, scope: !30)
!43 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 20, type: !44, isLocal: false, isDefinition: true, scopeLine: 20, isOptimized: false, unit: !2, variables: !4)
!44 = !DISubroutineType(types: !45)
!45 = !{!6}
!46 = !DILocalVariable(name: "a0", scope: !43, file: !3, line: 21, type: !6)
!47 = !DILocation(line: 21, column: 7, scope: !43)
!48 = !DILocation(line: 22, column: 6, scope: !43)
!49 = !DILocation(line: 22, column: 5, scope: !43)
!50 = !DILocation(line: 23, column: 6, scope: !43)
!51 = !DILocation(line: 24, column: 7, scope: !43)
!52 = !DILocation(line: 24, column: 3, scope: !43)
!53 = !DILocation(line: 25, column: 7, scope: !43)
!54 = !DILocation(line: 25, column: 5, scope: !43)
!55 = !DILocation(line: 26, column: 3, scope: !43)
