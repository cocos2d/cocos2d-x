#ifndef _GLESREF_H_
#define _GLESREF_H_

int GLES_Init();
void GLES_UnInit();
int GLES_Draw();

void gles_CaptureScreen();
void *gles_GetScreenData();
int gles_GetScreenWidth();
int gles_GetScreenHeight();

#endif