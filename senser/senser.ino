//力を検知するための閾値はこのように指定してください
//int strong = 

//ピンの指定もここでお願いします
//int xPin = 
//int yPin = 
//int zPin = 
//int sendPin = 割り込み用のピン

void setup() {
  Serial.begin(9600);
}

void draw() {
  //センサから値を取得

  //振ったことを検知

  //シリアル通信でLED側に送信(ピン未定:振った強さ)，割り込みを発生させるフラグを送信（ピン未定:High or Low）
}