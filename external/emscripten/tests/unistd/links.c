#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main() {
  char* files[] = {"/link", "/file", "/folder"};
  char buffer[256] = {0};

  for (int i = 0; i < sizeof files / sizeof files[0]; i++) {
    printf("readlink(%s)\n", files[i]);
    printf("ret: %d\n", readlink(files[i], buffer, 256));
    printf("errno: %d\n", errno);
    printf("result: %s\n\n", buffer);
    errno = 0;
  }

  printf("symlink/overwrite\n");
  printf("ret: %d\n", symlink("new-nonexistent-path", "/link"));
  printf("errno: %d\n\n", errno);
  errno = 0;

  printf("symlink/normal\n");
  printf("ret: %d\n", symlink("new-nonexistent-path", "/folder/link"));
  printf("errno: %d\n", errno);
  errno = 0;

  printf("readlink(created link)\n");
  printf("ret: %d\n", readlink("/folder/link", buffer, 256));
  printf("errno: %d\n", errno);
  printf("result: %s\n\n", buffer);
  errno = 0;

  printf("readlink(short buffer)\n");
  printf("ret: %d\n", readlink("/link", buffer, 4));
  printf("errno: %d\n", errno);
  printf("result: %s\n", buffer);
  errno = 0;

  return 0;
}
