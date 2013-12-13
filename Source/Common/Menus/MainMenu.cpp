//
//  MainMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MainMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"


MainMenu::MainMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonLoadLevel"));
    addButton(new UIButton("ButtonLevelEditor"));
    addButton(new UIButton("HighScore"));
    addButton(new UIButton("Settings"));
    addButton(new UIButton("ButtonExit"));
    m_Background = new OpenGLTexture("Background");
    
     }

MainMenu::~MainMenu()
{

}

const char* MainMenu::getName()
{
    return MAIN_MENU_SCREEN_NAME;
}



void MainMenu::buttonAction(UIButton* button)
{
    SaveLoad* saveLoad = (SaveLoad*)ScreenManager::getInstance()->getScreenForName(LOADSAVE_MENU_SCREEN_NAME); //IMPORTANT****

    int index = getIndexForButton(button);
    if(index == 0)
    {
         saveLoad->SetGameScreenBool(true);
        ScreenManager::getInstance()->switchScreen(LOADSAVE_MENU_SCREEN_NAME);
       
    }
    else if(index == 1)
    {
        ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		saveLoad->SetGameScreenBool(false);
    }
    
    else if(index == 2)
    {
        ScreenManager::getInstance()->switchScreen(HIGHSCORE_SCREEN_NAME);
    }
    
    else if(index == 3)
    {
        ScreenManager::getInstance()->switchScreen(SETTINGS_SCREEN_NAME);
    }
    
    else if (index == 4)
    {
        exit(1);
    }
}
