unsigned int playerTargetTime = 0;  //プレイヤー打つタイミングの時間

bool cpuTurn = false;

//bool isPlayerInCooldown = false;
//unsigned int cooldownStartTime = 0;
//const unsigned int playerCooldownDuration = 500; 

int playerJudge(unsigned int soundStartTime) {
  // if (isPlayerInCooldown) {
  //   if (millis() - cooldownStartTime >= playerCooldownDuration) {
  //     isPlayerInCooldown = false; 
  //   } else {
  //     return; 
  //   }
  // }

  // if (playerMovingTime < playerTargetTime) {
  //   isPlayerInCooldown = true;
  //   cooldownStartTime = millis();
  //   return;
  // }

  int ballSpeed_judge;
  int racketStrong = Serial.read();
  if (playerMovingTime - playerTargetTime < 1000 )return;

  switch (racketStrong) {
    case 0:  //弱
      if (abs(playerMovingTime - playerTargetTime) < 500) {
        ballSpeed_judge = 0;
        playerTargetTime = 2000 + millis;
      } else {
        //GAMEOVER
      }
      break;
    case 1:  //中
      if (abs(playerMovingTime - playerTargetTime) < 400) {
        ballSpeed_judge = 1;
        playerTargetTime = 1500 + millis();
      } else if (abs(playerMovingTime - playerTargetTime) < 700) {
        ballSpeed_judge = 0;
        playerTargetTime = millis() + 1000;
      } else {
        //Gamsover
      }
      break;
    case 2:  //強
      if (abs(playerMovingTime - playerTargetTime) < 300) {
        ballSpeed_judge = 2;
        playerTargetTime = millis() + 1000;
      } else if (abs(playerMovingTime - playerTargetTime) < 550) {
        ballSpeed_judge = 1;
        playerTargetTime = millis() + 1500;
      } else if (abs(playerMovingTime - playerTargetTime) < 800) {
        ballSpeed_judge = 0;
        playerTargetTime = millis() + 1000;
      } else {
        //Gamevoer
      }
      break;
  }
  soundStartTime = millis();
  cpuTargetTime = millis();
  playerTurn = true;
  return ballSpeed_judge,soundStartTime;
}

void cpuJudge() {

  unsigned int waitTime;
  switch (ballSpeed) {
    case 0: waitTime = 3000;
    break;
    case 1: waitTime = 2000;
    break;
    case 2: waitTime = 1000;
    break;
  }

  if (millis() - cpuTargetTime >= waitTime) {
    if (random(0, 10) < 2) {
    return;
    }
    ballSpeed = random(0, 3);
    playerTurn = false; 
    playerTargetTime = millis();      
  }
}