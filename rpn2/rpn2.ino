#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define EEPROM_ADDRESS 0x54
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int ROW_NUM = 6;
const int COLUMN_NUM = 4;

String KEYMAP[] = {
  "0", "1", "2", "3",
  "4", "5", "6", "7",
  "8", "9", "A", "B",
  "C", "D", "E", "F",
  "+", "-", "*", "/",
  "RUN", ".", " ", "Shift",

  "G", "I", "K", "M",
  "O", "Q", "S", "U",
  "W", "Y", "_", "=",
  "<", "(", "#", "ASK",
  "AND", "XOR", "^", String((char) 0xe3),
  "BS", "!", "LD", "Shift",

  "H", "J", "L", "N",
  "P", "R", "T", "V",
  "X", "Z", "RND", ":",
  ">", ")", "FRT", "PRT",
  "OR", "NOT", "%", "e",
  "DBG", "?", "ST", "Shift"
};

const char blkE[] PROGMEM  ="";
const char blk0[] PROGMEM  ="Welcome on the K1284 operating system userguide authored by    Benjamin Bercy";
const char blk1[] PROGMEM  ="0-7:Index            8-128:Documentation  128-255:User Blocks  256:Volatile Block";
const char blk2[] PROGMEM  ="8:+ 9:- 10:* 11:/    12:E/ 13:% 14:^      15:= 16:> 17:<       18:NOT 19:OR 20:XOR  21:AND 22:LD 23:ST   24:PRT 25:ASK 26:RND";
const char blk3[] PROGMEM  ="27:FRT 28:DUP 29:SWP 30:RLL 31:POP 32:OVR 33:CLK 34:IF 35:JMP  36:COS 37:SIN 38:TAN 39:ACOS 40:ASIN      41:ATAN 42:\xe3 43:e ";
const char blk4[] PROGMEM  ="44:LN 45:LOG 46:ROOT 47:ABS 48:INT 49:DEC 50:SIGN 51:BEEP      52:RUN 53:ED 54:DEL  55:CPY 56:DRW 57:PLT 58:CLS 59:SLOAD";
const char blk5[] PROGMEM  ="60:SSEND";
const char blk6[] PROGMEM  ="";
const char blk7[] PROGMEM  ="";
const char blk8[] PROGMEM  ="+: Add               A B + \x10 C            F F \x10 F              C = B + A";
const char blk9[] PROGMEM  ="-: Substract         A B - \x10 C            F F \x10 F              C = B - A";
const char blk10[] PROGMEM ="*: Multiply          A B * \x10 C            F F \x10 F              C = B x A";
const char blk11[] PROGMEM ="/: Divide            A B / \x10 C            F F \x10 F              C = B / A";
const char blk12[] PROGMEM ="E/: Euclidian Divide A B E/ \x10 C           I I \x10 I              C = B euclidian / A";
const char blk13[] PROGMEM ="%: Modulo            A B % \x10 C            I I \x10 I              C = B % A";
const char blk14[] PROGMEM ="^: Exponent          A B ^ \x10 C            F F \x10 F              C = B ^ A";
const char blk15[] PROGMEM ="=: Equals            A B = \x10 C            A A \x10 B              C = B == A";
const char blk16[] PROGMEM =">: Greater Than      A B > \x10 C            F F \x10 B              C = B > A";
const char blk17[] PROGMEM ="<: Lower Than        A B < \x10 C            F F \x10 B              C = B < A";
const char blk18[] PROGMEM ="NOT: Not             A NOT \x10 B            B \x10 B                B = ! A";
const char blk19[] PROGMEM ="OR: Or               A B OR \x10 C           B B \x10 B              C = A or B";
const char blk20[] PROGMEM ="XOR: Exclusive Or    A B XOR \x10 C          B B \x10 B              C = A xor B";
const char blk21[] PROGMEM ="AND: And             A B AND \x10 C          B B \x10 B              C = A and B";
const char blk22[] PROGMEM ="LD: Load Variable    A LD \x10 B             C \x10 A                B = load A";
const char blk23[] PROGMEM ="ST: Store Variable   A B ST \x10 \xed           A C \x10 \xed              store A in B";
const char blk24[] PROGMEM ="PRT: Print           A PRT \x10 \xed            A \x10 \xed                print A";
const char blk25[] PROGMEM ="ASK: Ask Value       A ASK \x10 B            A \x10 A                print A              B = input";
const char blk26[] PROGMEM ="RND: Random          A B RND \x10 C          I I \x10 I              C = rand with        B < C < A";
const char blk27[] PROGMEM ="FRT: Format          A B FRT \x10 C          A S \x10 S              C = B replace        # with A";
const char blk28[] PROGMEM ="DUP: Duplicate       A DUP \x10 A A          A \x10 A A              duplicates top";
const char blk29[] PROGMEM ="SWP: Swap            A B SWP \x10 B A        A A \x10 A A            swap top and previous";
const char blk30[] PROGMEM ="RLL: Roll            A B ~ C RLL \x10 B ~ C AA ~ A \x10 A ~ A        roll stack";
const char blk31[] PROGMEM ="POP: Pop             A POP \x10 \xed            A \x10 \xed                pop top";
const char blk32[] PROGMEM ="OVR: Over            A B OVR \x10 A B A      A A \x10 A A A          duplicates previous  to top";
const char blk33[] PROGMEM ="CLK: Clock           CLK \x10 A              \xed \x10 F                A = timestamp        seconds.millis";
const char blk34[] PROGMEM ="IF: If               A IF B \x10 \xed           B A \x10 A or \xed         If A do B";
const char blk35[] PROGMEM ="JMP: Jump            A JMP \x10 \xed            I \x10 \xed                Jump to instruction I";
const char blk36[] PROGMEM ="COS: Cosinus         A COS \x10 B            F \x10 F                B = cos(A)";
const char blk37[] PROGMEM ="SIN: Sinus           A SIN \x10 B            F \x10 F                B = sin(A)";
const char blk38[] PROGMEM ="TAN: Tangent         A TAN \x10 B            F \x10 F                B = tan(A)";
const char blk39[] PROGMEM ="ACOS: Arc Cosinus    A ACOS \x10 B           F \x10 F                B = acos(A)";
const char blk40[] PROGMEM ="ASIN: Arc Sinus      A ASIN \x10 B           F \x10 F                B = asin(A)";
const char blk41[] PROGMEM ="ATAN: Arc Tangent    A ATAN \x10 B           F \x10 F                B = atan(A)";
const char blk42[] PROGMEM ="\xe3: \xe3 Number          \xe3 \x10 A                \xed \x10 F                A = \xe3";
const char blk43[] PROGMEM ="e: e Number          e \x10 A                \xed \x10 F                   A = e";
const char blk44[] PROGMEM ="LN: Neperian Log     A LN \x10 B             F \x10 F                B = ln(A)";
const char blk45[] PROGMEM ="LOG: Logarithm       A B LOG \x10 C          F F \x10 F              C = B Log(A)";
const char blk46[] PROGMEM ="ROOT: Root           A B ROOT \x10 C         F F \x10 F              C = A root(B)";
const char blk47[] PROGMEM ="ABS: Absolute        A ABS \x10 B            F \x10 F                B = |A|";
const char blk48[] PROGMEM ="INT: To Integer      A INT \x10 B            F \x10 I                B = Integer part of A";
const char blk49[] PROGMEM ="DEC: Get Decimals    A DEC \x10 B            F \x10 F                B = Decimal part of A";
const char blk50[] PROGMEM ="SIGN: Sign           A SIGN \x10 B           F \x10 I                B = sign of A";
const char blk51[] PROGMEM ="BEEP: Sound GeneratorA B BEEP \x10 \xed         I I \x10 \xed              \x0e Beep tone B during A  itterations";
const char blk52[] PROGMEM ="RUN: Run Block       A RUN \x10 \xed            Blk \x10 \xed              Run block A";
const char blk53[] PROGMEM ="ED: Edit Block       A ED \x10 \xed             Blk \x10 \xed              Edit or Display block A";
const char blk54[] PROGMEM ="DEL: Delete Block    A DEL \x10 \xed            Blk \x10 \xed              Delete block A";
const char blk55[] PROGMEM ="CPY: Copy Block      A B CPY \x10 \xed          Blk Blk \x10 \xed          Copy block B in      block A";
const char blk56[] PROGMEM ="DRW: Draw            A B DRW \x10 \xed          I I \x10 \xed              Draw 24bit pattern A to line B";
const char blk57[] PROGMEM ="PLT: Plot            A B PLT \x10 \xed          F I \x10 \xed              Plot 0 \x18 to 24 \x19     value to line B";
const char blk58[] PROGMEM ="CLS: Clear           CLS \x10 \xed              \xed \x10 \xed                Clear window";
const char blk59[] PROGMEM ="SLOAD: Serial Load   A SLOAD \x10 \xed          Blk \x10 \xed              Receive Block A by   Serial link";
const char blk60[] PROGMEM ="SSEND: Serial Send   A SSEND \x10 \xed          Blk \x10 \xed              Send Block A by      Serial link";

