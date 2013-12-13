//
//  SaveLoad.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-15.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "SaveLoad.h"
#include "../Level Editor/LevelEditor.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"

SaveLoad::SaveLoad() : Menu(NULL, NULL), m_LevelEditor(NULL)//, m_Level(NULL)
{
	//m_SavingCheck = false;
    //m_LoadingCheck = false;

    m_LevelEditor = new LevelEditor();
    //m_Level = new Level();
    
    addButton(new UIButton("Save1"));
    addButton(new UIButton("Save2"));
    addButton(new UIButton("Save3"));
    addButton(new UIButton("Save4"));
    addButton(new UIButton("Save5"));
    addButton(new UIButton("Save6"));
    m_Background = new OpenGLTexture("Background");
}

SaveLoad::~SaveLoad()
{
    
  /*  if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }*/
     
    
    if(m_LevelEditor != NULL)
    {
        delete m_LevelEditor;
        m_LevelEditor = NULL;
    }
}

const char* SaveLoad::getName()
{
    return LOADSAVE_MENU_SCREEN_NAME;
}

void SaveLoad::buttonAction(UIButton* button)
{
    
    
    int index = getIndexForButton(button);
    LevelEditor* lvlEditor = (LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME); //IMPORTANT****
    Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
    
    if(index == 0 )
    {
		
		if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
				lvlEditor->CurrentLevel()->load("Level-1.txt");
            }

        }

        //Log::trace(m_SavingCheck?"true":"false");
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-1.txt");
            }
        }
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-1.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
        ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }
    }
    if(index == 1 )
    {
        if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
				lvlEditor->CurrentLevel()->load("Level-2.txt");
            }
            
        }
        
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-2.txt");
            }
        }
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-2.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
            ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }
    }
    
    if(index == 2 )
    {
        if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
				lvlEditor->CurrentLevel()->load("Level-3.txt");
            }
            
        }
        
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-3.txt");
            }
        }
        
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-3.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
            ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }    }
    
    if(index == 3 )
    {
        if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
				lvlEditor->CurrentLevel()->load("Level-4.txt");
            }
            
        }
        
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-4.txt");
            }
        }
        
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-4.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
            ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }
    }
    
    if(index == 4 )
    {
        if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
				lvlEditor->CurrentLevel()->load("Level-5.txt");
            }
            
        }
        
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-5.txt");
            }
        }
        
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-5.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
            ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }
    }


    if(index == 5 )
    {   
        if (lvlEditor->GetLoadingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->load("Level-6.txt");
            }
        
        }
    
        if (lvlEditor->GetSavingBool())
        {
            if(lvlEditor->CurrentLevel() != NULL)
            {
                lvlEditor->CurrentLevel()->save("Level-6.txt");
            }
        }
    
        if(GetGameScreenBool())
        {
            game->getLevel()->load("Level-6.txt");
            ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        }
        else
        {
            
            ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
        }
    }
}

bool SaveLoad::GetGameScreenBool()
{
    return m_GameScreenBool;
}

void SaveLoad::SetGameScreenBool(bool gameScreenBool)
{
    m_GameScreenBool = gameScreenBool;
}
