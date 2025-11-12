
#define PWM1 5
#define INA1 2
#define INB1 3
#define PWM2 6
#define INA2 4
#define INB2 7
#define ultra digitalRead(9)
#define numsensor 8
int port[numsensor] = { A0, A1, A2, A3, A4, A5, A6, A7 };
int Max[numsensor] = { 760, 747, 741, 742, 711, 728, 745, 731 };  //-100
int Min[numsensor] = { 150, 38, 37, 37, 38, 37, 37, 150 };        //+20
long F[numsensor];

int last_value = 0;
float leftmotor, rightmotor, powermotor, error, last_error, position;
const int signal_pin = A4;

void setup() {
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  // read();
  // while(1){
  // Serial.println(ultra);
  // }
  // viewreadline();
  while (digitalRead(8) == 1)
    ;
  delay(600);
  tt(50, 0.02, 0.2, 200);
  tt(95, 0.02, 0.2, 800);
  tb(45, 0.02, 0.2);
  l();

  tu(40, 0.02, 0.2);
  lopl();

  tb(50, 0.02, 0.2);
  l();

  tt(50, 0.02, 0.2, 150);
  tb(50, 0.02, 0.2);
  r();

  tt(80, 0.02, 0.2, 100);
  tr(80, 0.02, 0.2);
  tr(80, 0.02, 0.2);
  tr(50, 0.02, 0.2);
  r();

  tt(60, 0.02, 0.2, 100);
  tr(60, 0.02, 0.2);
  tb(50, 0.02, 0.2);
  tb(50, 0.02, 0.2);
  l();
  //////////////////////////////
  tt(50, 0.02, 0.2, 50);
  tb(50, 0.02, 0.2);
  r();

  tt(70, 0.02, 0.2, 150);
  tl(50, 0.02, 0.2);
  l();

  tt(50, 0.02, 0.2, 150);
  tb(50, 0.02, 0.2);
  l();

  ////////////////

  tt(50, 0.02, 0.2, 200);
  tt(80, 0.02, 0.2, 200);
  tb(50, 0.02, 0.2);
  l();
  move(35, 70, 100);

  tb(50, 0.02, 0.2);
  l();
  tl(50, 0.02, 0.2);
  l();

  tb(50, 0.02, 0.2);
  r();

  tt(48, 0.02, 0.2, 2700);

  tb(50, 0.02, 0.2);
  r();

  tb(50, 0.02, 0.2);
  r();

  tr(50, 0.02, 0.2);
  r();


  tt(55, 0.02, 0.2, 670);
  // tb(45, 0.02, 0.2);
  // move(-30,-30,50);
  move(0, 0, 250);


  tt(45, 0.015, 0.2, 400);
  tb(50, 0.02, 0.2);
  l();

  tt(45, 0.015, 0.2, 100);
  tl(50, 0.02, 0.2);
  l();

  tt(45, 0.015, 0.2, 50);
  tl(50, 0.02, 0.2);
  l();

  tt(50, 0.015, 0.2, 150);
  tt(80, 0.015, 0.2, 500);



  // move(50,50,500);
}

void loop() {
  motor(0, 0);
}


void motor(int PowL, int PowR) {
  PowL = (PowL * 255) / 100;
  PowR = (PowR * 255) / 100;
  if (PowL > 0) {
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, HIGH);
    analogWrite(PWM1, PowL);
  } else if (PowL == 0) {
    digitalWrite(INA1, HIGH);
    digitalWrite(INB1, HIGH);
    analogWrite(PWM1, 255);
  } else {
    digitalWrite(INA1, HIGH);
    digitalWrite(INB1, LOW);
    analogWrite(PWM1, -PowL);
  }

  if (PowR > 0) {
    digitalWrite(INA2, LOW);
    digitalWrite(INB2, HIGH);
    analogWrite(PWM2, PowR);
  } else if (PowR == 0) {
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, HIGH);
    analogWrite(PWM2, 0);
  } else {
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    analogWrite(PWM2, -PowR);
  }
}


