// --- 力を検知するための閾値 ---
const int weakThreshold = 500;
const int mediumThreshold = 640;
const int strongThreshold = 800;

// --- ピンの指定 ---
const int xPin = A0;
const int yPin = A1;
const int zPin = A2;
const int sendPin = 2;  // 割り込み通知用ピン

// --- 動作設定 ---

// --- 状態管理のための変数 ---
enum SwingState { IDLE, SWINGING }; // 「待機中」と「スイング中」の状態を定義
SwingState currentState = IDLE;     // 現在の状態
int peakLevelInSwing = -1;          // 現在のスイングで検出された力の最大レベル
unsigned long lastHitTime = 0;      // 最後にスイングを検出した時刻

void setup() {
  Serial.begin(9600);
  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW);
}

void loop() {
  int x = abs(analogRead(xPin) - 500);
  int y = abs(analogRead(yPin) - 500);
  int z = abs(analogRead(zPin) - 500);
  int strength = x + y + z - 200;

  int currentLevel = -1; // 今回のループでの力のレベル
  if (strength >= strongThreshold) {
    currentLevel = 2;
  } else if (strength >= mediumThreshold) {
    currentLevel = 1;
  } else if (strength >= weakThreshold) {
    currentLevel = 0;
  }

  // --- 3. ステートマシンによるスイング判定 ---
  switch (currentState) {
    case IDLE:
      // 「待機中」にスイングが始まったら (閾値を超えたら)
      if (currentLevel != -1) {
        currentState = SWINGING;        // 状態を「スイング中」へ移行
        peakLevelInSwing = currentLevel;  // ピークレベルを初期化
      }
      break;

    case SWINGING:
      // 「スイング中」の処理
      if (currentLevel != -1) {
        // 現在の力が今までのピークより強ければ、ピークを更新
        if (currentLevel > peakLevelInSwing) {
          peakLevelInSwing = currentLevel;
        }
      } else {
        // スイングが終わったら (力が閾値を下回ったら)
        
        // ★ 検出したピークレベルを送信 ★
        Serial.write(peakLevelInSwing);
        delay(10);

        // ★ 割り込み信号を送信 ★
        digitalWrite(sendPin, HIGH);
        delay(10); // 相手が確実に検知するための保持時間
        digitalWrite(sendPin, LOW);

        delay(700);
        // 最後に振った時刻を記録し、クールダウンを開始
        
        // 状態を「待機中」に戻し、次のスイングに備える
        currentState = IDLE;
      }
      break;
  }
}
