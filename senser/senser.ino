// --- 力を検知するための閾値 ---
const int weakThreshold = 300;
const int mediumThreshold = 550;
const int strongThreshold = 800;

// --- ピンの指定 ---
const int xPin = A0;
const int yPin = A1;
const int zPin = A2;
const int sendPin = 2;  // 割り込み通知用ピン

unsigned long lastHitTime = 0;  // クールダウン用

void setup() {
  Serial.begin(9600);
  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW);
}

void loop() {
  
  // センサから値を取得
  int x = abs(analogRead(xPin) - 500);
  int y = abs(analogRead(yPin) - 500);
  int z = abs(analogRead(zPin) - 500);
  int strength = x + y + z - 200;

  // unsigned long now = millis();

  // // クールダウン期間を設けて同じ振りを連続検出しないようにする
  // if (now - lastHitTime < 750) return;

  // 振りを検知（強さを判定）
  String level = "";
  if (strength >= strongThreshold) {
    level = "STRONG";
  } else if (strength >= mediumThreshold) {
    level = "MEDIUM";
  } else if (strength >= weakThreshold) {
    level = "WEAK";
  }

  if (level != "") {
    Serial.println(level);       // 強さを送信
    delay(10);                   // 通信安定のための短い待機

    digitalWrite(sendPin, HIGH); // 割り込み信号を送信
    delay(50);                   // 相手側に伝わるように少し保持
    digitalWrite(sendPin, LOW);  // 割り込み信号を終了
    delay(700);
    // lastHitTime = now;           // 最終検出時間を更新
  }

  // delay(10);  // 通信負荷軽減
}