void move(int a, int b, int c) {
  motor(a, b);
  // motor(2, b);
  delay(c);
}
void read() {
  while (true) {
    readPrivate();
    for (int i = 0; i < numsensor; i++) {
      Serial.print(F[i]);
      Serial.print(",\t");
    }
    Serial.println("");
  }
}

void viewreadline() {
  while (true) {
    // readPrivate();
    for (int i = 0; i < numsensor; i++) {
      Serial.print(F[i]);
      Serial.print(",\t");
    }
    Serial.println(ReadLine());
  }
}
// void run2() {
//   while (true) {
//     if (AL0 > 500 and AL1 > 600 and AL2 > 500 and AL0 > 550) {
//       break;
//     } else {
//       run();
//     }
//   }
// }
void readPrivate() {
  for (int i = 0; i < numsensor; i++) {
    F[i] = analogRead(port[i]);
  }
}
void Read() {
  readPrivate();
  for (int i = 0; i < numsensor; i++) {
    F[i] = map(F[i], Min[i], Max[i], 0, 1000);
    if (F[i] > 1000) {
      F[i] = 1000;
    }
    if (F[i] < 0) {
      F[i] = 0;
    }
    // glcd(i, 0, "%d    ", F[i]);
  }
}

int ReadLine() {
  unsigned long avg = 0, sum = 0;
  int on_line = 0;
  Read();
  for (int j = 0; j < numsensor; j++) {
    if (F[j] > 200) {
      on_line = 1;
    }
    avg = avg + (F[j] * (j * 1000));
    sum = sum + F[j];
  }
  if (on_line == 0) {
    if (last_value < (numsensor - 1) * 1000 / 2) {
      return 0;
    } else {
      return (numsensor - 1) * 1000;
    }
  } else {
    last_value = avg / sum;
  }
  return last_value;
}

void tn(float speed, float kp, float kd) {
  position = ReadLine();
  error = position - 3500;
  powermotor = (error * kp) + (kd * (error - last_error));
  last_error = error;
  leftmotor = speed + powermotor;
  rightmotor = speed - powermotor;
  if (leftmotor > 100) leftmotor = 100;
  if (rightmotor > 100) rightmotor = 100;
  if (leftmotor < -100) leftmotor = -100;
  if (rightmotor < -100) rightmotor = -100;
  move(leftmotor, rightmotor, 0);
}
void tt(float speed, float kp, float kd, long timer) {
  unsigned long lasttime = millis();
  while (millis() - lasttime <= timer) {
    tn(speed, kp, kd);
  }
}

void tu(float speed, float kp, float kd) {
  while (ultra == 1) {
    tn(speed, kp, kd);
  }
}
void tb(float speed, float kp, float kd) {
  ReadLine();
  while (F[0] > 200 or F[7] > 200) {
    tn(speed, kp, kd);
  }
  ReadLine();
  while (F[0] < 500 or F[7] < 500) {
    tn(speed, kp, kd);
  }
}
void tl(float speed, float kp, float kd) {
  ReadLine();
  while (F[0] > 150) {
    tn(speed, kp, kd);
  }
  ReadLine();
  while (F[0] < 700) {
    tn(speed, kp, kd);
  }
}
void tr(float speed, float kp, float kd) {
  ReadLine();
  while (F[7] > 150) {
    tn(speed, kp, kd);
  }
  ReadLine();
  while (F[7] < 700) {
    tn(speed, kp, kd);
  }
}
void l() {
  move(-15, 50, 0);
  ReadLine();
  while (F[0] > 100) {
    ReadLine();
  }
  ReadLine();
  while (F[0] < 300) {
    ReadLine();
  }
}
void r() {
  move(50, -15, 0);
  ReadLine();
  while (F[7] > 100) {
    ReadLine();
  }
  ReadLine();
  while (F[7] < 300) {
    ReadLine();
  }
}