//
//  SettingsScreen.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__SettingsScreen__
#define __GAM_1514_OSX_Game__SettingsScreen__

#include <iostream>


#include "Menu.h"


class SettingsScreen : public Menu
{
public:
    SettingsScreen();
    ~SettingsScreen();
    
    const char* getName();
    
private:
    void buttonAction(UIButton* button);
};

#endif /* defined(__GAM_1514_OSX_Game__SettingsScreen__) */
