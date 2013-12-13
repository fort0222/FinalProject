//
//  HighScoreScreen.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "HighScoreScreen.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"


HighScoreScreen::HighScoreScreen() : Menu(NULL , NULL, true)
{
    addButton(new UIButton("ButtonExit"));
    m_Title = new OpenGLTexture("HighScore");
    m_Background = new OpenGLTexture("Background");
    
}

HighScoreScreen::~HighScoreScreen()
{
    
}

const char* HighScoreScreen::getName()
{
	return HIGHSCORE_SCREEN_NAME;
}

void HighScoreScreen::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0 )
    {
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
    
    if (index == 1)
    {
        
    }
    
}