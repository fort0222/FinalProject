//
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Player.h"
#include "Hero.h"
#include "Enemy.h"
#include "PathFinder.h"
#include "Tiles/Tile.h"
#include "Tiles/DirtTile.h"
//#include "Tiles/GroundTile.h"
#include "../Game/Tiles/WaterTile.h"
#include "Tiles/FloorTile.h"
//#include "Tiles/GrassTile.h"
#include "../Game/Tiles/GrassTile.h"
#include "Tiles/LavaTile.h"
#include "Tiles/PitTile.h"

#include "Pickups/Pickup.h"
#include "Pickups/AmmoPickup.h"

#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include "../Math/GDRandom.h"
#include "../Utils/Utils.h"


Level::Level(bool isEditingLevel) :
    m_HorizontalTiles(0),
    m_VerticalTiles(0),
    m_TileSize(EMPTY_LEVEL_TILE_SIZE),
    m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
    m_Hero(NULL),
    m_Tiles(NULL),
    m_SelectedTileIndex(-1),
    m_PaintTileScoring(false),
    m_PaintTileIndexes(false)
{
    m_enemyCount = ENEMY_COUNT;
    
    //Create the player object
    if(isEditingLevel == false)
    {
        m_Hero = new Hero(this);
        
        //TODO make sconstants for these
        float min = 50.0f;
        float max = PLAYER_SPEED;
        GDRandom random;
        random.randomizeSeed();
        
        for(int i = 0; i < ENEMY_COUNT; i++)
        {
            float speed = min + random.random(max-min);
            
            Enemy* enemy = new Enemy(this, speed);
            m_Enemies.push_back(enemy);
        }
    }
    
    //Calculate the number of horizontal and vertical tiles
    m_HorizontalTiles = ScreenManager::getInstance()->getScreenWidth() / m_TileSize;
    m_VerticalTiles = ScreenManager::getInstance()->getScreenHeight() / m_TileSize;
    
    //Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];
    
    //Initialize all the tiles to NULL
    for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
    {
        m_Tiles[i] = NULL;
    }
    
    //Load an empty level
    load(NULL);
    
    //bool m_lose = false;

    
    
}

Level::~Level()
{
    //Delete the player object
	if(m_Hero != NULL)
	{
		delete m_Hero;
		m_Hero = NULL;
	}
    
    //Delete the tiles array, the inheriting class
    //must delete the object in this array itself
	if(m_Tiles != NULL)
	{
        //Cycle through and delete all the tile objects in the array
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            if(m_Tiles[i] != NULL)
            {
                delete m_Tiles[i];
                m_Tiles[i] = NULL;
            }
        }
        
		delete[] m_Tiles;
		m_Tiles = NULL;
	}
    
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        delete m_Enemies.at(i);
        m_Enemies.at(i) = NULL;
    }
    
    m_Enemies.clear();
}

void Level::update(double aDelta)
{
    //hero collision with the enemies
    for (int i =0; i < m_Enemies.size(); i++)
    {
        if (getTileIndexForPlayer(m_Enemies.at(i)) == getTileIndexForPlayer(m_Hero))
            {
                if(m_Enemies.at(i)->getIsActive() == true)
                {
                    m_Enemies.at(i)->setIsActive(false);
                    m_Hero->gotHit();
                    enemyCounter();
                    
                    
                    
                }
            }
    }
    

    
	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->update(aDelta);
		}
	}
    
	//Update the Player
	if(m_Hero != NULL)
	{
		m_Hero->update(aDelta);
	}
    
   // for(int i = 0; i < m_Enemies.size(); i++)
   // {
   //     m_Enemies.at(i)->update(aDelta);
   // }
    


	for(int i = 0; i < m_Enemies.size(); i++)
	{
		if(m_Enemies.at(i)->getIsActive() == true)
		{
			m_Enemies.at(i)->update(aDelta);
		}
	}

}

void Level::paint()
{
	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
        //Safety check the tile
		if(m_Tiles[i] != NULL)
		{
            //Paint the tile
            m_Tiles[i]->paint();
            
            //If the paint tile indexes flag is set to true,
            //draw the index number on the tiles
            if(m_PaintTileIndexes == true)
            {
                m_Tiles[i]->paintIndex(i);
            }
		}
	}
    
	//Paint the Player
	if(m_Hero != NULL)
	{
        //If paint tile scoring flag is set to true,
        //draw the path scoring
        if(m_PaintTileScoring == true)
        {
            m_Hero->getPathFinder()->paint();
        }
        
        //Paint the player
		m_Hero->paint();
	}
    
    for(int i = 0; i < m_Enemies.size(); i++)
    {
		if(m_Enemies.at(i)->getIsActive() == true)
		{
        m_Enemies.at(i)->paint();
		}
    }
}

