//
//  WaterTile.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__WaterTile__
#define __GAM_1514_OSX_Game__WaterTile__

#include <iostream>
#include "Tile.h"


class WaterTile : public Tile
{
public:
	WaterTile(const char* textureName = RES_TILE_WATER);
	virtual ~WaterTile();
    
    //Return the type of the tile
    const char* getType();
    
    float getTileSpeed();
};

#endif /* defined(__GAM_1514_OSX_Game__WaterTile__) */
