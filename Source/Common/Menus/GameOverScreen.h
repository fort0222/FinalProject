//
//  GameOverScreen.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-12-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GameOverScreen__
#define __GAM_1514_OSX_Game__GameOverScreen__

#include <iostream>

#include "Menu.h"


class GameOverScreen : public Menu
{
public:
    GameOverScreen();
    ~GameOverScreen();
    
    const char* getName();
    
private:
    void buttonAction(UIButton* button);
};


#endif /* defined(__GAM_1514_OSX_Game__GameOverScreen__) */
