// --- 力を検知するための閾値 ---
const int thresholdWeak = 300;
const int thresholdMedium = 550;
const int thresholdStrong = 800;

// --- ピンの指定 ---
const int xPin = A0;
const int yPin = A1;
const int zPin = A2;
const int sendPin = 2;  // 割り込み信号を送るピン(D2)

// --- 状態管理 ---
bool sentFlag = false;        // 重複送信防止用フラグ
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW); // 初期状態はLOW
}

void loop() {
  // センサから値を取得
  int x = abs(analogRead(xPin) - 500);
  int y = abs(analogRead(yPin) - 500);
  int z = abs(analogRead(zPin) - 500);
  int strength = x + y + z - 200;

  // 振ったことを検知（一定の時間を空ける）
  if (!sentFlag && strength > thresholdWeak) {
    String level = "";

    if (strength >= thresholdStrong) {
      level = "STRONG";
    } else if (strength >= thresholdMedium) {
      level = "MEDIUM";
    } else if (strength >= thresholdWeak) {
      level = "WEAK";
    }

    // シリアル通信でLED側に送信（振った強さを送る）
    Serial.print("HIT:");
    Serial.println(level);

    // 割り込み信号をHIGHで出力（相手が受け取ったらLOWに戻す）
    digitalWrite(sendPin, HIGH);
    delay(10);  // 割り込み検出のために短時間HIGH
    digitalWrite(sendPin, LOW);

    sentFlag = true;
    lastSendTime = millis();
  }

  // クールダウン（同じ振りを何度も検知しないように）
  if (sentFlag && millis() - lastSendTime > 750) {
    sentFlag = false;
  }

  delay(50); // 読み取り間隔調整
}
