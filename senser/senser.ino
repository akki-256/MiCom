void setup() {
  // size(500, 300);
  // arduino = new Arduino(this, "/dev/cu.usbserial-14P54815", 57600);

  // myFont = loadFont("CourierNewPSMT-48.vlw");
  // textFont(myFont, 20);
}

void draw() {
//   background(0);
//   fill(255);
//   text("Tennis Game", 20, 30);
//   text("Player: " + p1Score + "  CPU: " + cpuScore, 20, 60);

// //勝敗決定
//   if (gameOver) {
//     text("Game Over", 160, 150);
//     if (p1Score >= 5) {
//       text("Player Wins!", 160, 180);//勝ってるのにゲームオーバーはなんか違くない？Game setとかならしっくりきそう
//     } else if (cpuScore >= 5) {
//       text("CPU Wins!", 160, 180);
//     }
//     return;
//   }

//   //cpuのターンであれば何もしない(cpuのターン中にも振ったらアニメーションを表示するとしたらもう少し下でこの処理)
//   if (cpuTurn && millis() >= cpuActionTime) {
//     cpuHit();
//   }


//   // int p1x = arduino.analogRead(0) - 502;
//   // int p1y = arduino.analogRead(1) - 516;
//   // int p1z = arduino.analogRead(2) - 748;
//   // float p1Strength = sqrt(p1x * p1x + p1y * p1y + p1z * p1z);
  
//   int p1x = abs(arduino.analogRead(0) - 500);
//   int p1y = abs(arduino.analogRead(1) - 500);
//   int p1z = abs(arduino.analogRead(2) - 500);
//   float p1Strength = p1x+p1y+p1z-200;

// //クールダウンなら何も
//   if (millis() - p1LastTime < cooldownMillis) return;

// //打ち返し
//   if (p1Strength > threshold && p1CanHit && !cpuTurn) {
//     if (!awaitingSecondInput) {
//       // サーブ
//       if (p1Strength > strongThreshold) {
//         println("P1: 強 (1st)");
//         baseTime = 1.0;
//         lastP1Strength = "強";
//       } else if (p1Strength > mediumThreshold) {
//         println("P1: 中 (1st)");
//         baseTime = 2.0;
//         lastP1Strength = "中";
//       } else if (p1Strength > weakThreshold) {
//         println("P1: 弱 (1st)");
//         baseTime = 3.0;
//         lastP1Strength = "弱";
//       } else {
//         return;
//       }
//       startTime = millis();
//       awaitingSecondInput = true;
//       cpuTurn = true;
//       cpuActionTime = millis() + int(baseTime * 1000 + random(-200, 200));
//       println("CPU will return in " + nf((cpuActionTime - millis()) / 1000.0, 1, 2) + " sec.");
//     } else {
//       // 返球
//       float elapsed = (millis() - startTime) / 1000.0;
//       println("経過秒数: " + nf(elapsed, 1, 3) + " (基準=" + baseTime + ")");

//       boolean validHit = abs(elapsed - baseTime) <= 0.75;
//       if (validHit && p1Strength > strongThreshold) {
//         println("P1: 強 (返球)");
//         baseTime = 1.0;
//         lastP1Strength = "強";
//       } else if (validHit && p1Strength > mediumThreshold) {
//         println("P1: 中 (返球)");
//         baseTime = 2.0;
//         lastP1Strength = "中";
//       } else if (validHit && p1Strength > weakThreshold) {
//         println("P1: 弱 (返球)");
//         baseTime = 3.0;
//         lastP1Strength = "弱";
//       } else {
//         println("無効な打球。CPUに1点。");
//         cpuScore++;
//         checkGameOver();
//         resetRally();
//         return;
//       }

//       startTime = millis();
//       cpuTurn = true;
//       cpuActionTime = millis() + int(baseTime * 1000 + random(-200, 200));
//       println("CPU will return in " + nf((cpuActionTime - millis()) / 1000.0, 1, 2) + " sec.");
//     }

//     p1LastTime = millis();
//     p1CanHit = false;
//   }

//   if (millis() - p1LastTime > 500) p1CanHit = true;

//   if (awaitingSecondInput && !cpuTurn) {
//     float elapsedSinceStart = (millis() - startTime) / 1000.0;
//     if (elapsedSinceStart > baseTime + 0.75) {
//       println("タイムオーバー。CPUに1点。");
//       cpuScore++;
//       checkGameOver();
//       resetRally();
//     }
//   }
// }

// void cpuHit() {
//   // CPUミス確率を設定
//   float missProb = 0.0;
//   if (lastP1Strength.equals("強")) {
//     missProb = 0.3;
//   } else if (lastP1Strength.equals("中")) {
//     missProb = 0.2;
//   } else if (lastP1Strength.equals("弱")) {
//     missProb = 0.1;
//   }

//   if (random(1) < missProb) {
//     println("CPUがミス。プレイヤーに1点。");
//     p1Score++;
//     checkGameOver();
//     resetRally();
//     return;
//   }

//   // CPU返球強さをランダム決定
//   float r = random(1);
//   if (lastP1Strength.equals("弱")) {
//     if (r < 0.25) {
//       println("CPU: 弱");
//       baseTime = 3.0;
//     } else if (r < 0.5) {
//       println("CPU: 中");
//       baseTime = 2.0;
//     } else {
//       println("CPU: 強");
//       baseTime = 1.0;
//     }
//   } else if (lastP1Strength.equals("中")) {
//     if (r < 0.25) {
//       println("CPU: 弱");
//       baseTime = 3.0;
//     } else if (r < 0.75) {
//       println("CPU: 中");
//       baseTime = 2.0;
//     } else {
//       println("CPU: 強");
//       baseTime = 1.0;
//     }
//   } else if (lastP1Strength.equals("強")) {
//     if (r < 0.5) {
//       println("CPU: 弱");
//       baseTime = 3.0;
//     } else if (r < 0.75) {
//       println("CPU: 中");
//       baseTime = 2.0;
//     } else {
//       println("CPU: 強");
//       baseTime = 1.0;
//     }
//   }

//   startTime = millis();
//   cpuTurn = false;
// }

// // 点数リセット
// void resetRally() {
//   awaitingSecondInput = false;
//   cpuTurn = false;
//   lastP1Strength = "";
// }

// // 終了判定
// void checkGameOver() {
//   if (p1Score >= 5 || cpuScore >= 5) {
//     gameOver = true;
//   }
}