//
//  Enemy.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Enemy.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "Hero.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Constants/Constants.h"

Enemy::Enemy(Level* level, float speed) : Player(level)
{
    m_speed = speed;
    m_enemiesAlive = ENEMY_COUNT;
}

Enemy::~Enemy()
{
    
}

/*void Enemy::enemyCounter()
{
    m_enemiesAlive -=1;
    
    if (m_enemiesAlive <= 0)
    {
        ScreenManager::getInstance()->switchScreen(WIN_SCREEN_NAME);
        reset();
        m_enemiesAlive = ENEMY_COUNT;
    }
}
 */

const char* Enemy::getType()
{
    return ENEMY_TYPE;
}



void Enemy::update(double delta)
{
    Player::update(delta);
    
    //set the destination tile based on the pklaye'rs urrent tile
    setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
}

void Enemy::paint()
{
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
    OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);
    
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
    OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);

}

void Enemy::reset()
{
    Player::reset();
    setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
    
}

	void Enemy::handlePlayerCollision(Projectile* projectile)
	{

	}