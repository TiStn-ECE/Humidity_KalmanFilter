void komunikasi_pc(float measurement, float current_estimate)
{
  byte * b = (byte *) &measurement;
  byte * c = (byte *) &current_estimate;
  //  Serial.print("f:");
  Serial.write(255);
  Serial.write(b, 4);
  Serial.write(c, 4);
  Serial.flush();
}
