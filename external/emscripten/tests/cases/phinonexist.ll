; ModuleID = 'tests/hello_world.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"hello, world!\0A\00", align 1 ; [#uses=1 type=[15 x i8]*]

define i32 @main() {
  %retval = alloca i32, align 4
  %a12 = zext i1 1 to i32
  br label %13

; <label>:13                                      ; preds = %13, %1
  %a14 = phi i32 [ %a12, %1 ], [ %a15, %135 ]
  %call0 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str, i32 0, i32 0))
  %a15 = add nsw i32 %a14, 2
  %a16 = icmp eq i32 %a15, 9
  br label %17

; <label>:17                                      ; preds = %1
  ret i32 1
}

; [#uses=1]
declare i32 @printf(i8*, ...)

