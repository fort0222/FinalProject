//
//  LevelConstants.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_CONSTANTS_H
#define LEVEL_CONSTANTS_H

//Global enum for the Level's tile types,
//add additional tile types in this enum
enum TileType
{
  //TileTypeGround = 0,
  TileTypeDirt =1, // (0000 0001)
  TileTypeWater =2, // (0000 0010)
  TileTypeFloor =4,// (0000 0100)
  TileTypeGrass =8,// (0000 1000)
  TileTypeLava= 16,// (0001 0000)
  TileTypePit =32,// (0010 0000)
    
    //this count value MUST now be manually updated when a new tile type is added
  TileTypeUnknown =6,
    
  TileTypeCount = -1
};

enum PickupType
{
    PickupTypeAmmo = 64, // (0100 0000)
    
    //this count value MUST now be manually updated when a new pickup type is added
    PickupTypeCount = 1,
    PickupTypeUnknown = -1
};

//Level editor screen name
extern const char* LEVEL_EDITOR_SCREEN_NAME;

//Empty Level Constants
extern const int EMPTY_LEVEL_TILE_SIZE;
extern const int EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX;

#endif
