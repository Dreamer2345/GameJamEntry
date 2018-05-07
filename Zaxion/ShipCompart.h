#pragma once

#define TileSize 16


const uint8_t PROGMEM Core[] ={
5,7,
1,5,8,5,2,
6,0,0,0,6,
6,0,18,0,6,
8,0,6,0,8,
6,0,19,0,6,
6,0,0,0,6,
4,5,8,5,3,
};

const uint8_t PROGMEM Engineering[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,7,0,8,
6,0,0,0,6,
4,5,8,5,3,
};

const uint8_t PROGMEM LifeSupport[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,20,0,8,
6,0,0,0,6,
4,5,8,5,3,
};

const uint8_t PROGMEM Blaster[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,7,0,8,
6,0,0,0,6,
4,5,8,5,3,
};

const uint8_t PROGMEM Sheild[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,7,0,8,
6,0,0,0,6,
4,5,8,5,3,
};

const uint8_t PROGMEM Cargo[] ={
7,7,
1,5,5,8,5,5,2,
6,0,0,0,0,0,6,
6,0,21,0,21,0,6,
8,0,0,0,0,0,8,
6,0,21,0,21,0,6,
6,0,0,0,0,0,6,
4,5,5,8,5,5,3,
};

const uint8_t PROGMEM Thrust[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,0,0,8,
6,0,7,0,6,
4,5,5,5,3,
};


const uint8_t PROGMEM Cabin[] ={
3,3,
9,12,15,
10,13,16,
11,14,17,
};

const uint8_t PROGMEM None[] ={
5,5,
1,5,8,5,2,
6,0,0,0,6,
8,0,7,0,8,
6,0,0,0,6,
4,5,8,5,3,
};
                             
const uint8_t * ShipComps[] = {None,Cabin,Thrust,Core,Sheild,Blaster,Cargo,LifeSupport,Engineering};

void swap(uint8_t & x,uint8_t & x1){
  uint8_t o = x;
  x = x1;
  x1 = o;
}

inline bool Between(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
  if (x > x1)
    swap(x, x1);
    
  if (y > y1)
    swap(y, y1);
    
  return ((x <= x2) && (x2 <= x1) && (y <= y2) && (y2 <= y1));
}

uint8_t GetTileX(uint16_t x)
{
  return (x / TileSize);
}

uint8_t GetTileY(uint16_t y)
{
  return (y / TileSize);
}

uint8_t GetTileXOffset(uint16_t x)
{
  return (x % TileSize);
}

uint8_t GetTileYOffset(uint16_t y)
{
  return (y % TileSize);
}

uint8_t GetXSize(){
  const uint8_t * CLevel = ShipComps[GetShipBlock(playerobj.tx,playerobj.ty)];
  return pgm_read_byte(&CLevel[0]);
}

uint8_t GetYSize(){
  const uint8_t * CLevel = ShipComps[GetShipBlock(playerobj.tx,playerobj.ty)];
  return pgm_read_byte(&CLevel[1]);
}


uint8_t GetCompBlock(uint8_t x,uint8_t y){
  const uint8_t * CLevel = ShipComps[GetShipBlock(playerobj.tx,playerobj.ty)];
  uint8_t MAP_WIDTH = pgm_read_byte(&CLevel[0]);
  uint8_t MAP_HEIGHT = pgm_read_byte(&CLevel[1]);
  if (x >= MAP_WIDTH || y >= MAP_HEIGHT){return 22;}
  uint16_t Index = 2+(x+(y*MAP_WIDTH));
  return pgm_read_byte(&CLevel[Index]);
}

bool Walkable(uint16_t x, uint16_t y) {
  uint8_t p[4];
  bool Walk = true; 
  p[0] = (GetCompBlock(GetTileX(x-4), GetTileY(y-4)));
  p[1] = (GetCompBlock(GetTileX(x+3), GetTileY(y-4)));
  p[2] = (GetCompBlock(GetTileX(x-4), GetTileY(y+3)));
  p[3] = (GetCompBlock(GetTileX(x+3), GetTileY(y+3)));
  for (byte i=0; i<4;i++){
    if (!((p[i]==0)||(p[i]==14)||(p[i]==13)||(p[i]==8))){
        Walk = false;
        break;
      }
  }
  return Walk;
}


