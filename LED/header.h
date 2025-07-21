#ifndef GLOBALS_H
#define GLOBALS_H

extern volatile long interruptTime;
extern volatile long playerMovingTime;
extern short ballSpeed;
extern bool interrupt;
extern bool isBallMovingToCpu;
extern volatile long soundStartTime;
extern unsigned long cpuTargetTime;
extern long cpuMovingTime;
extern long playerTargetTime;

// ===================================
// 関数のプロトタイプ宣言
// ===================================
// 他のファイルから呼び出す関数をここに書いておくと管理しやすい
void (*resetFunc)(void) = 0;  //declare reset function @ address 0
void LEDsetup();
void BollaAnime(int ballSpeed, bool playerTurn, unsigned int MovingTime);
void showMatrix();
void playerJudge();
void cpuJudge();
void playSound();
void cpuJudge();
void playerJudge();
void clearBall();

#endif