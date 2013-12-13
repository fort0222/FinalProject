
  //GrassTile.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GrassTile__
#define __GAM_1514_OSX_Game__GrassTile__

#include <iostream>
#include "Tile.h"


class GrassTile : public Tile
{
public:
	GrassTile(const char* textureName = RES_TILE_GRASS);
	virtual ~GrassTile();
    
    //Return the type of the tile
    const char* getType();
    
    float getTileSpeed();
};


#endif /* defined(__GAM_1514_OSX_Game__GrassTile__) */