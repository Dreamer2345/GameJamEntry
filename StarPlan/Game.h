#pragma once
#define CENTERX 63
#define CENTERY 31
uint8_t MissionType = 0;
uint8_t JumpsLeft = 3;
uint8_t Dist = 3;
char StarBaseName[5];
uint8_t ShipParts[8];
uint8_t Pricing[7];
bool StarBase = false;
uint8_t paying = 0;

void PickRandomRoom(uint8_t Type){
  bool Chosen = false;
  do{
    for (int i=0; i<MAXX; i++) 
      for (int j=0; j<MAXY; j++) 
        {if ((GetShipBlock(i,j) == Type)&&(random(0,10)==0)) {ErrRoom.x = i; ErrRoom.y = j; Chosen = true; break;}}
  }while(Chosen == false);
}

bool HasRoom(uint8_t Type){
  for (int i=0; i<MAXX; i++) 
      for (int j=0; j<MAXY; j++) 
        {if (GetShipBlock(i,j) == Type) return true;}
  return false;
}

void RandomName(){
  for (int i=0; i<4; i++){
    if (rand() % 2 == 0){
      StarBaseName[i] = random(97,122);
    } else {
      StarBaseName[i] = random(48,57);
    }
    StarBaseName[4] = 0;
  }
}

uint8_t Reward(){
  uint8_t reward = 0;
  switch(MissionType){
    case 0: reward = random(5,10); break;
    case 1: reward = random(1,5); break;
  }
  return reward;
}

void ShipSetup(uint8_t Type){
  for (int i=0; i<MEMSIZE; i++) {Ship[i] = 0;}
  SetShipBlock(5,4,1);
  SetShipBlock(5,5,3);
  switch(Type){
    case 0:SetShipBlock(5,6,4); break;
    case 1:SetShipBlock(5,6,5); break;
    case 2:SetShipBlock(5,6,6); break;
  }
  SetShipBlock(5,7,2);
  Shipobj.Health = 100;
  playerobj.x = (2*16)-8;
  playerobj.y = (3*16)-8;
  playerobj.tx = 5;
  playerobj.ty = 4;
  playerobj.H = 100;
  JumpsLeft = 3;
  Dist = 3;
}

void Jump(){
  JumpsLeft--;
  StarBase = false;
  uint8_t Danger = 0;
  switch(MissionType){
    case 0:Danger = 1;
    case 1:Danger = 5;
    case 2:Danger = 10;
  }

  
  if (JumpsLeft == 0) {
    for (int i=0; i<7; i++) {Pricing[i] = random(5*(i+1),(5*(i+1))+5);}
    StarBase = true;
    paying = Reward();
    gameState = GameState::RewardDisplay;
  } else {
    if (random(0,Danger) == 0) {
      switch(random(0,10)){
        case 1:Err = 1; PickRandomRoom(3); break;
        case 2:Err = 2; PickRandomRoom(2); break;
        case 3:if(HasRoom(4)) {Err = 3; PickRandomRoom(4);}  break;
        case 4:if(HasRoom(5)) {Err = 4; PickRandomRoom(5);}  break;
        case 5:if(HasRoom(6)) {Err = 5; PickRandomRoom(6);}  break;
        case 6:if(HasRoom(7)) {Err = 6; PickRandomRoom(7);}  break;
        case 7:if(HasRoom(8)) {Err = 7; PickRandomRoom(8);}  break;
        case 8:break;
      }
    }
  }
  if (JumpsLeft == 255){
    Dist++;
    JumpsLeft = Dist;
    RandomName();
  }
}





void DrawInterior(){
  int tileX = GetTileX(playerobj.x);
  int tileY = GetTileY(playerobj.y);
  int offsetX = GetTileXOffset(playerobj.x);
  int offsetY = GetTileYOffset(playerobj.y);
    
  for (int i = -5; i < 5; i++)
  {
    for(int j = -3; j < 3; j++)
    {
      uint8_t block = GetCompBlock(tileX + i, tileY + j);
      
      int drawX = (i * 16) + CENTERX - offsetX;
      int drawY = (j * 16) + CENTERY - offsetY;
      sprites.drawSelfMasked(drawX, drawY, Background, block);
    }
  }
}



void DrawPlayer(){  
  const uint8_t PlayerFrames[] = { 0, 1, 0, 2 };
  if(!playerobj.Moving)
  {
    sprites.drawOverwrite(CENTERX - 4 , CENTERY - 4, PlayerSprites, 0);  
  }
  else
  {
    if(ard.everyXFrames(5))
    {
      ++playerobj.Frame;
      playerobj.Frame %= 4;
    }
    sprites.drawOverwrite(CENTERX - 4 , CENTERY - 4, PlayerSprites, PlayerFrames[playerobj.Frame]);
  }
}

