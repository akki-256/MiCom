unsigned int playerTargetTime = 0;  //プレイヤー打つタイミングの時間
unsigned int playerMovingTime = 0;

unsigned int cpuTargetTime = 0;  //CPU打つタイミングの時間
unsigned int cpuMovingTime = 0;

int racketStrongPin = 0;
int ballSpeed = 0;

bool playerTurn = false;
bool cpuTurn = false;

//bool isPlayerInCooldown = false;
//unsigned int cooldownStartTime = 0;
//const unsigned int playerCooldownDuration = 500; 

void playerJudge() {
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

  int racketStrong = analogRead(racketStrongPin);
  if (playerMovingTime - playerTargetTime < 1000 )return;

  switch (racketStrong) {
    case 0:  //弱
      if (abs(playerMovingTime - playerTargetTime) < 500) {
        ballSpeed = 0;
      } else {
        //GAMEOVER
      }
      break;
    case 1:  //中
      if (abs(playerMovingTime - playerTargetTime) < 400) {
        ballSpeed = 1;
      } else if (abs(playerMovingTime - playerTargetTime) < 700) {
        ballSpeed = 0;
      } else {
        //Gamsover
      }
      break;
    case 2:  //強
      if (abs(playerMovingTime - playerTargetTime) < 300) {
        ballSpeed = 2;
      } else if (abs(playerMovingTime - playerTargetTime) < 550) {
        ballSpeed = 1;
      } else if (abs(playerMovingTime - playerTargetTime) < 800) {
        ballSpeed = 0;
      } else {
        //Gamevoer
      }
      break;
  }
  startSoundTime = millis();
  cpuTargetTime = millis();
  playerTurn = true;
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