const char *const  documentation[] PROGMEM = {blk0 ,
                                              blk1 ,blk2 ,blk3 ,blk4 ,blk5 ,blk6 ,blk7 ,blk8 ,blk9 ,blk10,
                                              blk11,blk12,blk13,blk14,blk15,blk16,blk17,blk18,blk19,blk20,
                                              blk21,blk22,blk23,blk24,blk25,blk26,blk27,blk28,blk29,blk30,
                                              blk31,blk32,blk33,blk34,blk35,blk36,blk37,blk38,blk39,blk40,
                                              blk41,blk42,blk43,blk44,blk45,blk46,blk47,blk48,blk49,blk50,
                                              blk51,blk52,blk53,blk54,blk55,blk56,blk57,blk58,blk59,blk60,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,
                                              blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE ,blkE};

byte pin_rows[ROW_NUM] = { 24, 25, 26, 27, 28, 29 };
byte pin_cols[COLUMN_NUM] = { 15, 14, 13, 12 };
byte pin_state[5] = { 3, 4, 2, 1, 0 };
byte pin_tone = 18;
byte NUM_KEYS = 24;
byte state = 0;
String console = "";
String output = "";
String error = "";

bool flagError = true;
String mode = "run";

String prog[64];
int op = 0;
String variables[27];
String stack[8];
byte sp = 0;
int blkp = 256;
String blk256 = String();

