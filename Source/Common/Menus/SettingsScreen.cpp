//
//  SettingsScreen.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "SettingsScreen.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"


SettingsScreen::SettingsScreen() : Menu(NULL , NULL, true)
{
    addButton(new UIButton("ButtonExit"));
    addButton(new UIButton("Difficulty"));
    addButton(new UIButton("ScoreLimit"));
    addButton(new UIButton("TimeLimit"));
    m_Background = new OpenGLTexture("Background");
	
    
}

SettingsScreen::~SettingsScreen()
{
    
}

const char* SettingsScreen::getName()
{
	return SETTINGS_SCREEN_NAME;
}

void SettingsScreen::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0 )
    {
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
    
    if (index == 1)
    {
        
    }
    
    if (index == 2)
    {
    
    }
    
    if (index == 3)
    {
        
    }
    
}