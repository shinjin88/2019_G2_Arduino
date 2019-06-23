void magen() {
  if (digitalRead(4) == LOW) {
    //  if (switch1 == true) {
    time4round_R[0] = (millis() - time4round_R[1]);//前回の割り込みからの時間っす
    if (time4round_L[0] < 1000) {
      time4round_R[1] = millis();
      time4round_R[2] = (60000 / time4round_R[0]);
      time4round_R[3] = time4round_R[2];
    }
    else {
      time4round_R[2] = time4round_R[3];
    }
    /* switch1 = false;
      }
      else {
      switch1 = true;
      }*/
  }
  if (digitalRead(2) == LOW) {
    //if (switch1 == true) {
    time4round_L[0] = (millis() - time4round_L[1]);//前回の割り込みからの時間っす
    if (time4round_L[0] < 1000) {
      time4round_L[1] = millis();
      time4round_L[2] = (60000 / time4round_L[0]);
      time4round_L[3] = time4round_L[2];
    }
    else {
      time4round_L[2] = time4round_L[3];
    }
    /* switch1 = false;
      }
      else {
      switch1 = true;
      }*/
  }
  return;
}

/*void encoder() {

  if (time4round_R[0] < 1500) {
    time4round_R[2] = (360 / ((time4round_R[0] / 1000) * (NUMoMAG)));//ここで回転角/秒を出すっす
    Serial.println("DATA:RIGHT");
    Serial.print("time:");
    Serial.print(time4round_R[0] / 1000);
    Serial.println("sec");
    Serial.print("angle:");
    Serial.print(time4round_R[2]);
    Serial.println("°/sec");
  }
  else {
    time4round_R[2] = time4round_R[3];
  }

  if (time4round_L[0] < 1500) {
    time4round_L[2] = (360 / ((time4round_L[0] / 1000) * (NUMoMAG)));//ここで回転角/秒を出すっす
    Serial.println("DATA:LEFT");
    Serial.print("time:");
    Serial.print(time4round_L[0] / 1000);
    Serial.println("sec");
    Serial.print("angle:");
    Serial.print(time4round_L[2]);
    Serial.println("°/sec");
  }
  else {
    time4round_L[2] = time4round_L[3];
  }

  return;
}*/
