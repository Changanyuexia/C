#define LOGNAME "test_log.txt"
#define FORMT "--------------------------"
#define FAIL "\x1B[31mFAILED\x1B[0m"
#define PASS "\x1B[32mPASSED\x1B[0m"

#ifdef __STDC_LIB_EXT1__
  char str[26];
  ctime_s(str,sizeof str,&results);
  printf("%s", str);
#endif


int T_gmodeCheck(int mode);
int T_mallocArray(unsigned char **A, int mode);
int T_parseForStyle(unsigned char **A, char *s, int mode);
int T_reset(int mode);
int T_setColor(int mode);
int T_SDL(int mode);
int T_changeHeight(int mode);
int T_isSixel(int mode);
int T_decodeSixels(int mode);
