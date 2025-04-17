#define DIST_S 80 * 58.2 // 80cm로 제한
#define PING_INTERVAL 25  // 4개의 센서를 100ms 간격으로 측정하기 위해 25ms로 설정

int trig[4] = {2, 4, 6, 8}; // 트리거 핀 2, 4, 6, 8
int echo[4] = {3, 5, 7, 9}; // 에코 핀 3, 5, 7, 9
unsigned long pingTimer;
unsigned long lastPrintTime = 0; // 마지막 출력 시간
long dist_r[4];
int num = 0;
long checkpoint = 0; // ±3cm 이내의 값이 없을 때 표시할 변수
int flag = 0; // 네 번째 센서가 20 이하일 때 플래그 설정

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) { // 4개의 센서 초기화
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
  pingTimer = millis();
}

void loop() {
  if (millis() >= pingTimer) { // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += PING_INTERVAL; // Set the next ping time.
    dist_r[num] = trig_ultra(trig[num], echo[num]);
    num++;
  }
  if (num > 3) {
    num = 0;
    if (millis() - lastPrintTime >= 1000) { // 1초마다 출력
      oneSensorCycle();
      lastPrintTime = millis();
    }
  }
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

// ±5cm 이내로 차이 나는 값을 찾는 함수
void oneSensorCycle() {
  int similarCount = 0; // 몇개 값이 일치하는지 확인용
  long total = 0; // 평균내기 위해 합계용
  long sum =0; // 에러 탐지용

  // 3개의 센서 비교
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      if (abs(dist_r[i] - dist_r[j]) <= 5 && dist_r[i] != 0 && dist_r[j] != 0) { // ±5cm 이내인지 확인
        total += dist_r[i] + dist_r[j];
        similarCount += 2;
      }
    }
  }

  
  // 네 번째 센서가 20 미만일 경우 flag 설정
  if (dist_r[3] < 20 && dist_r[3] != 0 && (dist_r[0]<23 || dist_r[1]<23 || dist_r[2]<23)) {
    flag = 1;
    checkpoint=dist_r[3];
    Serial.print(checkpoint);
    Serial.print("cm ");
    Serial.println("slow down.");
    return;
  }
  else {
    flag = 0;
  }

  // 3개의 값이 비슷한 경우 평균 계산
  if (similarCount == 6) { // 모든 3개 센서가 비슷한 경우
    checkpoint = total / 6;
    Serial.print(checkpoint);
    Serial.println("cm");
  }
  // 2개의 값만 비슷한 경우 평균 계산
  else if (similarCount == 2) {
    checkpoint = total / 2;
    Serial.print(checkpoint);
    Serial.println("cm (one error)");
  }
  // 하나의 센서 값만 정상인 경우에도 그 값 출력
  else if (similarCount == 0 && (dist_r[0] != 0 || dist_r[1] != 0 || dist_r[2] != 0 || dist_r[3] != 0)) {
    for (int i = 0; i < 3; i++) {
      if (dist_r[i] != 0) {
        Serial.print(dist_r[i]);
        Serial.println("cm (two error)");
        break;
      }
    }
  }
  
  // 전부 다 0 값인 우
  for (int i = 0; i < 3; i++) {
      sum+=dist_r[i];
  }
  if(sum==0){
    Serial.print(dist_r[0]);
    Serial.print("cm ");
    Serial.println("error");
  }
}