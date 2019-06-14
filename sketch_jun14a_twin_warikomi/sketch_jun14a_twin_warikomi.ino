/*

  割り込みピンの割り当ての時間だオラァ!
 
  割り込みピンの割り当てについて
  割込ソース: 割込ピン
  　PCI0: PCINT0～7(PB0(D8),1(D9),2(D10),3(D11),4(D12),5(D13),6(なし),7(なし))
  　PCI1: PCINT8～15(PC0(A0),1(A1),2(A2),3(A3),4(A4),5(A5),6(RESET),7(欠番）))
  　PCI2: PCINT16～23(PD0(D0),1(D1),2(D2),3(D3),4(D4),5(D5),6(D6),7(D7))
  D9はPCI0

  流れ：ピン変化割り込みをピンXで行う

          PCICRを0にする(割り込みピンを初期化)
          PCMSK0~2を初期化
          ピン変化割り込みマスクレジスタPCMSK0~2(Xに対応)のPCINTXを1にする
          次にPCICR0~2を1にする

         例えばPD4=PCINT20(ArduinoではD4)では

          PCICR=0;
          PCMSK0=0;
       　 PCMSK1=0;
          PCMSK2=1<<(20-16);又は　PCMSK2 |=(1<<PCINT20);
          PCICR=1<<2;又は　PCICR |=(1<<PCIE2);　//

          の様に書く

        

  割り込みハンドルの書き方
    ISR(PCINT2_vect(hardware/tools/avr/avr/include/avr/iom328p.hを参照，))
  {
    // Interrupt Handling
  }


*/

//#include<avr/interrupt.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7 );

boolean stick_switch();
volatile boolean R3 = false;
volatile boolean led = false;

ISR(PCINT0_vect) {
  R3 = stick_switch();
  led = led_switch();
}

void setup() {
  // put your setup code here, to run once:
  PCICR = 0;
  PCMSK0 = 0;
  PCMSK1 = 0;
  PCMSK2 = 0;
  PCMSK0 |= ((1 << PCINT1) | (1 << PCINT2));  // D9,D10ピンからのピンチェンジ割込みを使う
  PCICR  |= (1 << PCIE0);                     // PCIE0グループからの割込み許可

  //Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Hello,World!");
  delay(1000);
  lcd.clear();

  /*pinMode(10,INPUT);
    pinMode(11,INPUT);*/
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  double  x = analogRead(0);
  double  y = analogRead(1);
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.setCursor(2, 0);
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("Y:");
  lcd.setCursor(2, 1);
  lcd.print(y);
  lcd.setCursor(9, 0);
  lcd.print("SWT:");
  lcd.setCursor(13, 0);
  if (R3 == true) {
    lcd.print("ON ");
  }
  else {
    lcd.print("OFF");
  }
  lcd.setCursor(9, 1);
  lcd.print("LED:");
  lcd.setCursor(13, 1);
  if (led == true) {
    lcd.print("ON ");
  }
  else {
    lcd.print("OFF");
  }

}

boolean stick_switch() {
  if (digitalRead(9) == LOW) {
    return true;
  }
  else {
    return false;
  }
}

boolean led_switch() {
  if (digitalRead(10) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}
