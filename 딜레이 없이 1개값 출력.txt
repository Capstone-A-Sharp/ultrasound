#define DIST_S 200*58.2 // 200cm로 제한
#define PING_INTERVAL 25 // Milliseconds (4개의 센서를 100ms 간격으로 측정하기 위해 25ms로 설정)

int trig[4] = {2, 4, 6, 8};  // 트리거 핀 2, 4, 6, 8
int echo[4] = {3, 5, 7, 9};  // 에코 핀 3, 5, 7, 9
uint8_t currentSensor = 0;  
unsigned long pingTimer;
long dist_r[4];
int num;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {  // 4개의 센서 초기화
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
  pingTimer = millis();
}

void loop() {
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += PING_INTERVAL;  // Set the next ping time.
    dist_r[num] = trig_ultra(trig[num], echo[num]);
    num++;      
  }
  if (num > 3) { num = 0; oneSensorCycle(); }
}

long trig_ultra(int TRIG, int ECHO) {
  long dist;
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  dist = pulseIn(ECHO, HIGH, DIST_S) / 58.2;
  return dist;
}

void oneSensorCycle() {
  bool found = false;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (abs(dist_r[i] - dist_r[j]) <= 5 && dist_r[i]!=0 && dist_r[j]!=0) { // ±5cm 이내인지 확인, 0값 날리기
        if (!found) {
          found = true;
        }
        Serial.print((dist_r[i]+dist_r[j])/2);
        Serial.println("cm");
      }
    }
  }
  if (!found) {
    Serial.println("Error");
  }
}