inline float strToFloat(String str) {
  if (str.length() > 20) {
    emitError("OverFlow");
    return 0;
  }
  char buffer[20];
  str.toCharArray(buffer, 20);
  return atof(buffer);
}

inline long strToInt(String str) {
  if (str.length() > 20) {
    emitError("OverFlow");
    return 0;
  }
  char buffer[20];
  str.toCharArray(buffer, 20);
  return atoi(buffer);
}

inline String intToStr(long in) {
  char buffer[20];
  itoa(in,buffer,20);
  String result = String(buffer);
  result.trim();
  return result;
}

inline String floatToStr(float f ) {
  char buffer[20];
  dtostrf(f,14,4,buffer);
  String result = String(buffer);
  result.trim();
  return result;
}

void add() {
  if (sp < 2) {
    emitError("Error on +");
    return;
  }
  String result = floatToStr(strToFloat(stack[sp - 1]) + strToFloat(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void sub() {
  if (sp < 2) {
    emitError("Error on -");
    return;
  }
  String result = floatToStr(strToFloat(stack[sp - 1]) - strToFloat(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void mul() {
  if (sp < 2) {
    emitError("Error on *");
    return;
  }
  String result = floatToStr(strToFloat(stack[sp - 1]) * strToFloat(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void div() {
  if (sp < 2) {
    emitError("Error on /");
    return;
  }
  String result = floatToStr(strToFloat(stack[sp - 1]) / strToFloat(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void ediv() {
  if (sp < 2) {
    emitError("Error on E/");
    return;
  }
  String result = intToStr(strToInt(stack[sp - 1]) / strToInt(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void mod() {
  if (sp < 2) {
    emitError("Error on %");
    return;
  }
  String result = intToStr(strToInt(stack[sp - 1]) % strToInt(stack[sp - 2]));
  pop();
  pop();
  push(result);
}
void exp() {
  if (sp < 2) {
    emitError("Error on ^");
    return;
  }
  String result = floatToStr(pow(strToFloat(stack[sp - 1]), strToFloat(stack[sp - 2])));
  pop();
  pop();
  push(result);
}
void eq() {
  if (sp < 2) {
    emitError("Error on =");
    return;
  }
  bool result = stack[sp - 1].equals(stack[sp - 2]) || strToFloat(stack[sp - 1]) == strToFloat(stack[sp - 2]);
  pop();
  pop();
  push(boolstr(result));
}
void gt() {
  if (sp < 2) {
    emitError("Error on >");
    return;
  }
  bool result = strToFloat(stack[sp - 1]) > strToFloat(stack[sp - 2]);
  pop();
  pop();
  push(boolstr(result));
}
void lt() {
  if (sp < 2) {
    emitError("Error on <");
    return;
  }
  bool result = strToFloat(stack[sp - 1]) < strToFloat(stack[sp - 2]);
  pop();
  pop();
  push(boolstr(result));
}
void lnot() {
  if (sp < 2) {
    emitError("Error on NOT");
    return;
  }
  bool result = !stack[sp - 1].equals("true");
  pop();
  push(boolstr(result));
}
void lor() {
  if (sp < 2) {
    emitError("Error on OR");
    return;
  }
  bool result = stack[sp - 1].equals("true") || stack[sp - 2].equals("true");
  pop();
  pop();
  push(boolstr(result));
}
void lxor() {
  if (sp < 2) {
    emitError("Error on XOR");
    return;
  }
  bool result = !stack[sp - 1].equals("true") != !stack[sp - 2].equals("true");
  pop();
  pop();
  push(boolstr(result));
}
void land() {
  if (sp < 2) {
    emitError("Error on AND");
    return;
  }
  bool result = stack[sp - 1].equals("true") && stack[sp - 2].equals("true");
  pop();
  pop();
  push(boolstr(result));
}
String boolstr(bool value) {
  if (value) {
    return "true";
  } else {
    return "false";
  }
}
void load() {
  if (sp < 1 || stack[sp - 1].charAt(0) - 'A' < 0 || stack[sp - 1].charAt(0) - 'A' > 25) {
    emitError("Error on LD");
    return;
  }
  String result = variables[stack[sp - 1].charAt(0) - 'A'];
  pop();
  push(result);
}
void store() {
  if (sp < 2 || stack[sp - 1].charAt(0) - 'A' < 0 || stack[sp - 1].charAt(0) - 'A' > 25) {
    emitError("Error on ST");
    return;
  }
  variables[stack[sp - 1].charAt(0) - 'A'] = stack[sp - 2];
  String result = stack[sp - 2];
  pop();
  pop();
  push(result);
}

String prepareStr(String str) {
  str.replace('_', ' ');
  str.trim();
  char first = str.charAt(0);
  str.toLowerCase();
  String result = String(first) + str.substring(1, str.length());
  return result;
}
void print() {
  if (sp < 1) {
    emitError("Error on PRT");
    return;
  }
  String toprint = String(stack[sp - 1]);
  printout(prepareStr(toprint));
  String result = stack[sp - 1];
  pop();
  push(result);
}
void ask() {
  if (sp < 1) {
    emitError("Error on ASK");
    return;
  }
  String toprint = String(stack[sp - 1]);
  printout(prepareStr(toprint));
}

void finish_ask(String input) {
  String result = String(input);
  console = "";
  pop();
  push(result);
}

void rnd() {
  if (sp < 2) {
    emitError("Error on RND");
    return;
  }
  String result = intToStr(random(strToInt(stack[sp - 1]), strToInt(stack[sp - 2])));
  pop();
  pop();
  push(result);
}
void format() {
  if (sp < 2) {
    emitError("Error on FRT");
    return;
  }
  stack[sp - 1].replace("#", stack[sp - 2]);
  String result = stack[sp - 1];
  pop();
  push(result);
}
void dup() {
  if (sp < 1) {
    emitError("Error on DUP");
    return;
  }
  push(stack[sp - 1]);
}
void swap() {
  if (sp < 2) {
    emitError("Error on SWP");
    return;
  }
  String tmp = stack[sp - 1];
  stack[sp - 1] = stack[sp - 2];
  stack[sp - 2] = tmp;
}
void roll() {
  if (sp < 2) {
    emitError("Error on RLL");
    return;
  }
  String tmp = stack[0];
  for (int i = 0; i < sp - 1; i++) {
    stack[i] = stack[i + 1];
  }
  stack[sp - 1] = tmp;
}
void pop() {
  if (sp < 1) {
    emitError("Error on POP");
    return;
  }
  sp--;
}
void over() {
  if (sp < 2 || sp > 7) {
    emitError("Error on OVR");
    return;
  }
  push(stack[sp - 2]);
}
void clock() {
  if (sp > 7) {
    emitError("Error on CLK");
    return;
  }
  long time = millis();
  long seconds = time / 1000;
  long subseconds = time % 1000;
  double timestamp = seconds + (subseconds * 0.001);
  push(floatToStr(timestamp));
}

void ifelse() {
  if (sp < 3) {
    emitError("Error on IF");
    return;
  }
  String result = "";
  if (stack[sp - 1].equals("false")) {
    op++;
  }
  pop();
}

void jmp() {
  if (sp < 1) {
    emitError("Error on JMP");
    return;
  }
  op = strToInt(stack[sp - 1]) - 1;
  pop();
}

void tcos() {
  if (sp < 1) {
    emitError("Error on COS");
    return;
  }
  String result = floatToStr(cos(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void tsin() {
  if (sp < 1) {
    emitError("Error on SIN");
    return;
  }
  String result = floatToStr(sin(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void ttan() {
  if (sp < 1) {
    emitError("Error on TAN");
    return;
  }
  String result = floatToStr(tan(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void tacos() {
  if (sp < 1) {
    emitError("Error on ACOS");
    return;
  }
  String result = floatToStr(acos(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void tasin() {
  if (sp < 1) {
    emitError("Error on ASIN");
    return;
  }
  String result = floatToStr(asin(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void tatan() {
  if (sp < 1) {
    emitError("Error on ASIN");
    return;
  }
  String result = floatToStr(atan(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void numpi() {
  if (sp > 7) {
    emitError("S.Overflow");
    return;
  }
  push("3.1416");
}
void nume() {
  if (sp > 7) {
    emitError("S.Overflow");
    return;
  }
  push("2.7183");
}
void aln() {
  if (sp < 1) {
    emitError("Error on LN");
    return;
  }
  String result = floatToStr(log(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void alog() {
  if (sp < 2) {
    emitError("Error on LOG");
    return;
  }
  String result = floatToStr(log(strToFloat(stack[sp - 1])) / log(strToFloat(stack[sp - 2])));
  pop();
  pop();
  push(result);
}
void aroot() {
  if (sp < 2) {
    emitError("Error on ROOT");
    return;
  }
  String result = floatToStr(pow(strToFloat(stack[sp - 1]), 1.0 / strToFloat(stack[sp - 2])));
  pop();
  pop();
  push(result);
}
void aabs() {
  if (sp < 1) {
    emitError("Error on ABS");
    return;
  }
  String result = floatToStr(abs(strToFloat(stack[sp - 1])));
  pop();
  push(result);
}
void aint() {
  if (sp < 1) {
    emitError("Error on INT");
    return;
  }
  String result = intToStr(strToInt(stack[sp - 1]));
  pop();
  push(result);
}
void adec() {
  if (sp < 1) {
    emitError("Error on DEC");
    return;
  }
  String result = floatToStr(strToFloat(stack[sp - 1]) - strToInt(stack[sp - 1]));
  pop();
  push(result);
}
void asign() {
  if (sp < 1) {
    emitError("Error on SIGN");
    return;
  }
  double v = strToFloat(stack[sp - 1]);
  pop();
  if (v > 0) {
    push("1");
  } else if (v < 0) {
    push("-1");
  } else {
    push("0");
  }
}
void beep() {
  if (sp < 2) {
    emitError("Error on BEEP");
    return;
  }
  int f = strToInt(stack[sp-1]);
  int d = strToInt(stack[sp-2]);
  pop();
  pop();
  buzz(f,d);
}
void run() {
  if (sp < 1) {
    emitError("Error on RUN");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  pop();
  blkp=blk;
  parse(readblk(blk));
  console = "";
  printout("Running BLK : "+blktoString(blk));
  op = -1;
}
void edit() {
  if (sp < 1) {
    emitError("Error on EDIT");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  pop();
  blkp=blk;
  mode = "edt";
  console = readblk(blk);
  output = "";
  op = 0;
  sp = 0;
}
void del() {
  if (sp < 1) {
    emitError("Error on DEL");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  printout("Del BLK : "+ blktoString(blk) + " " + (char) 16+ " "+ (char) 0x06) ;
  pop();
  blkp=blk;
  writeblk(blk,"");
}
void cpy() {
  if (sp < 2) {
    emitError("Error on CPY");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  int dest = strToInt(stack[sp-2]);
  printout("Copy BLK : "+ blktoString(blk) +(char) 16 + blktoString(dest));
  pop();
  pop();
  blkp=dest;
  writeblk(dest,readblk(blk));
}

void draw() {
  if (sp < 2) {
    emitError("Error on D");
    return;
  }
  int y = strToInt(stack[sp-1]) % 126;
  int pixels = strToInt(stack[sp-2]);
  for (int x =0; x < 24; x++) {
    if (pixels & 1L<<x) {
      display.drawPixel(y,x+38,SSD1306_WHITE);
    } else {
      display.drawPixel(y,x+38,SSD1306_BLACK);
    }
  }
  pop();
  pop();
}

void plot() {
  static int lastX=38;
  static int lastY=127;
  if (sp < 2) {
    emitError("Error on D");
    return;
  }
  int x = (strToInt(stack[sp-2]))+38;
  int y = (strToInt(stack[sp-1]) % 128);
  if (y > lastY) {
    display.drawLine(lastY,lastX,y,x,SSD1306_WHITE);
  }
  lastX = x;
  lastY = y;
  pop();
  pop();
}

void cls() {
  printout("");
  display.clearDisplay();
}
void sload() {
  if (sp < 1 && Serial) {
    emitError("Error on SLOAD");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  pop();
  blkp=blk;
  Serial.println("Block #"+blktoString(blk)+" waiting for new content :");
  Serial.flush();
  popupRender("receiving BLK : "+blktoString(blk));
  String content = String();
  while(1) {
      while(Serial.available() ==0){
      }
      char input = Serial.read();
      if (input == 13) {
        Serial.println("");
        break;
      }      
      else if (input == 0x7F) {
        if (content.length() > 0) {
        content = (content.length() == 0)? content : (content.substring(0, content.length() - 1));
          Serial.write(8);
          Serial.write(' ');
          Serial.write(8);    
        }
      }
      else {
        content +=input;
        Serial.write(input);
      }
  }
  Serial.println("Block received");
  writeblk(blk,content);
  
}
void ssend() {
  if (sp < 1 && Serial) {
    emitError("Error on SSEND");
    return;
  }
  int blk = strToInt(stack[sp-1]);
  pop();
  blkp=blk;
  String content = readblk(blk);
  if (content.length() == 0){
    Serial.println("Block #"+blktoString(blk)+" is free");
    return;
  }
  content.replace(String((char) 0xe3),"PI");
  Serial.println("Block #"+blktoString(blk)+" content :");
  Serial.print("<Start>");
  Serial.print(content);
  Serial.println("<End>");
}

String operators[] = {
  "+", "-", "*", "/", "E/", "%", "^", "=", ">", "<",
  "NOT", "OR", "XOR", "AND",
  "LD", "ST", "PRT", "ASK", "RND", "FRT",
  "DUP", "SWP", "RLL", "POP", "OVR", "CLK",
  "IF", "JMP",
  "COS", "SIN", "TAN", "ACOS", "ASIN", "ATAN",
  String((char) 0xe3), "e",
  "LN", "LOG", "ROOT", "ABS", "INT", "DEC", "SIGN",
  "BEEP", "RUN", "ED", "DEL", "CPY", 
  "DRW", "PLT", "CLS",
  "SLOAD","SSEND"
};
void (*exec[])() = {
  add, sub, mul, div, ediv, mod, exp, eq, lt, gt,
  lnot, lor, lxor, land,
  load, store, print, ask, rnd, format,
  dup, swap, roll, pop, over, clock,
  ifelse, jmp,
  tcos, tsin, ttan, tacos, tasin, tatan,
  numpi, nume,
  aln, alog, aroot, aabs, aint, adec, asign,
  beep, run, edit, del, cpy, 
  draw, plot, cls, sload, ssend
};


byte getOpcode(String toCheck) {
  int num = sizeof(exec) / sizeof(void*);
  for (int i = 0; i < num; i++) {
    if (toCheck.equals(operators[i])) {
      return i;
    }
  }
  return 255;
}

void push(String content) {
  stack[sp] = content;
  sp++;
}

void flush() {
  sp = 0;
}

void interpret(String token) {
  int opcode = getOpcode(token);
  if (token.length() == 0) {
    return;
  }
  if (opcode == 255) {
    if (sp > 7) {
      emitError("S.Overflow");
      console = "";
      return;
    }
    push(token);
  } else {
    exec[opcode]();
  }
}

void parse(String toParse) {
  int pointer = 0;
  prog[pointer] = "";
  for (int i = 0; i < toParse.length(); i++) {
    if (toParse.charAt(i) == '\n' || toParse.charAt(i) == '\r') {
      break;
    } else if (toParse.charAt(i) == ' ') {
      pointer++;
      prog[pointer] = "";
    } else {
      prog[pointer].concat(toParse.charAt(i));
    }
  }
  prog[pointer + 1] = "";
}

void drawIcon(int icon) {
  int x = display.getCursorX();
  int y = display.getCursorY();
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(0,1);
  display.print((char) icon);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.display();
  display.setCursor(x,y);
}

void buzz(int freq, int itt) {
  drawIcon(0x0e);
  for (int i = 0; i < itt; i++) {
    tone(pin_tone, compute_freq((freq + 32) + ((i % 3) * 12)), 7);
    delay(10);
  }
  noTone(pin_tone);
}

int compute_freq(int n) {
  return round(pow(2.0, (n - 49.0) / 12.0) * 440.0);
}

String blktoString(int blk) {
  char buffer[5];
  sprintf(buffer,"%04d",blk);
  return String(buffer);
}

void writeblk(int blk, String content) {
  if (blk >= 128 && blk <= 255) {
    drawIcon(0x1f);
    digitalWrite(pin_state[3], HIGH);
    popupRender("Write BLK : "+blktoString(blk));
    for (int pointer = 0; pointer <=126;pointer++) {
      byte actual = 0xFF;
      byte toWrite = 0xFF;
      Wire.beginTransmission(EEPROM_ADDRESS);
      Wire.write((int)((((blk-128)*128)+pointer) >> 8));
      Wire.write((int)((((blk-128)*128)+pointer) & 0xFF));
      Wire.endTransmission();
      Wire.requestFrom(EEPROM_ADDRESS,1);
      if (Wire.available()) {
        actual = Wire.read();
      }
      if (content.length() > pointer) {
        toWrite = (byte) content.charAt(pointer);
      }
      if (toWrite != actual) {
        Wire.beginTransmission(EEPROM_ADDRESS);
        Wire.write((int)((((blk-128)*128)+pointer) >> 8));
        Wire.write((int)((((blk-128)*128)+pointer) & 0xFF));
        Wire.write(toWrite);
        Wire.endTransmission();
        delay(10);
      }
    }
    digitalWrite(pin_state[3], LOW);
  } else if (blk == 256){
    blk256 = content;
  } else {
    return;
  }
}

String readblk(int blk) {
  if (blk >=0 && blk <=127) {
    char buffer[126];
    strcpy_P(buffer, (char *)pgm_read_word(&(documentation[blk])));
    return String(buffer);
  } else if (blk >= 128 && blk <= 255) {
    drawIcon(0x1e);
    digitalWrite(pin_state[3], HIGH);
    popupRender("Read BLK : "+blktoString(blk));
    String content="";
    for (int pointer = 0; pointer <=126;pointer++) {
      Wire.beginTransmission(EEPROM_ADDRESS);
      Wire.write((int)((((blk-128)*128)+pointer) >> 8));
      Wire.write((int)((((blk-128)*128)+pointer) & 0xFF));
      Wire.endTransmission();
      Wire.requestFrom(EEPROM_ADDRESS,1);
      if (Wire.available()) {
        char readed = (char) Wire.read();
        if (readed > 0 && readed < 128) {
          content.concat(readed);
        }
      }
    }
    digitalWrite(pin_state[3], LOW);
    return content;
  } else if (blk == 256){
    return blk256;
  } else {
    return "";
  }
}

void initComputer() {
  Serial.begin(9600);
  pinMode(pin_tone, OUTPUT);
  for (int i = 0; i < ROW_NUM; i++) {
    pinMode(pin_rows[i], OUTPUT);
    digitalWrite(pin_rows[i], LOW);
  }
  for (int i = 0; i < COLUMN_NUM; i++) {
    pinMode(pin_cols[i], INPUT);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(pin_state[i], OUTPUT);
    digitalWrite(pin_state[i], LOW);
  }
  digitalWrite(pin_state[state], HIGH);
}

int getKey() {
  for (int x = 0; x < ROW_NUM; x++) {
    digitalWrite(pin_rows[x], HIGH);
    for (int y = 0; y < COLUMN_NUM; y++) {
      if (digitalRead(pin_cols[y]) == HIGH) {
        int keycode = y + x * COLUMN_NUM;
        while (digitalRead(pin_cols[y]) == HIGH) {
        };
        digitalWrite(pin_rows[x], LOW);
        if (keycode == 23) {
          digitalWrite(pin_state[state], LOW);
          state = (state + 1) % 3;
          digitalWrite(pin_state[state], HIGH);
          buzz(((state+2) * 3),5);
          delay(10);
          buzz(((state+2) * 3),2);
          return -1;
        }
        return (y + x * COLUMN_NUM) + ((state)*NUM_KEYS);
      }
    }

    digitalWrite(pin_rows[x], LOW);
  }
  digitalWrite(pin_state[3], LOW);
  return -1;
}

void emitError(String err) {
  flagError = true;
  error = err;
  popupRender(err);
  buzz(10, 50);
}

void clearError() {
  flagError = false;
  error = "";
  digitalWrite(pin_state[4], LOW);
}

void popupRender(String message) {
  int x = display.getCursorX();
  int y = display.getCursorY();
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.fillRect(63-((message.length()/2)*6),32-4,3+((message.length())*6),10, SSD1306_WHITE);
  display.drawRect(62-((message.length()/2)*6),32-5,4+((message.length())*6),11, SSD1306_BLACK);
  display.setCursor(64-((message.length()/2)*6),32-3);
  display.print(message);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.display();
  display.setCursor(x,y);
}

void overlayRender() {
  if (millis() % 500 < 250) {
    display.drawChar(display.getCursorX(),display.getCursorY(),(char) 0xb0,SSD1306_WHITE,SSD1306_BLACK,1);
  }
}

void statusRender(String left, String right) {
  int x = display.getCursorX();
  int y = display.getCursorY();
  display.fillRect(0,0,128,9, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  if (flagError) {
    digitalWrite(pin_state[4], HIGH);  
  } else {
    digitalWrite(pin_state[4], LOW);
  }
  display.setCursor(0, 1);
  display.print(left);
  display.setCursor(128 -(6*8), 1);
  display.print(right);
  display.setCursor(x, y);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

}

void consoleRender() {
    display.setTextWrap(true);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    if (mode == "run") {
      display.fillRect(0,28,128,9,SSD1306_BLACK);
    } else {
      display.clearDisplay();
    }
    display.setCursor(0, 11);
    display.print(output);
    display.setCursor(0, 29);
    display.print((char) 16);
    display.print(console);
    display.drawFastHLine(0, 27, 128, SSD1306_WHITE);
    display.drawFastHLine(0, 37, 128, SSD1306_WHITE);
    display.drawFastHLine(0, 63, 128, SSD1306_WHITE);
}

void runRender() {
  consoleRender();
}

void dbgRender() {
  consoleRender();
  int x = display.getCursorX();
  int y = display.getCursorY();
  display.setCursor(0, 39);
  String buffer = String(prog[op]).substring(0,4);
  if (prog[op] != buffer) {
    buffer = buffer + "...";
  }
  display.print(" Stack..: " + String(sp) + " "+ (char)17 +" " + (buffer.length()==0?"End":buffer) + "\n");
  if (sp > 0) {
    display.print(" Head...: " + stack[sp - 1].substring(0, 11) + "\n");
  } else {
    display.print(" Stack Empty");
  }
  if (sp > 1) {
    display.print(" Head-1.: " + stack[sp - 2].substring(0, 11));
  }
  display.setCursor(x, y);
}

void editRender() {
  display.setTextWrap(true);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.setCursor(0, 11);
  display.print(console);
  display.drawFastHLine(0, 59, 128, SSD1306_WHITE);
}

void cmd(String toExec) {
  parse(toExec);
  printout(toExec);
  op = 0;
}

void executeTick(String input) {
  if (!prog[op].length()==0) {
    interpret(prog[op]);
    if (!prog[op].equals("ASK")) {
      op++;
    }
    if (input != "nop" && input != "dbg" && input != "run") {
      finish_ask(input);
      op++;
    }
  } else if (prog[op].length()==0) {
    if (sp > 0) {
      printout(stack[sp-1]);
    }
    prog[0] = "";
    sp = 0;
  }
}

String consoleTick(int key,int limit) {
  if (key == -1) {
    return "nop";
  }
  if (flagError) {
    clearError();
  }
  if (KEYMAP[key].equals("RUN")) {
    buzz(12, 2);
    delay(10);
    buzz(14, 2);
    delay(10);
    buzz(16, 4);
    String input = String(console);
    console = "";
    if (input.length() == 0) {
      return "run";
    } else {
      return input;
    }
  } else if (KEYMAP[key].equals("DBG")) {
    buzz(14, 2);
    delay(10);
    buzz(16, 4);
    return "dbg";
  } else if (KEYMAP[key].equals("BS")) {
    buzz(10, 2);
    if (console.length() == 0) {
      emitError("Underflow");
      return "nop";
    }
    console.remove(console.length() - 1);
    return "nop";
  } else if (KEYMAP[key].equals(" ")) {
      buzz(20, 2);
      delay(10);
      buzz(20, 4);
  }
  if (console.length() + KEYMAP[key].length() > limit) {
      emitError("Overflow");
  } else {
    console.concat(KEYMAP[key]);
  }
  return "nop";
}

void runTick(int key) {
  String input = consoleTick(key,20);
  if (input == "run") {
    mode = "edt";
    console = readblk(blkp);
    output = "";
    op = 0;
    sp = 0;
  } else if (input == "dbg") {
    mode = "dbg";
  } else if (input != "nop" ) {
    if (! prog[op].equals("ASK")) {
      cmd(input);
      input="nop";
    }
  }
  executeTick(input);
  if (mode == "run") {
    runRender();
    statusRender(error, "Run "+blktoString(blkp));
    overlayRender();
  } else {
    display.clearDisplay();
  }
}

void dbgTick(int key) {
  String input = consoleTick(key,21);
  if (input == "run") {
    executeTick(input);
    serialDbg();
  } else if (input == "dbg") {
    mode = "run";
  } else if (input != "nop" ) {
    if (! prog[op].equals("ASK")) {
      cmd(input);
      input="nop";
    } else {
      executeTick(input);
      serialDbg();
    }
  }
  if (mode == "dbg") {
    dbgRender();
    statusRender(error, "Dbg "+blktoString(blkp));
    overlayRender();
  } else {
    display.clearDisplay();
  }
}

void serialDbg() {
  Serial.print("(");
  for (int i = 0; i<sp; i++) {
    Serial.print(" "+stack[i]+" ");
    if (i<sp-1) {
      Serial.print("|");
    }
  }
  Serial.print(") ");
  Serial.print(" <- ");
  Serial.print(prog[op]);
  Serial.println();
}

void editTick(int key) {
  String input = consoleTick(key,126);
  if (input == "run") {
    mode = "run";
  } else if (input != "nop" && input != "debug" ) {
    writeblk(blkp,input);
    console = "";
    output = "";
    op = 0;
    sp = 0;
    prog[0] = "";
    mode = "run";
  }
  if (mode == "edt") {
    editRender();
    statusRender(error, "Edt "+blktoString(blkp));
    overlayRender();
  } else {
    display.clearDisplay();
  }
}

void printout(String out) {
  display.fillRect(0,10,128,20,SSD1306_BLACK);
  output = out;
}

void setup() {
  initComputer();
  digitalWrite(pin_state[0], HIGH);
  digitalWrite(pin_state[1], HIGH);
  digitalWrite(pin_state[2], HIGH);
  digitalWrite(pin_state[3], HIGH);
  digitalWrite(pin_state[4], HIGH);
  randomSeed(analogRead(A0));
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.cp437(true);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(6,0);
  display.print("K1284");
  display.setCursor(0,32);
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.fillRect(0,32,128,64, SSD1306_WHITE);
  display.print("        Ben's\n Old School Computers\n     2022 - 2023\n Operating System V2");
  display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
  display.display();
  delay(3000);
  clearError();
  digitalWrite(pin_state[0], HIGH);
  digitalWrite(pin_state[1], LOW);
  digitalWrite(pin_state[2], LOW);
  display.clearDisplay();
}

void loop() {
  while(1) {
    int key = getKey();
    if (mode == "run") {
      runTick(key);
    } else if (mode == "dbg") {
      dbgTick(key);
    } else {
      editTick(key);
    }
    display.display();
  }
}
