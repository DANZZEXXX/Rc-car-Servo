// ==========================================
// KODE ARDUINO (RECEIVER DI MOBIL RC)
// ==========================================
#include <Servo.h>

// Pin Motor Driver L298N
#define IN1 4
#define IN2 6
#define IN3 8
#define IN4 9

Servo servoKananKiri; // Pin 3 (S3)
Servo servoAtasBawah; // Pin 5 (S5)
Servo servoMajuMundur;// Pin 11 (S11)
Servo servoCapit;     // Pin 10 (S10)

char rcCmd;
int s3, s5, s11, s10;

void setup() {
  Serial.begin(9600); // Baudrate HC-06

  // Setup Pin Motor Driver jadi OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Setup Pin Servo
  servoKananKiri.attach(3);
  servoAtasBawah.attach(5);
  servoMajuMundur.attach(11);
  servoCapit.attach(10);

  // Posisikan ke tengah saat nyala
  servoKananKiri.write(90);
  servoAtasBawah.write(90);
  servoMajuMundur.write(90);
  servoCapit.write(0); 

  berhenti(); // Pastikan mobil ga jalan sendiri pas dinyalain
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');

    if (data.startsWith("<") && data.indexOf(">") > 0) {
      data.replace("<", "");
      data.replace(">", "");

      // Baca 1 Huruf (Perintah RC) dan 4 Angka (Sudut Servo)
      sscanf(data.c_str(), "%c,%d,%d,%d,%d", &rcCmd, &s3, &s5, &s11, &s10);

      // --- 1. GERAKKAN SERVO CAPIT ---
      servoKananKiri.write(s3);
      servoAtasBawah.write(s5);
      servoMajuMundur.write(s11);
      servoCapit.write(s10);

      // --- 2. GERAKKAN BAN MOBIL ---
      if (rcCmd == 'F') maju();
      else if (rcCmd == 'B') mundur();
      else if (rcCmd == 'R') belokKanan();
      else if (rcCmd == 'L') belokKiri();
      else berhenti();
    }
  }
}

// ==========================================
// FUNGSI MOTOR DRIVER RC
// (Kalau ban kebalik arahnya, tinggal tukar HIGH jadi LOW di sini)
// ==========================================

void maju() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKanan() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
