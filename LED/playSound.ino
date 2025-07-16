//音を再生する関数

const int speakerPin = A0;　//スピーカ接続用ピン

//弱，中，強を受け取る
void playSound(int strong) {
  unsigned long currentTime = millis() - interruptTime;         //割り込みから何ms経っているか
  switch (strong) {
    case 0://強
      strongPowerSound(currentTime);
      break;
    case 1://中
      middlePowerSound(currentTime);
      break;
    case 2://弱
      lowPowerSound(currentTime);
      break;
  }
}

void strongPowerSound(unsigned long currentTime) {
  if (currentTime < 80) {
    tone(speakerPin, 1000);
  } else if (currentTime < 150) {
    tone(speakerPin, 1250);
  } else if (currentTime < 210) {
    tone(speakerPin, 1500);
  } else if (currentTime < 270) {
    tone(speakerPin, 1750);
  } else if (currentTime < 390) {
    tone(speakerPin, 2000);
  } else {
    noTone(speakerPin);
  }
}

void middlePowerSound(unsigned long currentTime) {
  if (currentTime < 60) {
    tone(speakerPin, 1000);
  } else if (currentTime < 180) {
    tone(speakerPin, 1100);
  } else {
    noTone(speakerPin);
  }
}

void lowPowerSound(unsigned long currentTime) {
  if (currentTime < 20) {
    tone(speakerPin, 900);
  } else if (currentTime < 40) {
    noTone(speakerPin);
  } else if (currentTime < 240) {
    tone(speakerPin, 900);
  } else {
    noTone(speakerPin);
  }
}
