int interruptPin = 2;  //割り込み信号用ピン　　D2,D3のみ

volatile unsigned interruptTime = 0; //割り込み発生時の時間
volatile unsigned playerMovingTime = 0;  //相手のターンでの割り込み発生時．音の再生，判定で使用
bool isAnimating = false;               //アニメーションの動き
int playerStrong = -1;  //0:弱,1:中,2:強
int cpuStrong = -1;
bool playerTurn;//自分のターン

void setup() {
  //割り込み設定(割り込み発火監視ピン，割り込み時走らせる関数，モード)
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  // manを左上、man_in_the_mirrorを右下に表示
  drawPatch(6, 0, man);                 // 左上（上段）
  drawPatch(6, 24, man_in_the_mirror);  // 右下（下段）
  while (interruptTime <= 0) {
  }
  playerStrong = 1;
  playerTurn = true;
}

void loop() {
  if (playerTurn) {
    //プレイヤーが打った後
    playSound(playerStrong, playerMovingTime);
    cpuStrong = couJudge();  //適当なタイミングでplayerTurnをfalseにする
  } else {
    //プレイヤーがこれから打つ
    playSound(cpuStrong, cpuTime);
    playerStrong = judge(interruptTime);  //この関数の副作用でplayerTurnをtrueにする
  }

  showMatrix();
}

void onInterrupt() {
  interruptTime = millis();
  if (!playerTurn) playerMovingTime = interruptTime;
}