#pragma once

bool Walkable(uint16_t x, uint16_t y);
uint8_t GetCompBlock(uint8_t x,uint8_t y);
uint8_t GetYSize();
uint8_t GetXSize();
uint8_t GetTileX(uint16_t x);
uint8_t GetTileY(uint16_t y);

class PlayerClass {
  public:
  uint16_t x;
  uint16_t y;
  uint8_t tx;
  uint8_t ty;
  uint8_t Frame;
  bool Moving;
  byte d;
  char H;
  void PlayerMovement();
} playerobj;


void PlayerClass::PlayerMovement() {
  char xof = 0;
  char yof = 0;
  switch(d){
    case 0:yof = -1; break;
    case 1:yof = 1; break;
    case 2:xof = 1; break;
    case 3:xof = -1; break;
  }
  uint8_t relx = GetTileX(x)+xof;
  uint8_t rely = GetTileY(y)+yof;
  uint8_t bl1 = GetCompBlock(relx,rely);
  relx = GetTileX(x);
  rely = GetTileY(y);
  uint8_t bl = GetCompBlock(relx,rely);
  Point& ref = ErrRoom;
  Moving = false;
  if (ard.pressed(UP_BUTTON) ){
      if (Walkable(x,y-2)){
          y-=2;
          Moving = true;
        }
      d = 0;
    }
  if (ard.pressed(DOWN_BUTTON)){
      if (Walkable(x,y+2)){
          y+=2;
          Moving = true;
        }
      d = 1;
    }
  if (ard.pressed(RIGHT_BUTTON)){
      if (Walkable(x+2,y)){
          x+=2;
          Moving = true;
        }
      d = 2;
    }
  if (ard.pressed(LEFT_BUTTON)){
      if (Walkable(x-2,y)){
          x-=2;
          Moving = true;
        }
      d = 3;
    }   
  if (ard.pressed(B_BUTTON+A_BUTTON)){gameState = GameState::ShipMap; return;}
  if (ard.justPressed(A_BUTTON)){
    uint8_t mx = GetXSize();
    uint8_t my = GetYSize();
    if ((bl == 8)||(bl == 14)){
      if (relx == 0) {if ((GetShipBlock(tx-1,ty)!=0)&&(GetShipBlock(tx-1,ty)!=1)){tx--; x = (GetXSize()*16)-8; y = ((GetYSize()/2)*16)+8;}}
      else if (relx == mx-1) {if ((GetShipBlock(tx+1,ty)!=0)&&(GetShipBlock(tx-1,ty)!=1)){tx++; x = 8; y = ((GetYSize()/2)*16)+8;}}
      else if (rely == 0) {if ((GetShipBlock(tx,ty-1)!=0)&&(GetShipBlock(tx-1,ty)!=1)){ty--; x = ((GetXSize()/2)*16)+8; y = (GetYSize()*16)-8; }}
      else if (rely == my-1) {if ((GetShipBlock(tx,ty+1)!=0)&&(GetShipBlock(tx-1,ty)!=1)){ty++; x = ((GetXSize()/2)*16)+8; y = 8;}}
    }
    if (bl == 13) {
      gameState = GameState::StarMap;
    }
  }
  if (ard.justPressed(B_BUTTON)){
    uint8_t mx = GetXSize();
    uint8_t my = GetYSize();
    if((Err == 1) && (bl1 == 19) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 2) && (bl1 == 7) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 3) && (bl1 == 7) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 4) && (bl1 == 7) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 5) && (bl1 == 21) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 6) && (bl1 == 20) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
    if((Err == 7) && (bl1 == 7) && (ref.x == tx) && (ref.y == ty)) {Err = 0; Err1 = 0;}
  }
  if (bl == 13){
    ard.setCursor(0,0);
    ard.print(F("Access Star Map:A"));
  }

  if ((bl1 == 19) && (Err == 1) && (GetShipBlock(tx,ty) == 3) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Reboot Loop Drive:B"));
  }
  
  if ((bl1 == 7) && (Err == 2) && (GetShipBlock(tx,ty) == 2) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair Thrusters:B"));
  }

  if ((bl1 == 7) && (Err == 3) && (GetShipBlock(tx,ty) == 4) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair Sheild:B"));
  }

  if ((bl1 == 7) && (Err == 4) && (GetShipBlock(tx,ty) == 5) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair Blasters:B"));
  }
  
  if ((bl1 == 21) && (Err == 5) && (GetShipBlock(tx,ty) == 6) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair Cargo:B"));
  }

  if ((bl1 == 20) && (Err == 6) && (GetShipBlock(tx,ty) == 7) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair LifeSupport:B"));
  }

  if ((bl1 == 7) && (Err == 7) && (GetShipBlock(tx,ty) == 8) && (ref.x == tx) && (ref.y == ty)){
    ard.setCursor(0,0);
    ard.print(F("Repair Computer:B"));
  }
  
  

  
  
}
