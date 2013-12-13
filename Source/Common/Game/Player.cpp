//
//  Player.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Player.h"
#include "Level.h"
#include "PathNode.h"
#include "Tiles/Tile.h"
#include "Enemy.h"

#include "Pickups/AmmoPickup.h"

#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>

#include "../Utils/Utils.h"
#include "Projectile.h"
#include "../Screen Manager/ScreenManager.h"

Player::Player(Level* aLevel)
{
    m_Level = aLevel;
    
    //Create the PathFinder object
    m_PathFinder = new PathFinder(aLevel, this);
    
    //Initialize the current and destination tiles to NULL
    m_CurrentTile = NULL;
    m_DestinationTile = NULL;
    
    
    //Initialize the animation member variables
    m_CanAnimate = false;
    m_AbortAnimation = false;
    m_AnimationPathNodeIndex = -1;
    
    //set the player sped
    m_speed = PLAYER_SPEED;
    
    //Initialize the ammo amount and hp
    m_Ammo = 20;
	m_Health = 1;
    
    //Initialize the player's size
    setSize(PLAYER_SIZE, PLAYER_SIZE);
    
}

Player::~Player()
{
    if(m_PathFinder != NULL)
    {
        delete m_PathFinder;
        m_PathFinder = NULL;
    }
    //Set the current and desination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;
}

void Player::update(double aDelta)
{
	//update the projectiles
	for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->update(aDelta);
		}

	}

	//Remove any inactive projectiles from the projectile vector
	int index = 0;
	while (index != m_Projectiles.size())
	{
		if(m_Projectiles.at(index)->getIsActive() == false)
		{
			Log::debug("Deleting projectile");

			//delete the projectile and remove it from the vector
			delete m_Projectiles.at(index);
			m_Projectiles.erase(m_Projectiles.begin() + index);
		}
		else
		{
			index++;
		}
	}




    if(m_PathFinder->isSearchingPath() == true)
    {
        m_PathFinder->update(aDelta);
    }
    
    //Handle player animation
    if(isAnimating() == true && m_AnimationPathNodeIndex > -1)
    {
        PathNode* pathNode = m_PathFinder->getPathNodeAtIndex(m_AnimationPathNodeIndex);
        Tile* tile = pathNode!= NULL ? pathNode->getTile() : NULL;
        
        //safety check that tile isn't NULL
        if(tile != NULL)
        {
            float centerX = tile->getX() + (tile->getWidth() - getWidth()) / 2.0f;
            float centerY = tile->getY() + (tile->getHeight() - getHeight()) / 2.0f;
            
            //get the tile speed for the tile the player is on
            Tile* playerTile = m_Level->getTileForPosition(getX(), getY());
            float speed = playerTile->getTileSpeed();
            
            //Next calculate how much the player should animate this update() call,
            //use the animate() method to help calculate
            float playerX = animate(getX(), centerX, aDelta, speed);
            float playerY = animate(getY(), centerY, aDelta, speed);
            setPosition(playerX, playerY);
            
            //Has the player reached the center of the tile>
            if(playerX == centerX && playerY == centerY)
            {
                m_AnimationPathNodeIndex++;
                
                //set the current tile's path flag to false
                m_CurrentTile->setIsPath(false);
                
                //set the new current tile
                setCurrentTile(tile);
                
                //Does the tile have a pickup on it
                if(tile->getPickup() != NULL)
                {
                    handlePickup(tile->getPickup());
                    
                    //set the tile's pick to NULL, since it was picked up
                    tile->setPickup(NULL);
                }
                
                //Are we done animating completely?
                if(m_AnimationPathNodeIndex >= m_PathFinder->getPathSize())
                {
                    stopAnimating();
                    m_CurrentTile->setIsPath(false);
                }
                
                if(m_AbortAnimation == true)
                {
                    //Reset the flag to false
                    m_AbortAnimation = false;
                    
                    //Behin searching the new path
                    findPath();
                }
                
            }
        }
    }
    
}

void Player::paint()
{
	//cycle through and paint all the active projectiles
	for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}


	 OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_INSIDE_COLOR);
     OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);
     OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
     OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);

}

void Player::reset()
{
    //stop animating the player
    stopAnimating();
    
    //reset the path finder
    m_PathFinder->reset();
    
    //set the destination tile to NULL
    m_DestinationTile = NULL;

	//set the player's state to 'active'
	setIsActive(true);
    
    m_Ammo = 20;
    
    
}

void Player::fireProjectile(float x, float y)
{
	if (m_Ammo > 0)
	{
		m_Ammo--;

		//create a new projectile object
		Projectile* projectile = new Projectile(this, 1 ,10.0f);
		projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + (getHeight() / 2.0f));
		projectile->setTarget(x,y);
		m_Projectiles.push_back(projectile);

		Log::debug("Fired Projectile, %i ammo left", m_Ammo);
	}
	else
	{
		Log::debug("Can't fire projectile, no ammo left");
	}
}

void Player::applyDamage(int damage)
{
    
	m_Health -= damage;
    //for (int i =0; i < m_Enemies.size(); i++)
    //{
       
	if(m_Health <= 0)
	{
        m_Health = 0;
        setIsActive(false);
        m_Level->enemyCounter();
    
        
            //ScreenManager::getInstance()->switchScreen(HIGHSCORE_SCREEN_NAME);
        
    
    

            Log::debug("Player is dead");
            
	}
	else
	{
		Log::debug("Player is hit, %i health remaining", m_Health);
	//}
    }
}

void Player::setCurrentTile(Tile* tile)
{
	//Set the current tile pointer
	m_CurrentTile = tile;
    
	//Center the player's position on the tile
	setPosition(tile->getX() + ((tile->getWidth() - getWidth()) / 2), tile->getY() + ((tile->getHeight() - getHeight()) / 2));
}

void Player::setDestinationTile(Tile* tile)
{
	//Set the destination tile pointer
	m_DestinationTile = tile;
    
    //Start pathfinding
    if(isAnimating() == false)
    {
        findPath();
    }
    else
    {
        m_AbortAnimation = true;
    }
}

void Player::handlePickup(Pickup* pickup)
{
    switch(pickup->getPickupType())
    {
        case PickupTypeAmmo:
            m_Ammo += ((AmmoPickup*)pickup)->getAmmoCount();
            break;
            
        default:
            break;
    }
}

void Player::handleBoundsCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
	if (tile == NULL)
	{
		projectile->setIsActive(false);

		Log::debug("Projectile went off screen");
	}
}

void Player::pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound)
{
    if (pathFinder == m_PathFinder)
    {
        if(pathWasFound == true)
        {
            startAnimating();
        }
        else
        {
            m_PathFinder->reset();
        }
    }
}

//PathFinde methods
PathFinder* Player::getPathFinder()
{
    return m_PathFinder;
}

void Player::findPath()
{
    m_PathFinder->reset();
    m_PathFinder->findPath(m_CurrentTile, m_DestinationTile);
}

float Player::animate(float aCurrent, float aTarget, double aDelta, float speed)
{
    float increment = aDelta * m_speed * (aTarget < aCurrent ? -1 : 1) * speed;
    if(fabs(increment) > fabs(aTarget - aCurrent))
    {
        return aTarget;
    }
    else
    {
        aCurrent += increment;
    }
    return aCurrent;
}

void Player::startAnimating()
{
	m_CanAnimate = true;
	m_AnimationPathNodeIndex = 0;
}

void Player::stopAnimating()
{
	m_CanAnimate = false;
	m_AnimationPathNodeIndex = -1;
}

bool Player::isAnimating()
{
    return m_CanAnimate;
}
