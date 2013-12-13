

#ifndef __GAM_1514_OSX_Game__SplashScreen__
#define __GAM_1514_OSX_Game__SplashScreen__

#include "Menu.h"


class SplashScreen : public Menu
{
public:
    SplashScreen();
    ~SplashScreen();
    
    const char* getName();
    
    void keyUpEvent(int keyCode);
    

private:
    void buttonAction(UIButton* button);
};

#endif /* defined(__GAM_1514_OSX_Game__MainMenu__) */
