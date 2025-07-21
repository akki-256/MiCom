#ifndef GLOBALS_H
#define GLOBALS_H

extern volatile unsigned int interruptTime;
extern volatile unsigned int playerMovingTime;
extern short ballSpeed;
extern bool interrupt;
extern bool isBallMovingToCpu;
extern volatile unsigned int soundStartTime;
extern unsigned int cpuTargetTime;
extern unsigned int cpuMovingTime;
extern unsigned int playerTargetTime;

// ===================================
// 関数のプロトタイプ宣言
// ===================================
// 他のファイルから呼び出す関数をここに書いておくと管理しやすい
void LEDsetup();
void BollaAnime(int ballSpeed, bool playerTurn, unsigned int MovingTime);
void showMatrix();
void playerJudge();
void cpuJudge();
void playSound();
void cpuJudge();
void playerJudge();

#endif