
// Some stuff to patch up an emscripten-sdk build so it can be built natively (see nativize_llvm)

#include <stdio.h>
#include <stdlib.h>

extern "C" {

int *__errno()
{
  static int e = 0;
  return &e;
}

void __assert_func(const char *file, int line, const char *assertt, const char *cond)
{
  printf("assert-func: %s : %d : %s : %s\n", file, line, assertt, cond);
  abort();
}

//struct _reent *_impure_ptr;

}

