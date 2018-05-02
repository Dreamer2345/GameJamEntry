#include <Arduboy2.h>
Arduboy2 ard;
Sprites sprites;
uint8_t Err = 0;
uint8_t Err1 = 0;
uint8_t Uni = 0;
uint16_t Currency = 0;
#include "ENums.h"
#include "Bitmaps.h"
#include "Ship.h"
#include "Player.h"
#include "ShipCompart.h"
#include "Game.h"

void setup() {
  ard.begin();
  ard.clear();
  ard.initRandomSeed();
  ard.setFrameRate(30);
}

void loop() {
  if(!ard.nextFrame())
    return;

  ard.pollButtons();

  switch(gameState)
  {
    case GameState::MainMenu: break;
    case GameState::GameStart: RandomName(); ShipSetup(random(0,2)); gameState = GameState::MissionPick; break;
    case GameState::StarMap: StarMap(); break;
    case GameState::ShipDock: Dock(); break;
    case GameState::MissionPick: MissionPick(); break;
    case GameState::ShipMap: MapHandle(); break;
    case GameState::ShipInterior: InsideHandle(); break;
    case GameState::Battle: break;
    case GameState::RewardDisplay: RewardDisplay(); break;
    case GameState::Shop: Shop(); break;
    case GameState::ShopSell: ShopSell(); break;
    case GameState::ShopBuy: ShopBuy(); break;
  }
  if (Err!=0 && ard.everyXFrames(30)){
    playerobj.H-=5;
  } else {
    if (ard.everyXFrames(30)) {
      if (playerobj.H < 100)
        playerobj.H+=5;
      if (playerobj.H > 100)
        playerobj.H = 100;
     
    }
  }
  
  ard.display(CLEAR_BUFFER);
}