void Level::reset()
{ 
	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
	}
    
	//Make a player* vector to hold the hero and Enemies for reset()
    std::vector<Player*> players;
    
    if(m_Hero != NULL)
    {
        players.push_back(m_Hero);
    }
    
    for(int i = 0; i < m_Enemies.size(); i++)
    {
        players.push_back(m_Enemies.at(i));
    }
    
    GDRandom random;
    random.randomizeSeed();
    int tileIndex = -1;
    std::vector<int> usedTileIndexes;
    
    for(int i = 0; i < players.size(); i++)
    {
        tileIndex = -1;
        while (tileIndex == -1)
        {
            tileIndex = random.random(getNumberOfTiles());
            
            if(getTileForIndex(tileIndex)->isWalkableTile() == false)
            {
                tileIndex = -1;
            }
            else
            {
                //cycle through and ensure the index hasn't already been used
                for(int j = 0; j < usedTileIndexes.size(); j++)
                {
                    if(usedTileIndexes.at(j) == tileIndex)
                    {
                        tileIndex = -1;
                        break;
                    }
                }
                
                if(tileIndex != -1)
                {
                    players.at(i)->setCurrentTile(getTileForIndex(tileIndex));
                    players.at(i)->reset();
                    usedTileIndexes.push_back(tileIndex);
                }
                
            }
            
            
        }
        
    }
    
    if (m_Hero != NULL)
    {
    m_Hero->m_Stamina = 3;
    }
    
    
    m_enemyCount = ENEMY_COUNT;
    
    
}

void Level::enemyCounter()
{
    
        
    m_enemyCount -=1;
    
        
    if(m_enemyCount <= 0)
    {
        ScreenManager::getInstance()->switchScreen(WIN_SCREEN_NAME);
        m_Hero->m_Stamina++;
        reset();
        
    }
}

void Level::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	if(m_Hero != NULL)
	{
		m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
}

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	if (m_Hero != NULL)
    {
        m_Hero->mouseLeftClickUpEvent(aPositionX, aPositionY);
    }
}

void Level::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_R)
    {
        reset();
    }
    if (keyCode == KEYCODE_S)
    {
        togglePaintTileScoring();
    }
    else if(keyCode == KEYCODE_I)
    {
        togglePaintTileIndexes();
    }
    
    if(keyCode == KEYCODE_C)
    {
        load(NULL);
    }
    
    else if(keyCode == KEYCODE_D)
    {
        if(m_Hero!= NULL)
        {
            m_Hero->getPathFinder()->togglePathFindingDelay();
        }
    }

	else
	{
		if(m_Hero != NULL)
		{
			m_Hero->keyUpEvent(keyCode);
		}
	}
}

void Level::load(const char* levelName)
{
    
    //If the level name isn't NULL load the level from the filesystem,
    //if it is NULL load an empty level with just ground tiles
    if(levelName != NULL)
    {
        std::ifstream inputStream;
        
        inputStream.open(levelName, std::ifstream::in | std::ifstream::binary);
        
        if(inputStream.is_open() == true)
        {
            inputStream.seekg(0, inputStream.end);
            long long bufferSize = inputStream.tellg();
            
            inputStream.seekg(0, inputStream.beg);
            
            char* buffer = new char [bufferSize];
            
            inputStream.read(buffer, (int)bufferSize);
            
            inputStream.close();
            
            for(int i = 0; i < bufferSize; i++)
            {
                PickupType pickupType = PickupTypeUnknown;
                
                //Check to see if the buffer[i] contains the ammoPickup bit
                if((buffer[i] & PickupTypeAmmo) > 0)
                {
                    //it does
                    pickupType = PickupTypeAmmo;
                    
                    //clear the AmmoPicup bit
                    buffer[i] &= ~PickupTypeAmmo;
                }
                //set the tile type
                setTileTypeAtIndex((TileType)buffer[i],i);
                
                //set the pickup type
                setPickupTypeAtIndex(pickupType, i);
            }
            
            delete[] buffer;
            buffer = NULL;
            
        }
        
        
        
        
    }
    else
    {
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            setTileTypeAtIndex(TileTypeDirt, i);
        }
    }
    
    //The level is loaded, reset everything
    reset();
}

void Level::save(const char* levelName)
{
    //TODO: save the level
    //Create the buffer
    int bufferSize = getNumberOfTiles();
    char* buffer = new char[bufferSize];
    
    for (int i = 0; i < bufferSize; i++)
    {
        buffer[i]=(char)getTileTypeForIndex(i);
        
        //save the tile's pickup if there is one
        if(m_Tiles[i]->getPickup() != NULL && m_Tiles[i]->getPickup()->getPickupType() != PickupTypeUnknown)
        {
            buffer[i] |= m_Tiles[i]->getPickup()->getPickupType();
            
        }
    }
    
    std::ofstream outputStream;
    outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);
    
    if (outputStream.is_open() == true)
    {
        outputStream.write(buffer, bufferSize);
        outputStream.close();
    }
    
    delete[] buffer;
    buffer = NULL;
}

