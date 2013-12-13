//
//  WinScreen.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__WinScreen__
#define __GAM_1514_OSX_Game__WinScreen__

#include <iostream>

#include "Menu.h"


class WinScreen : public Menu
{
public:
    WinScreen();
    ~WinScreen();
    
    const char* getName();
    
private:
    void buttonAction(UIButton* button);
};

#endif /* defined(__GAM_1514_OSX_Game__WinScreen__) */
