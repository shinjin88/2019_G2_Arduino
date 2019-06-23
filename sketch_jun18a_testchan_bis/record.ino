void record(const char *filename, Sailing_Data Log, int mode) {
file = SD.open(filename, FILE_WRITE);

  switch (mode) {
    case 1:
      file.print("TIME:");
      file.println(Log.time_stamp);
      file.print("LAT:");
      file.println(Log.nlat);
      file.print("LNG:");
      file.println(Log.nlng);
      file.print("Distance_To_TAG:");
      file.println(Log.ndistance);
      file.print("Distance_From_Prev_Point:");
      file.println(Log.pdistance);
      file.print("Course_To_TAG");
      file.println(Log.course_tag);
      file.print("Course_From_Prev_Point:");
      file.println(Log.course_prev);
      /*file.print("Course_Human_Like?:");
      file.println(Log.hcourse);
      file.print("Course_Deg?:");*/
     /* file.println(Log.course_deg);*/
//      file.print("Speed(GPS):");
//      file.println(Log.speed_gps);
      file.print("Speed(Encoder)R:");
      file.println(Log.speed_encoder_R);
      file.print("Speed(Encoder)L:");
      file.println(Log.speed_encoder_L);
      file.print("Pred_movetime:");
      file.println(Log.Pred_movetime);
//      file.print("Pred_turntime:");
//      file.println(Log.Pred_turntime_R);
      break;

    case 2:
    file.print("TIME:");
      file.println(Log.time_stamp);
      file.println("STS: MOVEING: FORWARD");
      //file.print("DISTANCE:");
      //file.println("3m(仮）");
      break;

    case 3:
    file.print("TIME:");
      file.println(Log.time_stamp);
      file.println("STS: MOVEING: TURN LEFT");
      file.print("ANGLE(encoder):");
      file.println((Log.course_tag - Log.course_prev));
      break;

    case 4:
    file.print("TIME:");
      file.println(Log.time_stamp);
      file.println("STS: MOVEING: TURN RIGHT");
      file.print("ANGLE(encoder):");
      file.println((Log.course_tag - Log.course_prev));
      break;

    case 5:
    file.print("TIME:");
      file.println(Log.time_stamp);
      file.println("STS:WAITING...");
      break;
    case 6:
    file.print("TIME:");
      file.println(Log.time_stamp);
      file.println("STS:すたっくはんてい！");
      break;
  }
  file.close();
  return ;
}
