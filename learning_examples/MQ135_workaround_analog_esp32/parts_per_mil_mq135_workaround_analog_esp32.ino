void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("begin");
}

void loop() {
  Serial.println(analogRead(15)); // ppm metrics (raw (i think))
  // put your main code here, to run repeatedly:
}
