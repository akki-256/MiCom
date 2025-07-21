#include "header.h"

unsigned int playerTargetTime = 0;  //プレイヤー打つタイミングの時間
unsigned int waitTime[] = { 3000, 2000, 1000 };

void playerJudge() {
  if (playerTargetTime > playerMovingTime + 1000) return;  //空振りしてるがまだ振れる時
  int racketStrong = -1;                                   // 初期値は-1
  if (Serial.available() > 0) racketStrong = Serial.read();
  // 読み取れなかった場合は、何もせずに関数を抜ける
  if (racketStrong == -1) return;

  switch (racketStrong) {
    case 0:  //弱
      if (abs(playerMovingTime - playerTargetTime) < 500) {
        ballSpeed = 0;
        cpuTargetTime = millis() + 3000;
      } else {
        //GAMEOVER
      }
      break;
    case 1:  //中
      if (abs(playerMovingTime - playerTargetTime) < 400) {
        ballSpeed = 1;
        cpuTargetTime = 1500 + millis();
      } else if (abs(playerMovingTime - playerTargetTime) < 700) {
        ballSpeed = 0;
        cpuTargetTime = millis() + 1000;
      } else {
        //Gamsover
      }
      break;
    case 2:  //強
      if (abs(playerMovingTime - playerTargetTime) < 300) {
        ballSpeed = 2;
        cpuTargetTime = millis() + 1000;
      } else if (abs(playerMovingTime - playerTargetTime) < 550) {
        ballSpeed = 1;
        cpuTargetTime = millis() + 1500;
      } else if (abs(playerMovingTime - playerTargetTime) < 800) {
        ballSpeed = 0;
        cpuTargetTime = millis() + 1000;
      } else {
        //Gamevoer
      }
      break;
  }

  soundStartTime = millis();
  isBallMovingToCpu = true;
}

void cpuJudge() {
  if (millis() + 200 > cpuTargetTime) {  //200くらいなら早まってもよし
    if (random(0, 10) < 2) return;       //playerWin
    ballSpeed = random(0, 3);
    isBallMovingToCpu = false;
    playerTargetTime = millis() + waitTime[ballSpeed];
    soundStartTime = millis();
  }
}