; ModuleID = '/tmp/tmpxFUbAg/test_emcc1.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%struct.c_s = type { i8, float, i32 }

@.str = private unnamed_addr constant [12 x i8] c"RESULT: %d\0A\00", align 1

define internal fastcc void @f2(%struct.c_s* noalias nocapture sret %agg.result) nounwind {
  %agg.result.1 = getelementptr inbounds %struct.c_s* %agg.result, i32 0, i32 1
  store float 0.000000e+00, float* %agg.result.1, align 4
  %agg.result.2 = getelementptr inbounds %struct.c_s* %agg.result, i32 0, i32 2
  store i32 43110, i32* %agg.result.2, align 4
  ret void
}

define internal fastcc void @f1(%struct.c_s* nocapture %tp) nounwind {
  %1 = alloca %struct.c_s, align 8
  call fastcc void @f2(%struct.c_s* sret %1)
  %2 = bitcast %struct.c_s* %1 to i96*
  %srcval1 = load i96* %2, align 8
  %3 = and i96 %srcval1, 255
  %4 = icmp eq i96 %3, 0
  br i1 %4, label %5, label %12

; <label>:5                                       ; preds = %0
  %6 = lshr i96 %srcval1, 32
  %7 = trunc i96 %6 to i32
  %8 = bitcast i32 %7 to float
  %9 = getelementptr inbounds %struct.c_s* %tp, i32 0, i32 1
  %10 = load float* %9, align 4
  %11 = fcmp olt float %8, %10
  br i1 %11, label %12, label %14

; <label>:12                                      ; preds = %5, %0
  %13 = bitcast %struct.c_s* %tp to i96*
  store i96 %srcval1, i96* %13, align 4
  br label %14

; <label>:14                                      ; preds = %12, %5
  ret void
}

define i32 @main() nounwind {
  %t = alloca %struct.c_s, align 4
  %1 = getelementptr inbounds %struct.c_s* %t, i32 0, i32 1
  store float 1.000000e+00, float* %1, align 4
  call fastcc void @f1(%struct.c_s* %t)
  %2 = getelementptr inbounds %struct.c_s* %t, i32 0, i32 2
  %3 = load i32* %2, align 4
  %4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0), i32 %3) nounwind
  ret i32 0
}

declare i32 @printf(i8* nocapture, ...) nounwind

