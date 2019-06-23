//=====================================================================
//
//        ∧ ∧
//  　   (*`Д′)　 ≀≀≀ ＜いいから解読しろっす！自分は雰囲気でArduinoをいじってるっす！正直勢いで書いたし清書もクソもあったもんじゃねぇっす！
//  　～ (_ uu )   旦      ついでにＳＤカードへの書き込み等の部分はまだ導入してねぇっす！要は未完成品ってことっす！
//                        SDカードはやったけどCSVになってねえじゃねえかクソ!
//
//      割り込みの仕様はここ(http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=3069)を確認するっす
//　　https://github.com/cansat-niigata/2019_G2_Arduino.git

//=====================================================================



//xbee RX:0TX:1


//=====LEFT=====
#define PIN_L1 3
#define PIN_L2 5
//=====RIGHT=====
#define PIN_R1 6
#define PIN_R2 9
//=====FLIGHT PIN=====
#define PIN_FLIGHT /*(A)*/2
//=====MAG=====
//#define MAGPIN_L 2//2か3固定っす
//#define MAGPIN_R 4//3にする
#define NUMoMAG 6//磁石の数っす
//volatile int state = LOW;
volatile double time4round_L[4] = {0};//割り込み関数で値を取りたい時はそれを格納する変数を先頭にvolatileをつけてグローバル変数で宣言するっすこれをつけると変数がレジスタじゃなくてRAMから読まれるとかなんとかっすあいつ割り込みの話すると急に早口
volatile double time4round_R[4] = {0};
//ここだと割り込みが処理された時間([1])と前回の割り込み処理からの経過時間([0])、回転角([2])を得るためにグローバル変数使ってるけど実際に使うときは[1]はいらないかもっす

#define Radius_of_Wheel 0.065
#define Radius_of_Turn 0.085

//=====GPS=====
#define PIN_TX 14//A0
#define PIN_RX 15//A1

//===TARGET===
#define TAG_LAT 35.658551
#define TAG_LNG 139.745426
#define test_LAT 37.865901947
#define test_LNG 138.93835449
//=====Servo=====
#define PIN_SERVO 10

//=====SD=====
#define PIN_SD1 11//→チップセレクト？12,13
#define PIN_SD2 12
#define PIN_SD3 13
//#define FILE_NAME ("Loglog_chan.txt")

#include <TinyGPS++.h>
//#include <SoftwareSerial.h>←クソ！
#include <MultiUART.h>
//#include <Servo.h>
#include <Adafruit_TiCoServo.h>
#include <known_16bit_timers.h>
#include <SD.h>

//===Handle/Object===
TinyGPSPlus gpsplus;
MultiUART mySerial(PIN_TX, PIN_RX); // (TX, RX) GPSとの通信用
Adafruit_TiCoServo myservo;
File file;


//===Prototype_declaration===

unsigned long forward_LEFT(unsigned long time4move/*ms*/);
unsigned long forward_RIGHT(unsigned long time4move/*ms*/);
unsigned long forward(unsigned long time4move/*ms*/);
//unsigned long turn_LEFT(unsigned long time4turn/*ms*/);
//unsigned long turn_RIGHT(unsigned long time4turn/*ms*/);
unsigned long back_LEFT(unsigned long time4move/*ms*/);
unsigned long back_RIGHT(unsigned long time4move/*ms*/);
//unsigned long back(unsigned long time4move/*ms*/);

int purge();

void wait (unsigned long waittime);

void magen();
//void encoder();



//=====GLOBAL/SETUP=====
int trigger = 0;
//boolean file_judge;
boolean flag = false;
double prev_LAT = 0;
double prev_LNG = 0;
double N_LAT = 0;
double N_LNG = 0;
//double late_LAT = 0;
//double late_LNG = 0;
//int MODE = 0;

const char *FILE_NAME = "Loglog_chan.txt";

unsigned long movetime = 0;
unsigned long tag_movetime = 3000;
unsigned long turntime = 0;
unsigned long tag_turntime_R = 3000;
unsigned long tag_turntime_L = 3000;


typedef struct {
  unsigned long time_stamp;
  double nlat;
  double nlng;
 // double speed_gps;
  double speed_encoder_R;
  double speed_encoder_L;
  //double course_deg;
  double course_tag;
  double course_ptag;
  double course_prev;
  //const char* hcourse;
  double ndistance;
  double pdistance;
  unsigned long Pred_movetime;
  unsigned long Pred_turntime_R;
  unsigned long Pred_turntime_L;
} Sailing_Data;

Sailing_Data Datas = {};
Sailing_Data observer(double L_LAT, double L_LNG, double P_LAT, double P_LNG, double roll_speed, double Radius_Wheel, double Radius_Turn );
void record(const char *filename, Sailing_Data Log, int mode);
//
ISR(PCINT2_vect) {
  //  // Interrupt Handling
  magen();
}

void setup() {
  // put your setup code here, to run once:
  PCICR = 0;
  PCMSK0 = 0;
  PCMSK1 = 0;
  PCMSK2 = 0;
  PCMSK2 |= ((1 << PCINT18) | (1 << PCINT20));  // D2,D4ピンからのピンチェンジ割込みを使う
  PCICR  |= (1 << PCIE2);                     // PCIE2グループからの割込み許可


  Serial.begin(9600);//pc
  mySerial.begin(9600);//gps
  SD.begin();


  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);



  //pinMode(PIN_FLIGHT, INPUT);

  pinMode(2, INPUT);
  pinMode(4, INPUT);
}
