#include "test.h"
#define TOT_TESTS 100
#define SUCCESS 0
#define ERROR   1
#define WIDTH  40
#define HEIGHT 25
#define FNTFILENAME "m7fixed.fnt"
#define FRSTCNTRLALPHA 0x81
#define LSTCNTRLALPHA  0xAF
#define FRSTCNTRLGRAPH 0x90
#define LSTCNTRLGRAPH 0x9F
#define FRSTSIXEL    160
#define GRAPHCHARS   64
#define SPACE_CHAR 32
/* Font stuff */
typedef unsigned short fntrow;

#define FRAMERATE 20
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

enum control {red=0x81,green,yellow,blue,magenta,cyan,white,singleHeight=0x8C,doubleHeight,
  grRed=0x91,grGreen,grYellow,grBlue,grMagenta,grCyan,grWhite,contiguousG=0x99,separetedG,blackBack=0x9C,newBack,holdG,releaseG,black};

enum sixels {s_one=1,s_two=2,s_three=4,s_four=8,s_five=16,s_six=64};

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
typedef struct pallete Pallete;
struct pallete{
  Color red;
  Color green;
  Color yellow;
  Color magenta;
  Color cyan;
  Color blue;
  Color white;
  Color black;
};

typedef struct charStyle CharStyle;
struct charStyle{
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



TestResults test(char *s, int mode);
Pallete setPallete(void);
int isCntrlGraph(int code);
int isCntrlAlhpa(int code);
int isGraphMode(int code);
int isHeight(int code);
Color setColor(int clr);
CharStyle setCoordinates(CharStyle style, int x, int y);
void parseForStyle(CharStyle style[HEIGHT][WIDTH], unsigned char **A);
CharStyle gmodeCheck(CharStyle style,unsigned char ctrl);
Color changeColor(Color col, unsigned char code);
CharHeight changeHeight(unsigned char code);
CharStyle changeGraphStyle(CharStyle style,  unsigned char code);
CharStyle reset(CharStyle style);
void printArray(unsigned char **A);
void SDL(CharStyle style[HEIGHT][WIDTH],unsigned char **A);
/*void createGraphFont(short graphdata[GRAPHCHARS][3][2]);*/
void decodeSixels(int dots[3][2], int i);