void DrawShipMap(){
  uint8_t tileX = playerobj.tx;
  uint8_t tileY = playerobj.ty;
  if(ard.everyXFrames(5))
    {
      ++playerobj.Frame;
      playerobj.Frame %= 4;
    }  
  for (int i = -4; i < 5; i++)
  {
    for(int j = -4; j < 5; j++)
    {
      uint8_t block = GetShipBlock(tileX + i, tileY + j);
      if ((Err != 0)&&((tileX + i) == ErrRoom.x)&&((tileY + j) == ErrRoom.y)&&(playerobj.Frame <=1)){block = 10;}
      int drawX = (i * 8) + CENTERX;
      int drawY = (j * 8) + CENTERY;
      sprites.drawOverwrite(drawX, drawY, ShipElements, block);
    }
  }
}


void MapHandle(){
  DrawShipMap();
  if (ard.justPressed(A_BUTTON)){gameState = GameState::ShipInterior; Uni = 0;}
}

void InsideHandle(){
  DrawInterior();
  DrawPlayer();
  playerobj.PlayerMovement();
  ard.setCursor(0,54);
  ard.print(F("H:"));
  ard.print(static_cast<uint8_t>(playerobj.H));
}

void StarMap(){
  ard.setCursor(0,0);
  ard.println(F("LIO:OS:V10.5"));
  ard.print(F("Jumps Left To:"));
  ard.print(StarBaseName);
  ard.print(F(":"));
  ard.println(JumpsLeft);
  if (StarBase){ard.println(F("Star Base In Range"));}
  if (Uni > 0){ard.println(F("^"));} else {ard.println(F(""));}
  switch(Uni){
    case 0: ard.println(F(">Activate Loopdrive")); break;
    case 1: ard.println(F(">Dock")); break;
    case 2: ard.println(F(">Save Progress")); break;
    case 3: ard.println(F(">Exit Console")); break;
  }
  if (Uni < 3){ard.println(F("v"));}
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<3)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    switch(Uni){
    case 0: if(Err == 0) {Jump();} else {Err1 = 2;} break;
    case 1: if (StarBase){gameState = GameState::ShipDock; Uni = 0;} else {Err1 = 1;} break;
    case 2: break;
    case 3: gameState = GameState::ShipInterior; Uni = 0; break;
  }  
  }
  
  if (ard.justPressed(B_BUTTON)){gameState = GameState::ShipInterior; Uni = 0;}
  
  switch(Err1){
    case 1: ard.print(F("No Star Base In Range")); break;
    case 2: ard.println(F("Engine Malfunction:")); switch(Err){
            case 1: ard.print(F("Core Missaligned!")); break;
            case 2: ard.print(F("Thruster Degraded!")); break;
            case 3: ard.print(F("Sheild Dispersed!")); break;
            case 4: ard.print(F("Blaster Jammed!")); break;
            case 5: ard.print(F("Cargo Breach!")); break;
            case 6: ard.print(F("LifeSupport Failing!")); break;
            case 7: ard.print(F("Enginerring Fault!")); break;
            }  
            break;
  }
  if ((Err1>0)&&(ard.everyXFrames(60))&&(Err1 <= 2)){
    Err1 = 0;
  }
  
}

void MissionPick(){
  ard.setCursor(0,0);
  ard.println(F("LIO:OS:V10.5"));
  ard.println(F("Choose A Mission:"));
  if (Uni > 0){ard.println(F("^"));} else {ard.println();}
  switch(Uni){
    case 0: ard.println(F(">Escort")); break;
    case 1: ard.println(F(">Transport Cargo")); break;
    case 2: ard.println(F(">No Job")); break;
  }
  if (Uni < 2){ard.println(F("v"));}
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<2)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    gameState = GameState::StarMap; 
    MissionType = Uni; 
    Uni = 0;
  }
}

void RewardDisplay(){
  if (MissionType != 2){
    ard.setCursor(0,0);
    ard.println(F("LIO:OS:V10.5"));
    ard.setCursor(0,CENTERY-6);
    ard.print(F("You Earned:")); 
    ard.print(paying); 
    if (ard.justPressed(A_BUTTON)){
      gameState = GameState::MissionPick; 
      Uni = 0; 
      Currency += paying;
    }
  } else {gameState = GameState::MissionPick; Uni = 0; }
}


