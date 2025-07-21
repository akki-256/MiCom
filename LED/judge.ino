#include "header.h"

long playerTargetTime = 0;  //プレイヤー打つタイミングの時間
unsigned int waitTime[] = { 3000, 2000, 1000 };

void playerJudge() {
  if (playerTargetTime > playerMovingTime + 200) return;
  int racketStrong = -1;
  if (Serial.available() > 0) racketStrong = Serial.read();
  if (racketStrong == -1) return;

  switch (racketStrong) {
    case 0:  //弱
      if (abs(playerMovingTime - playerTargetTime) < 500) {
        ballSpeed = 0;
        cpuTargetTime = millis();
        cpuTargetTime += 3000;
      } else {
        Serial.println("GAMEOVER");
        resetFunc();
      }
      break;
    case 1:  //中
      Serial.println("評価");
      if (abs(playerMovingTime - playerTargetTime) < 400) {
        ballSpeed = 1;
        cpuTargetTime = millis();
        cpuTargetTime += 1500;
      } else if (abs(playerMovingTime - playerTargetTime) < 700) {
        ballSpeed = 0;
        cpuTargetTime = millis();
        cpuTargetTime += 1000;
      } else {
        Serial.println("GAMEOVER");
        resetFunc();
      }
      break;
    case 2:  //強
      if (abs(playerMovingTime - playerTargetTime) < 300) {
        ballSpeed = 2;
        cpuTargetTime = millis();
        cpuTargetTime += 1000;
      } else if (abs(playerMovingTime - playerTargetTime) < 550) {
        ballSpeed = 1;
        cpuTargetTime = millis();
        cpuTargetTime += 1500;
      } else if (abs(playerMovingTime - playerTargetTime) < 800) {
        ballSpeed = 0;
        cpuTargetTime = millis();
        cpuTargetTime += 1000;
      } else {
        Serial.println("GAMEOVER");
        resetFunc();
      }
      break;
    default:
      Serial.println("想定外の文字");
  }

  soundStartTime = millis();
  isBallMovingToCpu = true;
  clearBall();
  isAnimating = true;
}

void cpuJudge() {
  if (millis() > cpuTargetTime - 70) {  //70くらいなら早まってもよし
    if (random(0, 10) < 2) {
      Serial.println("YOU WIN");
      resetFunc();
    }
    ballSpeed = random(0, 3);
    isBallMovingToCpu = false;
    cpuMovingTime = millis();
    playerTargetTime = millis();
    playerTargetTime += waitTime[ballSpeed];
    soundStartTime = millis();
    clearBall();
    isAnimating = true;
  }
}