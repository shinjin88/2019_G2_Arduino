int purge() {
  int i;
  int pos;
  myservo.attach(PIN_SERVO);
  for  (i = 0; i < 5; i++) {
    Serial.print("PURGING...Count:");
    Serial.println(i);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);    // tell servo to go to position in variable 'pos'
     // Serial.println("Servo is Moving...");
      delay(10);                      // waits 10ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //  Serial.println("Servo is Moving...");
      delay(10);                      // waits 10ms for the servo to reach the position
    }
  }
  Serial.println("Purged!");
  myservo.detach();
  return 1;
}
