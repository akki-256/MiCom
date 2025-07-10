//音を再生する関数
int speakerPin = A0;

int startTime = 0;//サウンド再生時の時間

//弱，中，強を受け取る
void playSound(int strong){
  int startTime = millis();
  switch(strong){
    case 0:
     strongPowerSound();
    case 1:
    middlePowerSound();
    case 2:
    lowPowerSound();
  }
}

void strongPowerSound() {
  tone(A0, 1000);  // 約C6未満
  delay(80);
  tone(A0, 1250);  // D6あたり
  delay(70);
  tone(A0, 1500);  // E6あたり
  delay(60);
  tone(A0, 1750);  // G6近辺
  delay(50);
  tone(A0, 2000);  // 高音フィニッシュ
  delay(120);
  noTone(A0);
}

void middlePowerSound() {
  tone(A0, 1000);
  delay(60);
  tone(A0, 1100);
  delay(120);
  noTone(A0);
}

void lowPowerSound() {
  tone(A0, 900);
  delay(delayNum);
  noTone(A0);
  delay(delayNum);
  tone(A0, 900);
  delay(200);
  noTone(A0);
}
