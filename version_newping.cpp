#include <NewPing.h>

// 초음파 센서 핀 설정
#define TRIG_PIN1 2
#define ECHO_PIN1 3
#define TRIG_PIN2 4
#define ECHO_PIN2 5
#define TRIG_PIN3 6
#define ECHO_PIN3 7
#define TRIG_PIN4 8
#define ECHO_PIN4 9

#define MAX_DISTANCE 1000 // 최대 거리 설정 (cm)

// NewPing 객체 생성
NewPing sonar1(TRIG_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIG_PIN3, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIG_PIN4, ECHO_PIN4, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50); // 각 측정 사이에 약간의 지연 추가

  // 각 센서에서 거리 측정
  long distance1 = sonar1.ping_cm();
  long distance2 = sonar2.ping_cm();
  long distance3 = sonar3.ping_cm();
  long distance4 = sonar4.ping_cm();

  // 센서 1 거리 출력
  Serial.print("Sensor 1 Distance: ");
  if (distance1 == 0) {
    Serial.print("Error");
  } else {
    Serial.print(distance1);
    Serial.print(" cm");
  }

  Serial.print(" | Sensor 2 Distance: ");
  if (distance2 == 0) {
    Serial.print("Error");
  } else {
    Serial.print(distance2);
    Serial.print(" cm");
  }

  Serial.println(); // 줄 바꿈 추가

  // 센서 3 거리 출력
  Serial.print("Sensor 3 Distance: ");
  if (distance3 == 0) {
    Serial.print("Error");
  } else {
    Serial.print(distance3);
    Serial.print(" cm");
  }

  Serial.print(" | Sensor 4 Distance: ");
  if (distance4 == 0) {
    Serial.print("Error");
  } else {
    Serial.print(distance4);
    Serial.print(" cm");
  }

  Serial.println();
  delay(1000); // 1초마다 측정
}
