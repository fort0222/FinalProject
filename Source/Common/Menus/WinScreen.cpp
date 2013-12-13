//
//  WinScreen.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "WinScreen.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"


WinScreen::WinScreen() : Menu(NULL , NULL)
{
    
    addButton(new UIButton("ButtonExit"));
    m_Background = new OpenGLTexture("BackgroundWin");
    
}

WinScreen::~WinScreen()
{
    
}

const char* WinScreen::getName()
{
	return WIN_SCREEN_NAME;
}

void WinScreen::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0 )
    {
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
    
    
}