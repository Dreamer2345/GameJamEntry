#pragma once

enum class GameState { 
      MainMenu, 
      ShipPick,
      GameStart,
      StarMap,
      ShipDock, 
      ShipInterior,
      Battle,
      ShipMap,
      MissionPick,
      RewardDisplay,
      ShipEdit,
      PartPick,
      Shop,
      ShopSell,
      ShopBuy,
      Death,
};
GameState gameState = GameState::MainMenu;

