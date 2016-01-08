#define SUCCESS 0
#define ERROR   1
#define WIDTH  40
#define HEIGHT 25
#define FNTFILENAME "m7fixed.fnt"
#define FRSTCNTRLALPHA 129
#define LSTCNTRLALPHA  143
#define FRSTCNTRLGRAPH 144
#define LSTCNTRLGRAPH 159
#define FRSTSIXEL    160
#define GRAPHCHARS   64
#define SPACE_CHAR 32+128
/* Font stuff */
typedef unsigned short fntrow;


#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

enum control {red=129,green,yellow,blue,magenta,cyan,white,singleHeight=140,doubleHeight,
  grRed=145,grGreen,grYellow,grBlue,grMagenta,grCyan,grWhite,contiguousG=153,separetedG,blackBack=156,newBack,holdG};

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

unsigned char **fileInput(char *s);
unsigned char **mallocArray(int width ,int height);

void parseForStyle(CharStyle style[HEIGHT][WIDTH], unsigned char **A);
CharStyle gmodeCheck(CharStyle style,unsigned char ctrl);
Color changeColor(Color col, unsigned char code);
CharHeight changeHeight(unsigned char code);
CharStyle changeGraphStyle(CharStyle style,  unsigned char code);
void defaultStyle(CharStyle style[HEIGHT][WIDTH]);
CharStyle reset(CharStyle style);
void printArray(unsigned char **A);
void SDL(CharStyle style[HEIGHT][WIDTH],unsigned char **A);
/*void createGraphFont(short graphdata[GRAPHCHARS][3][2]);*/
void decodeSixels(int dots[3][2], int i);
