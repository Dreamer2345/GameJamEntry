#pragma once

enum class GameState { 
      MainMenu, 
      GameStart,
      StarMap,
      ShipDock, 
      ShipInterior,
      Battle,
      ShipMap,
      MissionPick,
      RewardDisplay,
      ShipEdit,
      Shop,
      ShopSell,
      ShopBuy,
};
GameState gameState = GameState::GameStart;

