  //PitTile.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__PitTile__
#define __GAM_1514_OSX_Game__PitTile__

#include <iostream>
#include "Tile.h"


class PitTile : public Tile
{
public:
	PitTile(const char* textureName = RES_TILE_PIT);
	virtual ~PitTile();
    
    //Return the type of the tile
    const char* getType();
    
    //float getTileSpeed();
};


#endif /* defined(__GAM_1514_OSX_Game__LavaTile__) */