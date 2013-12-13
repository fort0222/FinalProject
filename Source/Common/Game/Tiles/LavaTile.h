
  //LavaTile.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__LavaTile__
#define __GAM_1514_OSX_Game__LavaTile__

#include <iostream>
#include "Tile.h"


class LavaTile : public Tile
{
public:
	LavaTile(const char* textureName = RES_TILE_LAVA);
	virtual ~LavaTile();
    
    //Return the type of the tile
    const char* getType();
    
    //float getTileSpeed();
};


#endif /* defined(__GAM_1514_OSX_Game__LavaTile__) */