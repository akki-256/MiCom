//LEDアニメーション表示用の関数
//BollaAnime()とshowMatrix()を使ってね！

//BollaAnime()について
//アニメーションを描写するかどうか管理する変数を用意してね！本ぷろぐらむisAnimatingにあたる
//打たれた時間を保存する変数を用意してね！本プログラムlastHitMillisにあたる
//スピードを管理する変数を用意してね！本プログラムspeedLevelにあたる
//誰のターンか管理する変数を用意してね！本ぷろぐらむplayerturnにあたる
//以上の変数をグローバル関数として定義するか引数として定義して
//以下BollaAnime()でしか参照しないであろうグローバル変数一覧
//parabola_low,parabola_middle,parabola_high,intervalTable,currentFrame

//showMatrix()について


#include <LedControl.h>

#define ROWS 16
#define COLS 32

LedControl lc = LedControl(11, 13, 10, 8);


bool isAnimating = false;                 //アニメーションを描写するかどうか
unsigned long lastHitMillis = 3000;     // 打ち返した時刻
int speedLevel = 2;                  // 0: low, 1: middle, 2: high
bool playerturn=false;            //誰のターンか管理する変数

//BollaAnime()でしか参照しないであろうグローバル変数
const int intervalTable[3] = {900, 700, 500};//ドットが移動するまでのインターバル
int currentFrame = -1;            // 今のボール位置（0〜8列）初期値を-1として宣言すること
//左上3行８列に貼り付ける．対称図形のため逆から読み込むことで拡張できるkedoそのまま書いた
//一列ずつ読み込み前列を削除することにより球が動いているように見せる
//弱の軌道
int parabola_low[5][16]={
{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};
//中の軌道
int parabola_middle[5][16]={
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};
//強の軌道
int parabola_high[5][16]={
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
};

 
int man[10][8] = {
{0, 1, 1, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 1, 1},
{0, 1, 1, 1, 0, 0, 1, 1},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 0, 0, 0, 0},
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
{0, 0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0, 1},

};


int matrix[ROWS][COLS]={};

//確認用
// void setup(){
//   LEDsetup();
//   while (!Serial);
// }
// void loop(){
//   if(millis()>3000&&millis()<19000){
//     isAnimating=true;
//   }
//   LEDloop();
// }

void LEDsetup(){
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  // manを左上、man_in_the_mirrorを右下に表示
  drawPatch(6, 0, man);             // 左上（上段）
  drawPatch(6, 24, man_in_the_mirror);  // 右下（下段）
}

void LEDloop(){
  BollaAnime();

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

void BollaAnime() {
  if (!isAnimating) return;

  unsigned long now = millis();
  int interval = intervalTable[speedLevel];
  int frame;
  if(playerturn){
    frame = 15-(now - lastHitMillis) / interval;
  }else{
    frame = (now - lastHitMillis) / interval;
  }

  if (frame >= 16||frame <= -1) {
    isAnimating = false;
    currentFrame = -1;
    return;
  }
  if (frame != currentFrame) {
    // 軌道配列を選択
    int (*path)[16] =
      (speedLevel == 0) ? parabola_low :
      (speedLevel == 1) ? parabola_middle :
                          parabola_high;

    // 前の位置を消す（範囲外アクセス防止）
    if (currentFrame >= 0 && currentFrame < 16) {
      for (int r = 0; r < 5; r++) {
        matrix[r + 3][currentFrame + 8] = 0;
      }
    }

    // 新しい位置を描画
    for (int r = 0; r < 5; r++) {
      matrix[r + 3][frame + 8] = path[r][frame];
    }
    currentFrame = frame;
  }
}

void showMatrix() {
  //上段
  for (int i = 0; i < 4; i++) {
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

