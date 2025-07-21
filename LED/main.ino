#include "header.h"

int interruptPin = 2;  //割り込み信号用ピン　　D2,D3のみ

volatile long interruptTime = 0;     //割り込み発生時の時間
volatile long playerMovingTime = 0;  //自分のターンでの振られた時間
short ballSpeed = 0;                 //現在のボールのスピード
bool interrupt = false;
bool isBallMovingToCpu;            //自分のターン
volatile long soundStartTime = 0;  //効果音が発生した時間
unsigned long cpuTargetTime = 0;
long cpuMovingTime = 0;

void setup() {
  //割り込み設定(割り込み発火監視ピン，割り込み時走らせる関数，モード)
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
  Serial.begin(9600);
  LEDsetup();

  const int UNUSED_ANALOG_PIN = A3;
  randomSeed(analogRead(UNUSED_ANALOG_PIN));

  interruptTime = 0;
  delay(10);

  while (interruptTime == 0) {}
  ballSpeed = 1;
  cpuTargetTime = millis() + 2000;
  soundStartTime = millis();
  isBallMovingToCpu = true;
  interrupt = false;
}

void loop() {
  if (isBallMovingToCpu) {
    BollaAnime(ballSpeed, isBallMovingToCpu, playerMovingTime);
    cpuJudge();  //このときに，isBallMovingToCpuをfalseに
  } else {
    BollaAnime(ballSpeed, isBallMovingToCpu, cpuMovingTime);
    if (interrupt) {
      playerJudge();                                                      //この関数の副作用でisBallMovingToCpuをtrueにする
      interrupt = false;
    }
    if (millis() > (unsigned int)playerTargetTime + 1000) resetFunc();  //call reset
  }
  playSound();
  showMatrix();
}

//割り込み関数
void onInterrupt() {
  interrupt = true;
  interruptTime = millis();
  if (!isBallMovingToCpu) {
    playerMovingTime = interruptTime;
  }
}