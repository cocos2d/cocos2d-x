#ifndef prof_h_seen
#define prof_h_seen
#ifdef __cplusplus
extern "C" {
#endif

void monstartup(const char *libname);
void moncleanup(void);

#ifdef __cplusplus
}
#endif
#endif
