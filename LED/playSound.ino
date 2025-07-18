//音を再生する関数

const int speakerPin = 0;//スピーカ接続用ピン

//弱，中，強を受け取る
void playSound() {
  if(soundStartTime == 0)return;
  unsigned long time = millis() - soundStartTime;         //割り込みから何ms経っているか
  switch (ballSpeed) {
    case 0://強
      strongPowerSound(time);
      break;
    case 1://中
      middlePowerSound(time);
      break;
    case 2://弱
      lowPowerSound(time);
      break;
  }
}

void strongPowerSound(unsigned long time) {
  if (time < 80) {
    tone(speakerPin, 1000);
  } else if (time < 150) {
    tone(speakerPin, 1250);
  } else if (time < 210) {
    tone(speakerPin, 1500);
  } else if (time < 270) {
    tone(speakerPin, 1750);
  } else if (time < 390) {
    tone(speakerPin, 2000);
  } else {
    noTone(speakerPin);
    soundStartTime = 0;
  }
}

void middlePowerSound(unsigned long time) {
  if (time < 60) {
    tone(speakerPin, 1000);
  } else if (time < 180) {
    tone(speakerPin, 1100);
  } else {
    noTone(speakerPin);
    soundStartTime = 0;
  }
}

void lowPowerSound(unsigned long time) {
  if (time < 20) {
    tone(speakerPin, 900);
  } else if (time < 40) {
    noTone(speakerPin);
  } else if (time < 240) {
    tone(speakerPin, 900);
  } else {
    noTone(speakerPin);
    soundStartTime = 0;
  }
}
