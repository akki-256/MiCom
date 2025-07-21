#include "header.h"

int interruptPin = 2;//割り込み信号用ピン　　D2,D3のみ

volatile unsigned int interruptTime;     //割り込み発生時の時間
volatile unsigned int playerMovingTime = 0;  //自分のターンでの振られた時間
short ballSpeed = 0;  //現在のボールのスピード
bool interrupt = false;
bool isBallMovingToCpu;                  //自分のターン
volatile unsigned int soundStartTime = 0;  //効果音が発生した時間
unsigned int cpuTargetTime = 0;
unsigned int cpuMovingTime = 0;

void setup() {
  //割り込み設定(割り込み発火監視ピン，割り込み時走らせる関数，モード)
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
  Serial.begin(9600);
  LEDsetup();
  delay(10);

  while (interruptTime <= 0) {}
  ballSpeed = 1;
  cpuTargetTime = millis() + 2000;
  soundStartTime = millis();
  isBallMovingToCpu = true;
  interrupt = false;
}

void loop() {
  if (isBallMovingToCpu) {
    cpuJudge();  //このときに，isBallMovingToCpuをfalseに
    BollaAnime(ballSpeed,isBallMovingToCpu,playerMovingTime);
  } else {
    if (interrupt) {
      playerJudge();  //この関数の副作用でisBallMovingToCpuをtrueにする
      interrupt = false;
    }
    //プレイヤが降らないと敗北判定できない
    BollaAnime(ballSpeed,isBallMovingToCpu,cpuMovingTime);
  }
  playSound();
  showMatrix();
}

//割り込み関数
void onInterrupt() {
  interrupt = true;
  interruptTime = millis();
  if (!isBallMovingToCpu) playerMovingTime = interruptTime;
}