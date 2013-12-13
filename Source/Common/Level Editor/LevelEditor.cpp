//
//  LevelEditor.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LevelEditor.h"
#include "../Game/Level.h"
#include "../Game/Tiles/Tile.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
#include "../Menus/SaveLoad.h"


LevelEditor::LevelEditor() :
    m_TilesMenu(NULL),
	m_SideMenuLeft(NULL),
    m_Level(NULL),
    m_IsMouseDown(false),
    m_SelectedTileIndex(-1),
    m_LoadingBool(false),
    m_SavingBool(false)
{
    //Create the Tiles menu items
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
	m_SideMenuLeft = new UISideMenu(this,SideMenuLeft);
    
    m_SideMenuLeft->addButton(new UIButton("ButtonClear"));
    m_SideMenuLeft->addButton(new UIButton("ButtonLoad"));
    m_SideMenuLeft->addButton(new UIButton("ButtonSave"));
    m_SideMenuLeft->addButton(new UIButton("ButtonExit"));
    
    m_TilesMenu->addButton(new UIToggle("MenuTileDirt"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTileFloor"));
	m_TilesMenu->addButton(new UIToggle("MenuTileGrass"));
	m_TilesMenu->addButton(new UIToggle("MenuTileLava"));
	m_TilesMenu->addButton(new UIToggle("MenuTilePit"));
    
    //Create the level object
    m_Level = new Level(true);
    
    //Reset everything
    reset();
}

LevelEditor::~LevelEditor()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    
    if(m_TilesMenu != NULL)
    {
        delete m_TilesMenu;
        m_TilesMenu = NULL;
    }

	if(m_SideMenuLeft != NULL)
	{
		delete m_SideMenuLeft;
		m_SideMenuLeft = NULL;
	}
}

const char* LevelEditor::getName()
{
    return LEVEL_EDITOR_SCREEN_NAME;
}

void LevelEditor::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->update(delta);
    }

	if(m_SideMenuLeft != NULL)
    {
        m_SideMenuLeft->update(delta);
    }
}

void LevelEditor::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->paint();
    }

	if(m_SideMenuLeft != NULL)
    {
        m_SideMenuLeft->paint();
    }
}

void LevelEditor::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }

	if(m_SideMenuLeft != NULL)
    {
        m_SideMenuLeft->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_Level != NULL)
    {        
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
			TileType types[] = {TileTypeDirt, TileTypeWater, TileTypeFloor, TileTypeGrass, TileTypeLava, TileTypePit};
			TileType type = types[m_SelectedTileIndex];

            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
}

void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
}

void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
    //Set the mouse up flag
    m_IsMouseDown = false;
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {

			TileType types[] = {TileTypeDirt, TileTypeWater, TileTypeFloor, TileTypeGrass, TileTypeLava, TileTypePit};
			TileType type = types[m_SelectedTileIndex];

            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
    
    //Notify the tiles menu of the mouse event
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
    }

	if(m_SideMenuLeft != NULL)
    {
        m_SideMenuLeft->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void LevelEditor::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_TAB)
    {
        if(m_TilesMenu != NULL)
        {
            m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
        }

		if(m_SideMenuLeft != NULL)
        {
            m_SideMenuLeft->isShowing() == true ? m_SideMenuLeft->hide() : m_SideMenuLeft->show();
        }

    }
    
    if(keyCode == KEYCODE_T)
    {
        if(m_Level != NULL)
        {
            m_Level->setPickupTypeAtIndex(PickupTypeAmmo, 101);
        }
    }
    
    else if(keyCode == KEYCODE_Y)
    {
        if(m_Level != NULL)
        {
            m_Level->setPickupTypeAtIndex(PickupTypeUnknown, 101);
        }
    }
    
}

void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
    if(sideMenu == m_SideMenuLeft)
    {
        if(buttonIndex == 0)
        {
            for( int i = 0; i < m_Level->getNumberOfTiles(); i++)
            {
                m_Level->setTileTypeAtIndex(TileTypeDirt, i);
            }
        }
        
        if(buttonIndex == 1)
        {
            SetSavingBool(false);
            SetLoadingBool(true);
            
            ScreenManager::getInstance()->switchScreen(LOADSAVE_MENU_SCREEN_NAME);
        }
        
        if(buttonIndex == 2)
        {
			SetLoadingBool(false);
            SetSavingBool(true);
            
            ScreenManager::getInstance()->switchScreen(LOADSAVE_MENU_SCREEN_NAME);
            
        }
        
        if(buttonIndex == 3)
        {
            ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
        }
    
    }

}

void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
    if(sideMenu == m_TilesMenu)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TilesMenu->hide();
        m_SideMenuLeft->hide();
    }

	
	/*if(sideMenu == m_SideMenuLeft)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_SideMenuLeft->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_SideMenuLeft->hide();
    
    }
     */
}

//Get a bool for game screen with getter and setter, and if statement checking if it should switch to level edit or game screen

bool LevelEditor::GetLoadingBool()
{
    return m_LoadingBool;
}

bool LevelEditor::GetSavingBool()
{
    return m_SavingBool;
}


void LevelEditor::SetLoadingBool(bool loadingBool)
{
    m_LoadingBool = loadingBool;
	//m_LoadingCheck = loadingBool;
}

void LevelEditor::SetSavingBool(bool savingBool)
{
    m_SavingBool = savingBool;
	//m_SavingCheck = savingBool;
}

Level* LevelEditor::CurrentLevel()
{
    return m_Level;
}

/*
bool LevelEditor::GetGameScreenBool()
{
    return m_GameScreenBool;
}

void LevelEditor::SetGameScreenBool(bool gameScreenBool)
{
    m_GameScreenBool = gameScreenBool;
}
 
*/
/*void SaveLoad::SetLoadingBool(bool loadingBool)
{
    m_LoadingBool = loadingBool;
}

void SaveLoad::SetSavingBool(bool savingBool)
{
    m_SavingBool = savingBool;
}



*/