; ModuleID = 'tests/hello_world.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"hello, world!\0A\00", align 1 ; [#uses=1 type=[15 x i8]*]

; [#uses=0]
define i32 @main() {
entry:
  %retval = alloca i32, align 4                   ; [#uses=1 type=i32*]
  %doub = alloca double, align 4
  store i32 0, i32* %retval
  %0 = bitcast double* %doub to i32
  %1 = uitofp i32 %0 to double
  store double %1, double* %doub, align 1
  store double %1, double* %doub, align 2
  store double %1, double* %doub, align 4
  store double %1, double* %doub, align 8
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str, i32 0, i32 0)) ; [#uses=0 type=i32]
  ret i32 1
}

; [#uses=1]
declare i32 @printf(i8*, ...)