TileType Level::getTileTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        return m_Tiles[index]->getTileType();
    }
    return TileTypeUnknown;
}

PickupType Level::getPickupTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        if(m_Tiles[index]->getPickup() != NULL)
        {
            return m_Tiles[index]->getPickup()->getPickupType();
        }
    }
    return PickupTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
    return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
    if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
        return false;
    }
    return true;
}

int Level::getTileCoordinateForPosition(int aPosition)
{
	return (aPosition / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPosition(aPositionX);
	int coordinatesY = getTileCoordinateForPosition(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}
    
	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}
                                      
int Level::getTileIndexForPlayer(Player* player)
{
	return getTileIndexForPosition(player->getX(),player->getY());
}

Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
    //Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}
    
    //If we got here, it means the index passed in was out of bounds
	return NULL;
}
                                      
Tile* Level::getTileForPlayer(Player* player)
{
	return getTileForPosition(player->getX(), player->getY());
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
    setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
    setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
    //Safety check the index
    if(index >= 0 && index < getNumberOfTiles())
	{
        //Don't replace the tile if its the same type of tile that already exists
        if(m_Tiles[index] != NULL && m_Tiles[index]->getTileType() == tileType)
        {
            return;
        }
    
        //Delete the tile at the index, if one exists
        if(m_Tiles[index] != NULL)
        {
            delete m_Tiles[index];
            m_Tiles[index] = NULL;
        }
        
        //Create the new tile based on the TileType
        switch (tileType)
        {
            case TileTypeDirt:
                m_Tiles[index] = new DirtTile();
                break;
                
            case TileTypeWater:
                m_Tiles[index] = new WaterTile();
                break;
                
            case TileTypeFloor:
                m_Tiles[index] = new FloorTile();
                break;

			case TileTypeGrass:
				m_Tiles[index] = new GrassTile();
				break;

			case TileTypeLava:
				m_Tiles[index] = new LavaTile();
				break;

			case TileTypePit:
				m_Tiles[index] = new PitTile();
				break;

            case TileTypeUnknown:
            default:
                m_Tiles[index] = NULL;
                break;
        }
        
        //Calculate the coordinates and set the tile position and size
        int coordinateX = (index % getNumberOfHorizontalTiles());
        int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
        m_Tiles[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
        m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}

void Level::setPickupTypeAtPosition(PickupType pickupType, int positionX, int positionY)
{
    setPickupTypeAtIndex(pickupType, getTileIndexForPosition(positionX, positionY));
}

void Level::setPickupTypeAtCoordinates(PickupType pickupType, int coordinateX, int coordinateY)
{
    setPickupTypeAtIndex(pickupType, getTileIndexForCoordinates(coordinateX, coordinateY));
}

void Level::setPickupTypeAtIndex(PickupType pickupType, int index)
{
    //safety check the index
    if(index >= 0 && index < getNumberOfTiles())
    {
        //Don't replace the tile if a pickup of the same type already exists there
        if(m_Tiles[index] != NULL && m_Tiles[index]->getPickup() != NULL)
        {
            if(m_Tiles[index]->getPickup()->getPickupType() == pickupType)
            {
                return;
            }
        }
        
        //Delete the pickup at the index, if one exists already
        if(m_Tiles[index] != NULL)
        {
            if(m_Tiles[index]->getPickup() != NULL)
            {
                m_Tiles[index]->setPickup(NULL);
            }
            
            
            switch(pickupType)
            {
                case PickupTypeAmmo:
                {
                    GDRandom random;
                    random.randomizeSeed();
                    
                    int min = 5;
                    int max = 50;
                    int ammo = min + random.random(max-min);
                    
                    m_Tiles[index]->setPickup(new AmmoPickup(ammo));
                }
                    break;
                    
                //TODO: Make sure to add future pickups here for object creation
                    
                case PickupTypeUnknown:
                default:
                    break;
            }
            
            //set the pickups position and size
            if(m_Tiles[index]->getPickup() != NULL)
            {
                int coordinateX = (index % getNumberOfHorizontalTiles());
                int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
                
                Pickup* pickup = m_Tiles[index]->getPickup();
                float x = (coordinateX * m_TileSize) + (m_TileSize - pickup->getWidth()) /2.0f;
                float y = (coordinateY * m_TileSize) + (m_TileSize - pickup->getHeight()) / 2.0f;
                pickup->setPosition(x,y);
            }
            
        }
        
    }
}





void Level::togglePaintTileScoring()
{
    m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
    m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}
    
	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;
    
	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}

int Level::getSelectedTileIndex()
{
	return m_SelectedTileIndex;
}
                    
Hero* Level::getHero()
{
    return m_Hero;
}

std::vector<Enemy*>Level::getEnemies()
{
	return m_Enemies;
}


