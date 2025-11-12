const int sensorPin = A0; // กำหนดขาที่เชื่อมต่อ Light Sensor TC01

int sensorValue; // ตัวแปรเก็บค่าแสง



void setup() {

  Serial.begin(9600); // เริ่มต้นใช้งาน Serial Monitor

}



void loop() {

  sensorValue = analogRead(sensorPin); // อ่านค่าแสงจาก Light Sensor TC01

  Serial.print("Light level: ");

  Serial.println(sensorValue); // แสดงค่าแสงที่อ่านได้ใน Serial Monitor

  delay(1000); // รอเวลาสั้น ๆ ก่อนที่จะอ่านค่าแสงใหม่

}