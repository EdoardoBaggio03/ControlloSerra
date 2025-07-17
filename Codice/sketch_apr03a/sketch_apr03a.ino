int x=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Temp.val=");
Serial.print(x);
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);
x++;
}
