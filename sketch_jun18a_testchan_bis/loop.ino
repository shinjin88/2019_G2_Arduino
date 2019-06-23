void loop() {
  // put your main code here, to run repeatedly:
  if (trigger == 2) {
    Serial.println("STS:goal?");
  }
  else {
    if (trigger == 0) {
      Serial.println("STS:STANDBY");
      Serial.println(analogRead(2));
      if (analogRead(2) < 400) {
        wait(10000);
        trigger = purge();
        Serial.println("Waiting GPS data...");

maze1:
        delay(1000);
        if (flag == false) {
          do {
            gpsplus.encode(mySerial.read());
            Serial.println("loading GPS data...");
            if (gpsplus.location.isUpdated()) {

              prev_LAT = gpsplus.location.lat();
              prev_LNG = gpsplus.location.lng();

              Serial.println("Got latest GPS data...");
              Serial.print("LAT:");
              Serial.println(gpsplus.location.lat());
              Serial.print("LNG:");
              Serial.println(gpsplus.location.lng());

              flag = true;
            }
          } while (mySerial.available());
          goto maze1;
        }
        flag = false;
      }
    }
    else {
      if (/*Datas.ndistance  > 3*/gpsplus.distanceBetween(
                                    prev_LAT,
                                    prev_LNG,
                                    TAG_LAT,
                                    TAG_LNG
                                  ) > 3) {

        movetime = forward(tag_movetime);

        record(FILE_NAME, Datas, 2);

        Serial.println("Waiting GPS data...");
maze2:
        delay(1000);
        if (flag == false) {
          do {

            gpsplus.encode(mySerial.read());
            Serial.println("loading GPS data...");
            if (gpsplus.location.isUpdated()) {

              N_LAT = gpsplus.location.lat();
              N_LNG = gpsplus.location.lng();

              Serial.println("Got latest GPS data...");
              Serial.print("LAT:");
              Serial.println(gpsplus.location.lat());
              Serial.print("LNG:");
              Serial.println(gpsplus.location.lng());
              flag = true;
            }
          } while (mySerial.available());
          goto maze2;
        }
        flag = false;

        Datas = observer(gpsplus.location.lat(), gpsplus.location.lng(), prev_LAT, prev_LNG, time4round_R[2], time4round_L[2], (Radius_of_Wheel), (Radius_of_Turn));

        record(FILE_NAME,  Datas, 1);

        if (Datas.pdistance < 2) {
          Serial.println("すたっくはんてい！");
          record(FILE_NAME, Datas, 6);
          back_LEFT(3000);
          back_RIGHT(2000);
          back_LEFT(2000);
          back_RIGHT(3000);
          //  goto bailout;
        }
        else {
          if (5 <= Datas.course_ptag && Datas.course_ptag < 180) {
            tag_turntime_L = (360 - Datas.course_ptag + Datas.course_tag) / Datas.Pred_turntime_L;

            if (Datas.course_prev - Datas.course_ptag > 0) {
              tag_turntime_L = tag_turntime_L - 200;
            }
            else {
              tag_turntime_L = tag_turntime_L + 200;
            }

            turntime = forward_LEFT(tag_turntime_L);
            record(FILE_NAME, Datas, 3);
            //flag = true;
          }
          else {
            if (180 <= Datas.course_ptag && Datas.course_ptag < 355) {
              tag_turntime_R = (360 + Datas.course_ptag - Datas.course_tag) / Datas.Pred_turntime_R;

              if (Datas.course_prev - Datas.course_ptag > 0) {
                tag_turntime_R = tag_turntime_R - 200;
              }
              else {
                tag_turntime_R = tag_turntime_R + 200;
              }

              turntime = forward_RIGHT(tag_turntime_R);
              record(FILE_NAME, Datas, 4);
              //flag = true;
            }
          }
        }
        tag_movetime = (/*(Datas.ndistance) */3 / Datas.speed_encoder_R);
        //        encoder() ;
        prev_LAT = gpsplus.location.lat();
        prev_LNG = gpsplus.location.lng();
      }
      else {
        trigger = 2;
        record(FILE_NAME, Datas, 1);

      }
    }
  }
}
