void wait (unsigned long waittime) {
  unsigned long now = millis();
  while (true) {
    if (millis() >= (now + waittime) ) {
      Serial.println("Go!");
      return;
    }
    else {
      Serial.print(((now + waittime) - millis()) / 1000);
      Serial.println(" to Go");
    }
  }
}
