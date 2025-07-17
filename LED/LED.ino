//LEDアニメーション表示用の関数
//BollaAnime()とshowMatrix()を使ってね！
#include <LedControl.h>

#define ROWS 16
#define COLS 32
 
LedControl lc = LedControl(11, 13, 10, 8);
 
int man[10][8] = {
{0, 1, 1, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 1, 1},
{0, 1, 1, 1, 0, 0, 1, 1},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0, 0},
};
//左上3行８列に貼り付ける
int man_in_the_mirror[10][8] = {
{0, 0, 0, 0, 1, 1, 1, 0},
{1, 1, 0, 0, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0, 1},
};
//左上3行８列に貼り付ける対称図形のため逆から読み込むことで拡張できる
//一列ずつ読み込み前列を削除することにより球が動いているように見せる

//弱の軌道
int parabola_low[5][9]]={
{0, 0, 0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0},
};

int parabola_middle[5][9]]={
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 1, 1, 1, 0, 0, 0},
{0, 1, 1, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0},
};

int parabola_high[5][9]]={
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 0, 0, 0, 0, 0},
};


int matrix[ROWS][COLS]={};
 
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
}
 
void loop() {
  // matrix 全体をクリア
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      matrix[r][c] = 0;
    }
  }
 
  // manを左上、man_in_the_mirrorを右下に表示
  drawPatch(6, 0, man);             // 左上（上段）
  drawPatch(6, 24, man_in_the_mirror);  // 右下（下段）
 
  showMatrix();
  delay(1000);
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

void BollaAnime(){
  if (!isAnimating) return;

  unsigned long now = millis();
  int interval = intervalTable[speedLevel];
  int frame = (now - lastHitMillis) / interval;

  if (frame >= 18) {
    isAnimating = false;
    currentFrame = -1;
    return;
  }

  if (frame != currentFrame) {
    // 軌道配列を選択
    byte (*path)[18] =
      (speedLevel == 0) ? parabola_low :
      (speedLevel == 1) ? parabola_middle :
                          parabola_high;

    // 前の位置を消す（範囲外アクセス防止）
    if (currentFrame >= 0 && currentFrame < 18) {
      for (int r = 0; r < 5; r++) {
        matrix[r + 3][currentFrame + 12] = 0;
      }
    }

    // 新しい位置を描画
    for (int r = 0; r < 5; r++) {
      matrix[r + 3][frame + 12] = path[r][frame];
    }

    currentFrame = frame;
  }
  
}

void showMatrix() {
  //上段
  for(int i = 0; i<4; i++){
    int dev = 3 - i; 
    for (int row = 0; row < 8; row++) {

      lc.setRow(dev, row, convertbit(row,i*8));
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
byte convertbit(int row,int start){
  byte value = 0;
  for (int i = 0; i < 8; i++) {
      value <<= 1;               // 左に1ビットシフト
      value |= matrix[row][start+i];       // ビットを追加
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