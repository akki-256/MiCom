#include "header.h"
#include <LedControl.h>

#define ROWS 16
#define COLS 32

LedControl lc = LedControl(11, 13, 10, 8);

bool isAnimating = true;                                           //アニメーションを描写するかどうか
const int intervalTable[3] = { 3000 / 16, 2000 / 16, 1000 / 16 };  //ドットが移動するまでのインターバル
int currentFrame = -1;                                             // 今のボール位置（0〜8列）初期値を-1として宣言すること

int man[10][8] = {
  { 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 0, 1, 0, 0, 1, 1 },
  { 0, 1, 1, 1, 0, 0, 1, 1 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 0, 1, 1, 0, 0, 0 },
  { 1, 1, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0 },
};

int matrix[ROWS][COLS] = {};

void LEDsetup() {
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  drawPatch(6, 0, man);  // 左上（上段）
  int mirror[10][8];
  man_in_the_mirror(mirror, man);
  drawPatch(6, 24, mirror);  // 右下（下段）
  showMatrix();
}

// matrixへ8×10の画像を貼り付け
void drawPatch(int destRow, int destCol, int src[10][8]) {
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 8; c++) {
      int row = destRow + r;
      int col = destCol + c;
      if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        matrix[row][col] = src[r][c];
      }
    }
  }
}

void man_in_the_mirror(int dest[10][8], int src[10][8]) {
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 8; c++) {
      dest[r][7 - c] = src[r][c];
    }
  }
}

void BollaAnime(int ballSpeed, bool isBallMovingToCpu, long MovingTime) {
  if (!isAnimating) return;

  //弱の軌道
  int parabola_low[5][16] = {
    { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  };
  unsigned long now = millis();
  int interval = intervalTable[ballSpeed];
  int frame;
  if (!isBallMovingToCpu) {
    frame = 15 - (now - MovingTime) / interval;
  } else {
    frame = (now - MovingTime) / interval;
  }

  if (frame >= 16 || frame <= -1) {
    isAnimating = false;
    currentFrame = -1;
    return;
  }
  if (frame != currentFrame) {
    // 前の位置を消す（範囲外アクセス防止）
    if (currentFrame >= 0 && currentFrame < 16) {
      for (int r = 0; r < 5; r++) {
        matrix[r + 3][currentFrame + 8] = 0;
      }
    }

    // 新しい位置を描画
    for (int r = 0; r < 5; r++) {
      matrix[r + 3][frame + 8] = parabola_low[r][frame];
    }
    currentFrame = frame;
  }
}

void clearBall() {
  // ボールが描画される可能性のある中央エリアを全て0にする
  // 範囲は matrix の8列目から23列目まで (16列分)
  for (int r = 3; r < 8; r++) { // ボールが描画される縦の範囲
    for (int c = 8; c < 24; c++) { // ボールが描画される横の範囲
      matrix[r][c] = 0;
    }
  }
  currentFrame = -1; // フレーム位置も確実にリセット
}

void showMatrix() {
  //上段
  for (int i = 0; i < 4; i++) {
    int dev = 3 - i;
    for (int row = 0; row < 8; row++) {
      lc.setRow(dev, row, convertbit(row, i * 8));
    }
  }
  //下段
  for (int i = 0; i < 4; i++) {
    int dev = 4 + i;
    for (int row = 0; row < 8; row++) {
      int flippedRow = 7 - row;  // 上下反転
      lc.setRow(dev, row, convertbitFlipCol(flippedRow + 8, i * 8));
    }
  }
}

//配列をビット列に変換 左→右
byte convertbit(int row, int start) {
  byte value = 0;
  for (int i = 0; i < 8; i++) {
    value <<= 1;                      // 左に1ビットシフト
    value |= matrix[row][start + i];  // ビットを追加
  }
  return value;
}

// 下段用：右→左（左右反転）
byte convertbitFlipCol(int row, int start) {
  byte value = 0;
  for (int i = 7; i >= 0; i--) {
    value <<= 1;
    value |= matrix[row][start + i];
  }
  return value;
}