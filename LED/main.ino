int interruptPin = 2;  //割り込み信号用ピン　　D2,D3のみ

volatile unsigned interruptTime = 0;  //割り込みが発生したかどうかを格納する　loop内で初期化予定
bool isAnimating = false;

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
  drawPatch(6, 0, man);             // 左上（上段）
  drawPatch(6, 24, man_in_the_mirror);  // 右下（下段）
}

void loop() {
  if (interruptFLG && Serial.available()) {
    interruptFLG = false;
    judge(Serial.read());
  }
  BollaAnime();
  showMatrix();
}

void onInterrupt() {
  interruptTime = millis();
}