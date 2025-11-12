#define S0 7
#define S1 8
#define S2 4
#define S3 5
#define sensorOut 6

int redFrequency, greenFrequency, blueFrequency;
int redValue, greenValue, blueValue;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // ตั้งค่าให้สเกลความถี่เป็น 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
  Serial.println("TCS230 Color Detection");
}

void loop() {
  // --- วัดค่า Red ---
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redValue = map(redFrequency, 25, 72, 255, 0);

  // --- วัดค่า Green ---
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenValue = map(greenFrequency, 30, 90, 255, 0);

  // --- วัดค่า Blue ---
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueValue = map(blueFrequency, 25, 70, 255, 0);

  // หาค่าสีที่มากที่สุดแล้วพิมพ์ชื่อออกมา
  if (redValue > greenValue && redValue > blueValue) {
    Serial.println("Red");
  } 
  else if (greenValue > redValue && greenValue > blueValue) {
    Serial.println("Green");
  } 
  else if (blueValue > redValue && blueValue > greenValue) {
    Serial.println("Blue");
  } 
  else {
    Serial.println("Unknown");
  }

  delay(500);
}
