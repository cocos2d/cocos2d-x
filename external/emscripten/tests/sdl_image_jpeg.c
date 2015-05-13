#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include <emscripten.h>

int testImage(SDL_Surface* screen, const char* fileName) {
  SDL_Surface *image = IMG_Load(fileName);
  if (!image)
  {
     printf("IMG_Load: %s\n", IMG_GetError());
     return 0;
  }
  assert(image->format->BitsPerPixel == 32);
  assert(image->format->BytesPerPixel == 4);
  assert(image->pitch == 4*image->w);
  int result = image->w;

  SDL_BlitSurface (image, NULL, screen, NULL);
  SDL_FreeSurface (image);

  return result;
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_SWSURFACE);

  int result = 0;
  result = testImage(screen, "screenshot.jpeg"); // relative path
  assert(result != 0);
  result |= testImage(screen, "/screenshot.jpeg"); // absolute path
  assert(result != 0);

  SDL_Flip(screen);

  printf("you should see an image.\n");

  SDL_Quit();

  REPORT_RESULT();

  return 0;
}

