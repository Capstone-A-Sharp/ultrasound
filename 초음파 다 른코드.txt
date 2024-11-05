// 초음파 센서 핀 설정
int trigPin1 = 2;
int echoPin1 = 3;
int trigPin2 = 4;
int echoPin2 = 5;
int trigPin3 = 7;
int echoPin3 = 6;
int trigPin4 = 8;
int echoPin4 = 9;

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 300000);
  if (duration == 0) {
    return -1; // 측정 실패 시 -1 반환
  }
  long distance = (duration * 0.034) / 2;
  delay(10);
  if(distance <400){
    return distance;
  }
  return -1;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
}

void loop() {
  long distance1 = measureDistance(trigPin1, echoPin1);
  long distance2 = measureDistance(trigPin2, echoPin2);
  long distance3 = measureDistance(trigPin3, echoPin3);
  long distance4 = measureDistance(trigPin4, echoPin4);

  Serial.print("Sensor 1 Distance: ");
  if (distance1 == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distance1);
    Serial.print(" cm");
  }

  Serial.print(" | Sensor 2 Distance: ");
  if (distance2 == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distance2);
    Serial.print(" cm");
  }

  Serial.println(); // 줄 바꿈 추가

  Serial.print("Sensor 3 Distance: ");
  if (distance3 == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distance3);
    Serial.print(" cm");
  }

  Serial.print(" | Sensor 4 Distance: ");
  if (distance4 == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distance4);
    Serial.print(" cm");
  }

  Serial.println();
  Serial.println();
  delay(1000); // 1초마다 측정
}
