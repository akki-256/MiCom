int interruptPin = 2;  //割り込み信号用ピン　　D2,D3のみ

volatile unsigned interruptTime = 0;     //割り込み発生時の時間
volatile unsigned playerMovingTime = 0;  //自分のターンでの振られた時間
bool isAnimating = false;                //アニメーションが動いているか
short ballSpeed = -1;  //現在のボールのスピード
bool interrupt = false;
bool playerTurn;                  //自分のターン
unsigned int soundStartTime = 0;  //効果音が発生した時間

void setup() {
  //割り込み設定(割り込み発火監視ピン，割り込み時走らせる関数，モード)
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  // manを左上、man_in_the_mirrorを右下に表示
  drawPatch(6, 0, man);                 // 左上（上段）
  drawPatch(6, 24, man_in_the_mirror);  // 右下（下段）
  delay(10);

  //ユーザにサーブを打たせる
  while (interruptTime <= 0) {}
  ballSpeed = 1;
  cpuTargetTime = millis()+//球のスピードが中のときの時間
  soundStartTime = millis();
  playerTurn = true;
  interrupt = false;
}

void loop() {
  if (playerTurn) {
    //プレイヤーが打った後，その時間を記憶し，
    //その時間からプレイヤーからの球の強さを加味したタイミングを計算，ランダムな強さで球を返す
    cpuStrong = couJudge();  //このときに，playerTurnをfalseに
  } else {
    //cpuが打った後，その時間を記録し
    //プレイヤが振った後，適切に振られていることをチェック
    if (interrupt && !playerTurn) {
      playerJadge();  //この関数の副作用でplayerTurnをtrueにする
      interrupt = false;
    }
  }

  playSound(ballSpeed);
  playerMove();            //プレイヤが振った時に画面上の人も動作を行う
  BollaAnime(playerTurn);  //playerTurnがtrueならボールの起動はプレイヤ→cpu，falseならボールの起動はcpu→プレイヤ
  showMatrix();
}

//割り込み関数
void onInterrupt() {
  //現在の状態を取得
  interrupt = true;
  interruptTime = millis();
  //打ち返すタイミング用の現在時刻の確保
  if (!playerTurn) playerMovingTime = interruptTime;
}