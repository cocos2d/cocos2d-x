@.str = private constant [15 x i8] c"hello, world!\0A\00", align 1 ; [#uses=1]

define linkonce_odr i32 @main() align 2 {
  %333 = call i32 @printf(i8* getelementptr inbounds ([15 x i8]* @.str, i32 0, i32 0)) ; [#uses=0]
  %199 = trunc i8 1 to i1                        ; [#uses=1]
  br i1 %199, label %label555, label %label569

label555:                                     ; preds = %0
  br label %label569 ; branch should ignore all code after it in the block
                                              ; No predecessors!
  %a472 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %a473 = extractvalue { i8*, i32 } %a472, 0
  %a474 = extractvalue { i8*, i32 } %a472, 1
  br label %label569

label569:                                     ; preds = %0
  br i1 %199, label %label990, label %label999

label990:
  ret i32 0 ; ret should ignore all code after it in the block
                                              ; No predecessors!
  %a472 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %a473 = extractvalue { i8*, i32 } %a472, 0
  %a474 = extractvalue { i8*, i32 } %a472, 1
  br label %label569

label999:                                     ; preds = %555
  ret i32 0
}

declare i32 @printf(i8*)
declare i32 @__gxx_personality_v0(...)

