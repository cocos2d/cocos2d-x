; ModuleID = '/dev/shm/tmp/src.cpp.o'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"hello, %d %d!\0A\00", align 1 ; [#uses=1 type=[15 x i8]*]
@_dispatchTable = internal global i64 0

define i32 @doit(i32 %x, { i32, i32 } %y) {
  %y0 = extractvalue { i32, i32 } %y, 0
  %y1 = extractvalue { i32, i32 } %y, 1
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str, i32 0, i32 0), i32 %y0, i32 %y1) ; [#uses=0 type=i32] [debug line = 5:13]
  ret i32 0
}

define i32 @main() {
entry:
  %retval = alloca i32, align 4                   ; [#uses=1 type=i32*]
  %myi64 = alloca i64, align 4
  %comp = alloca { i32, i32 }, align 4            ; [#uses=1]
  store i32 0, i32* %retval
  br label %cond.end

cond.null:
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi { i32, i32 } [ { i32 5, i32 6 }, %entry ], [ zeroinitializer, %cond.null ] ; [#uses=1]
  store { i32, i32 } %cond, { i32, i32 }* %comp
  %call = call i32 (i32, { i32, i32 })* @doit(i32 1, { i32, i32 } %cond) ;
  store { i32, i32 } { i32 ptrtoint (i64* @_dispatchTable to i32), i32 0 }, { i32, i32 }* getelementptr inbounds ([1 x i64]* @_dispatchTable, i32 0, i32 0, i32 1), align 4
  ret i32 0                             ; [debug line = 6:13]
}

; [#uses=1]
declare i32 @printf(i8*, ...)

