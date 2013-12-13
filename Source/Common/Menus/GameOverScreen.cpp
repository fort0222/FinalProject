//
//  GameOverScreen.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GameOverScreen.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"


GameOverScreen::GameOverScreen() : Menu(NULL , NULL)
{
    
    addButton(new UIButton("ButtonExit"));
    m_Background = new OpenGLTexture("BackgroundLost");

}

GameOverScreen::~GameOverScreen()
{
    
}

const char* GameOverScreen::getName()
{
	return GAME_OVER_SCREEN_NAME;
}

void GameOverScreen::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0 )
    {
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
    
    
}