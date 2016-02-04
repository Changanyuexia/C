#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TOT_TESTS 100
#define SUCCESS 0
#define ERROR   1
#define WIDTH  40
#define HEIGHT 25
#define FNTFILENAME "fontfiles/m7fixed.fnt"
#define ALTFNTFNAME "fontfiles/trebouchet.fnt"
#define TLTXTOFFSET    0x80
#define FRSTSIXEL      0xA0
#define ONECOLUMN      16
#define GRAPHCHARS     64
#define SPACE_CHAR     32
#define BLOCK_CHAR     0xFF
/* Font stuff */
typedef unsigned short fntrow;

#define FRAMERATE 20
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

enum control {defFont=0x8A,altFont,red=0x81,green,yellow,blue,magenta,cyan,white,singleHeight=0x8C,doubleHeight,
  grRed=0x91,grGreen,grYellow,grBlue,grMagenta,grCyan,grWhite,contiguousG=0x99,separetedG,blackBack=0x9C,newBack,holdG,releaseG,black};

enum sixels {s_one=1,s_two=2,s_three=4,s_four=8,s_five=16,s_six=64};

enum choseFont {defaultFont,alternFont};
enum displayMode {alpha,graph};
enum graphMode {contiguous,separated, hold};

enum charHeight{singleH, doubleH1,doubleH2};
typedef enum charHeight CharHeight;

typedef struct color Color;
struct color{
  int r;
  int g;
  int b;
};

typedef struct charStyle CharStyle;
struct charStyle{
  enum choseFont font;
  Color background;
  Color character;
  Color graphics;
  int ox;
  int oy;
  int holdCnt;
  CharHeight height;
  enum displayMode dMode;
  enum graphMode grMode;
};

enum testMode {silent,verbose};
typedef struct tRes TestResults;
struct tRes{
  int passed;
  int total;
};

unsigned char **fileInput(char *s);
unsigned char **mallocArray(int height ,int width);
void freeArray(unsigned char **A, int height);

TestResults test(int mode);
Color setColor(int clr);
CharStyle setCoordinates(CharStyle style, int x, int y);
void parseForStyle(CharStyle style[HEIGHT][WIDTH], unsigned char **A);
void asignGraphicsStyle(CharStyle *tempStyle, CharStyle style[HEIGHT][WIDTH], unsigned char **A );
void asignAlphaStyle(CharStyle *tempStyle, CharStyle style[HEIGHT][WIDTH], unsigned char code);
void gmodeCheck(CharStyle *style,unsigned char ctrl);
CharHeight changeHeight(unsigned char code);
CharStyle changeGraphStyle(CharStyle style,  unsigned char code);
CharStyle reset(CharStyle style);
void printArray(unsigned char **A);
void SDL(CharStyle style[HEIGHT][WIDTH],unsigned char **A);
void setupSDL(fntrow graphdata[2][FNTCHARS][FNTHEIGHT],fntrow fontdata[FNTCHARS][FNTHEIGHT],fntrow fontA[FNTCHARS][FNTHEIGHT]);
/*void createGraphFont(short graphdata[GRAPHCHARS][3][2]);*/
void decodeSixels(int dots[3][2], int i);
