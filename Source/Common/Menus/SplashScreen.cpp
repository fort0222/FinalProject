#include "SplashScreen.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Level Editor/LevelEditor.h"
#include "../Menus/SaveLoad.h"
#include "../OpenGL/OpenGL.h"


SplashScreen::SplashScreen() : Menu(NULL , NULL)
{
	addButton(new UIButton("SplashButton"));
    
}

SplashScreen::~SplashScreen()
{

}

const char* SplashScreen::getName()
{
	return SPLASH_SCREEN_SCREEN_NAME;
}

void SplashScreen::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0 )
    {
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}

}



void SplashScreen::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_SPACE)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}

