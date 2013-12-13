//
//  FloorTile.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "FloorTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


FloorTile::FloorTile(const char* textureName) : Tile(TileTypeFloor, textureName, true)
{
    
}

FloorTile::~FloorTile()
{
    
}

const char* FloorTile::getType()
{
    return TILE_FLOOR_TYPE;
}

float FloorTile::getTileSpeed()
{
    return 1.0f;
}
