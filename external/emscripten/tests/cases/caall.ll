; ModuleID = 'tests/hello_world.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"hello, world!\0A\00", align 1 ; [#uses=1 type=[15 x i8]*]

; [#uses=0]
define i32 @main() {
entry:
  %retval = alloca i32, align 4                   ; [#uses=1 type=i32*]
  store i32 0, i32* %retval
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str, i32 0, i32 0)) ; [#uses=0 type=i32]
  %call12 = call void (i32*)** @_ZNSt3__13mapINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEPFvP6ObjectENS_4lessIS6_EENS4_INS_4pairIKS6_SA_EEEEEixERSE_(i32 10)
  %26 = load void (%class.Object*)** %call12
  ret i32 1
}

define (i32*)** @_ZNSt3__13mapINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEPFvP6ObjectENS_4lessIS6_EENS4_INS_4pairIKS6_SA_EEEEEixERSE_(i32 %x) {
entry:
  %ret = inttoptr i32 0 to (i32*)**
  ret %ret
}

; [#uses=1]
declare i32 @printf(i8*, ...)
