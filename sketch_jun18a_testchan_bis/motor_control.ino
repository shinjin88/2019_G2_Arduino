unsigned long forward_LEFT(unsigned long time4move/*ms*/) {
  unsigned long starttime = millis();
  Serial.println("STS: MOVEING: FORWARD:LEFT");
  while (millis() <= starttime + time4move) {
    digitalWrite(PIN_R1, HIGH);
    digitalWrite(PIN_R2, LOW);
  }
  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_R2, LOW);
  return time4move;
}

unsigned long forward_RIGHT(unsigned long time4move/*ms*/) {
  unsigned long starttime = millis();
  Serial.println("STS: MOVEING: FORWARD:RIGHT");
  while (millis() <= starttime + time4move) {
    digitalWrite(PIN_L1, HIGH);
    digitalWrite(PIN_L2, LOW);
  }
  digitalWrite(PIN_L1, LOW);
  digitalWrite(PIN_L2, LOW);
  return time4move;
}

unsigned long forward(unsigned long time4move/*ms*/) {
  unsigned long starttime = millis();
  Serial.println("STS: MOVEING: FORWARD");
  while (millis() <= starttime + time4move) {
    digitalWrite(PIN_R1, HIGH);
    digitalWrite(PIN_R2, LOW);
    digitalWrite(PIN_L1, HIGH);
    digitalWrite(PIN_L2, LOW);

  }
  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_R2, LOW);
  digitalWrite(PIN_L1, LOW);
  digitalWrite(PIN_L2, LOW);
  return time4move;
}


//unsigned long turn_LEFT(unsigned long time4turn) {
//  unsigned long starttime = millis();
//  Serial.println("STS: MOVEING: TURN LEFT");
//  if (millis() <= (starttime + time4turn)) {
//    digitalWrite(PIN_R1, HIGH);
//    digitalWrite(PIN_R2, LOW);
//    digitalWrite(PIN_L1, LOW);
//    digitalWrite(PIN_L2, HIGH);
//  }
//  digitalWrite(PIN_R1, LOW);
//  digitalWrite(PIN_R2, LOW);
//  digitalWrite(PIN_L1, LOW);
//  digitalWrite(PIN_L2, LOW);
//  return time4turn;
//}

//unsigned long turn_RIGHT(unsigned long time4turn) {
//  unsigned long starttime = millis();
//  Serial.println("STS: MOVEING: TURN RIGHT");
//  if (millis() <= (starttime + time4turn)) {
//    digitalWrite(PIN_R1, LOW);
//    digitalWrite(PIN_R2, HIGH);
//    digitalWrite(PIN_L1, HIGH);
//    digitalWrite(PIN_L2, LOW);
//  }
//  digitalWrite(PIN_R1, LOW);
//  digitalWrite(PIN_R2, LOW);
//  digitalWrite(PIN_L1, LOW);
//  digitalWrite(PIN_L2, LOW);
//  return time4turn;
//}
//
unsigned long back_LEFT(unsigned long time4move/*ms*/) {
  unsigned long starttime = millis();
  Serial.println("STS: MOVEING: BACK:LEFT");
  while (millis() <= starttime + time4move) {
    digitalWrite(PIN_R1, LOW);
    analogWrite(PIN_R2, 200);

  }
  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_R2, LOW);
  return time4move;
}

unsigned long back_RIGHT(unsigned long time4move/*ms*/) {
  unsigned long starttime = millis();
  Serial.println("STS: MOVEING: BACK:RIGHT");
  while (millis() <= starttime + time4move) {
    digitalWrite(PIN_L1, LOW);
    analogWrite(PIN_L2, 200);

  }
  /* digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);*/
  digitalWrite(PIN_L1, LOW);
  digitalWrite(PIN_L2, LOW);
  return time4move;
}

//unsigned long back(unsigned long time4move/*ms*/) {
//  //  analogWrite(PIN_VREF_A, 255);
//  //  analogWrite(PIN_VREF_B, 255);
//  unsigned long starttime = millis();
//  Serial.println("STS: MOVEING: BACK");
//  while (millis() <= starttime + time4move) {
//    digitalWrite(PIN_R1, LOW);
//    digitalWrite(PIN_R2, HIGH);
//    digitalWrite(PIN_L1, LOW);
//    digitalWrite(PIN_L2, HIGH);
//
//  }
//  digitalWrite(PIN_R1, LOW);
//  digitalWrite(PIN_R2, LOW);
//  digitalWrite(PIN_L1, LOW);
//  digitalWrite(PIN_L2, LOW);
//  return time4move;
//}
