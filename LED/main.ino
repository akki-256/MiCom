int interruptPin = 2;  //割り込み信号用ピン　　D2,D3のみ

volatile unsigned interruptTime = 0;  //割り込みが発生したかどうかを格納する　loop内で初期化予定

void setup() {
  //割り込み設定(割り込み発火監視ピン，割り込み時走らせる関数，モード)
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
  Serial.begin(9600);
}

void loop() {
  if (interruptFLG && Serial.available()) {
    interruptFLG = false;
    judge(Serial.read());
  }
}

void onInterrupt() {
  interruptTime = millis();
}