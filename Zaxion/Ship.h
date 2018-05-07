#pragma once

#define MAXX 9
#define MAXY 9
#define MEMSIZE ((MAXX/2)*MAXY)
uint8_t Ship[MEMSIZE];
Point ErrRoom;

struct ShipClass{
  uint8_t Health;
  uint8_t Speed;
  uint8_t Attack;
  uint8_t Defence;
  uint8_t Cargo;
}Shipobj;

uint16_t GetOffset(uint8_t x,uint8_t y){
  uint16_t ColCheck = ((x/2)+(y*(MAXX/2)));
  if (ColCheck < (MEMSIZE))
    return ColCheck;
  else
    {
    return 0;
    }
}

uint8_t GetShipBlock(uint8_t x,uint8_t y){
 if (x >= MAXX || y >= MAXY){return 0;}
 uint8_t Block = 0;
 if (x % 2 == 0){
    Block = Ship[GetOffset(x,y)] >> 4;
 } else {
    Block = Ship[GetOffset(x,y)] & 0x0F;
 }
 return Block;
}

void SetShipBlock(uint8_t x,uint8_t y,uint8_t b){
 uint8_t Block = Ship[GetOffset(x,y)];
 uint8_t AddBlock = b;
 if (x % 2 == 0){
    AddBlock = AddBlock << 4;
    Block &= 0x0F;
 } else {
    Block &= 0xF0;
 }
 Block |= AddBlock;
 Ship[GetOffset(x,y)] = Block;
}


