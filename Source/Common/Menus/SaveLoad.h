//
//  SaveLoad.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-15.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__SaveLoad__
#define __GAM_1514_OSX_Game__SaveLoad__

#include <iostream>
#include "Menu.h"

class LevelEditor;
class Level;

class SaveLoad : public Menu
{
public:
    SaveLoad();
    ~SaveLoad();
    
    const char* getName();

	//bool m_LoadingTrue;
	//bool m_SavingTrue;
	//bool m_SavingCheck;
    //bool m_LoadingCheck;

	//void SetLoadingBool(bool loadingBool);
	//void SetSavingBool(bool savingBool);
    
    bool GetGameScreenBool();
    void SetGameScreenBool(bool gameScreenBool);
    
private:
    void buttonAction(UIButton* button);
    LevelEditor* m_LevelEditor;
    
    bool m_GameScreenBool;

    
	
};


#endif /* defined(__GAM_1514_OSX_Game__SaveLoad__) */
