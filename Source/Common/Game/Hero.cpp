//
//  Hero.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Hero.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "Enemy.h"

Hero::Hero(Level* level) : Player(level)
{
    m_Stamina = 3;
    m_levelForHealth = level;

}

Hero::~Hero()
{
    
}


const char* Hero::getType()
{
    return HERO_TYPE;
}

void Hero::mouseLeftClickUpEvent(float positionX, float positionY)
{
    Tile* tile = m_Level->getTileForPosition(positionX, positionY);
    if(tile != NULL && tile->isWalkableTile()== true)
    {
        setDestinationTile(tile);
    }
    
}

void Hero::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	 Tile* tile = m_Level->getTileForPosition(positionX, positionY);
    if(tile != NULL && tile->isWalkableTile()== true)
    { 
        //set the level's selected tile, this call is optional
        m_Level->setSelectedTileIndex(m_Level->getTileIndexForTile(tile));
    }
    
}

void Hero::gotHit()
{
    
        
    m_Stamina -=1;
    
    if (m_Stamina <= 0)
    {
        
        m_levelForHealth->reset();
        ScreenManager::getInstance()->switchScreen(GAME_OVER_SCREEN_NAME);
        
        
    }
}

void Hero::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_SPACE)
	{
		Tile* targetTile = m_Level->getTileForIndex(m_Level->getSelectedTileIndex());
		float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
		float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);

		fireProjectile(centerX, centerY);
	}
}

void Hero::handlePlayerCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());

	for(int i =0; i < m_Level->getEnemies().size(); i++)
	{
		Enemy* enemy = m_Level->getEnemies().at(i);
		if(enemy != NULL && enemy->getIsActive() == true)
		{
			Tile* enemyTile = m_Level->getTileForPlayer(enemy);

			if(tile == enemyTile)
			{
				Log::debug("Hero projectile hit an enemy");

				enemy->applyDamage(projectile->getDamage());
				projectile->setIsActive(false);
			}
		}
	}
}