void Dock(){
  ard.setCursor(0,0);
  ard.print(StarBaseName);
  ard.println(F(":OS:V10.5"));
  if (Uni > 0){ard.println(F("^"));} else {ard.println();}
  switch(Uni){
    case 0: ard.println(F(">Edit Ship")); break;
    case 1: ard.println(F(">Shop")); break;
    case 2: ard.println(F(">Return")); break;
  }
  if (Uni < 2){ard.println(F("v"));}
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<2)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    switch(Uni){
    case 0: gameState = GameState::ShipEdit; Uni = 0; break;
    case 1: gameState = GameState::Shop; Uni = 0; break;
    case 2: gameState = GameState::StarMap; Uni = 0; break;
    }  
  }
  if (ard.justPressed(B_BUTTON)){Uni = 0; gameState = GameState::StarMap;}
}

void Shop(){
  ard.setCursor(0,0);
  ard.print(StarBaseName);
  ard.println(F(":Shop:OS:V10.5"));
  ard.print(F("Currency:"));
  ard.println(Currency);
  if (Uni > 0){ard.println(F("^"));} else {ard.println();}
  switch(Uni){
    case 0: ard.print(F(">Buy")); break;
    case 1: ard.print(F(">Sell")); break;
    case 2: ard.print(F(">Return")); break;
  }
  if (Uni < 2){ard.println(F("v"));}
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<2)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    switch(Uni){
    case 0: gameState = GameState::ShopBuy; Uni = 0; break;
    case 1: gameState = GameState::ShopSell; Uni = 0; break;
    case 2: gameState = GameState::ShipDock; Uni = 0; break;
    }  
      
  }
  if (ard.justPressed(B_BUTTON)){Uni = 0; gameState = GameState::ShipDock;}
}


void ShopBuy(){
  ard.setCursor(0,0);
  ard.print(StarBaseName);
  ard.println(F(":Shop:OS:V10.5"));
  ard.print(F("Currency:"));
  ard.println(Currency);
  if (Uni > 0){ard.println(F("^"));} else {ard.println();}
  switch(Uni){
    case 0: ard.print(F(">Buy Thruster:")); break;
    case 1: ard.print(F(">Buy Sheild:")); break;
    case 2: ard.print(F(">Buy Blasters:")); break;
    case 3: ard.print(F(">Buy Cargo Hold:")); break;
    case 4: ard.print(F(">Buy LifeSupport:")); break;
    case 5: ard.print(F(">Buy Engineering:")); break;
    case 6: ard.print(F(">Buy Core:")); break;
    case 7: ard.print(F(">Return")); break;
  }
  if (Uni != 8){
    ard.println(Pricing[Uni]);
    ard.print(F("Holding:"));
    ard.println(ShipParts[Uni]);
  }

  if (Uni < 7){ard.println(F("v"));}
  
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<7)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    if (Uni != 7){
      if (Currency >= Pricing[Uni]){
        ShipParts[Uni]++;
        Currency-=Pricing[Uni];
      }
    }else{
      Uni = 0;
      gameState = GameState::Shop;
    }
  }
  if (ard.justPressed(B_BUTTON)){Uni = 0; gameState = GameState::Shop;}
}

void ShopSell(){
  ard.setCursor(0,0);
  ard.print(StarBaseName);
  ard.println(F(":Shop:OS:V10.5"));
  ard.print(F("Currency:"));
  ard.println(Currency);
  if (Uni > 0){ard.println(F("^"));} else {ard.println();}
  switch(Uni){
    case 0: ard.print(F(">Sell Thruster:")); break;
    case 1: ard.print(F(">Sell Sheild:")); break;
    case 2: ard.print(F(">Sell Blasters:")); break;
    case 3: ard.print(F(">Sell Cargo Hold:")); break;
    case 4: ard.print(F(">Sell LifeSupport:")); break;
    case 5: ard.print(F(">Sell Engineering:")); break;
    case 6: ard.print(F(">Sell Core:")); break;
    case 7: ard.print(F(">Return")); break;
  }
  if (Uni != 7){
    ard.println(Pricing[Uni]-1);
    ard.print(F("Holding:"));
    ard.println(ShipParts[Uni]);
  }
  if (Uni < 7){ard.println(F("v"));}
  
  if (ard.justPressed(DOWN_BUTTON)&&(Uni<7)){
    Uni++;
    }
  if (ard.justPressed(UP_BUTTON)&&(Uni>0)){
    Uni--;
    }
  if (ard.justPressed(A_BUTTON)){
    if (Uni != 7){
      if (ShipParts[Uni] > 0){
        ShipParts[Uni]--;
        Currency+=(Pricing[Uni]-1);
      }
    }else{
      Uni = 0;
      gameState = GameState::Shop;
    }
  }
  if (ard.justPressed(B_BUTTON)){Uni = 0; gameState = GameState::Shop;}
}


void RunShipEdit(){
  DrawShipMap();
}









