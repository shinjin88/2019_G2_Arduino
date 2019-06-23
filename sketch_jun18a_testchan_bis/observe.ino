Sailing_Data observer(double L_LAT, double L_LNG, double P_LAT, double P_LNG, double roll_speed_R, double roll_speed_L, double Radius_Wheel, double Radius_Turn ) {
  Sailing_Data Dairy;//これlogの方がかっこいいっすね...
  Dairy.nlat = L_LAT;
  Dairy.nlng = L_LNG;
  Dairy.ndistance = gpsplus.distanceBetween(
                      L_LAT,
                      L_LNG,
                      TAG_LAT,
                      TAG_LNG
                    );
  Dairy.pdistance = gpsplus.distanceBetween(
                      P_LAT,
                      P_LNG,
                      L_LAT,
                      L_LNG
                    );
  /*Dairy.hcourse = gpsplus.cardinal(gpsplus.courseTo(
                                     L_LAT,
                                     L_LNG,
                                     TAG_LAT,
                                     TAG_LNG
                                   )
                                  );*/
  Dairy.course_tag = gpsplus.courseTo(
                       L_LAT,
                       L_LNG,
                       TAG_LAT,
                       TAG_LNG
                     );
  Dairy.course_ptag = gpsplus.courseTo(
                        P_LAT,
                        P_LNG,
                        TAG_LAT,
                        TAG_LNG
                      );
  //Dairy.course_deg = gpsplus.course.deg();
  Dairy.course_prev = gpsplus.courseTo(
                        P_LAT,
                        P_LNG,
                        L_LAT,
                        L_LNG
                      );

//  Dairy.speed_gps = gpsplus.speed.mps();
  Dairy.speed_encoder_R = roll_speed_R * (Radius_Wheel);
  Dairy.speed_encoder_L = roll_speed_L * (Radius_Wheel);
  Dairy.Pred_movetime = (3 / (roll_speed_R * (Radius_Wheel))) * 1000;
  Dairy.Pred_turntime_R = (((2 * Radius_Turn * 3.14) / (roll_speed_R * (Radius_Wheel))) * 1000 / 360);
  Dairy.Pred_turntime_L = (((2 * Radius_Turn * 3.14) / (roll_speed_L * (Radius_Wheel))) * 1000 / 360);
  Dairy.time_stamp = millis();

  /*Serial.print("TIME:");
    Serial.println(Dairy.time_stamp);
    Serial.print("LAT:");
    Serial.println(Dairy.nlat);
    Serial.print("LNG:");
    Serial.println(Dairy.nlng);
    Serial.print("Distance_To_TAG:");
    Serial.println(Dairy.ndistance);
    Serial.print("Distance_From_Prev_Point:");
    Serial.println(Dairy.pdistance);
    Serial.print("Course_To_TAG");
    Serial.println(Dairy.course_tag);
    Serial.print("Course_From_Prev_Point:");
    Serial.println(Dairy.course_prev);
    Serial.print("Course_Human_Like?:");
    Serial.println(Dairy.hcourse);
    Serial.print("Course_Deg?:");
    Serial.println(Dairy.course_deg);
    Serial.print("Speed(GPS):");
    Serial.println(Dairy.speed_gps);
    Serial.print("Speed(Encoder):");
    Serial.println(Dairy.speed_encoder);*/

  return Dairy;
}
