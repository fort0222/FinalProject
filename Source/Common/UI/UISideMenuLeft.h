
//  UISideMenuLeft.h
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-14.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__UISideMenuLeft__
#define __GAM_1514_OSX_Game__UISideMenuLeft__

#include "UIToggle.h"
#include "../OpenGL/OpenGL.h"
#include <stdlib.h>
#include <vector>

enum SideMenuOrientation
{
    SideMenuLeft = 0,
    SideMenuRight
};

class UISideMenuListener;

class UISideMenuLeft : public UIToggleListener
{
public:
    UISideMenuLeft(UISideMenuListener* listener, SideMenuOrientation orientation);
    ~UISideMenuLeft();
    
    void update(double delta);
    void paint();
    
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void keyUpEvent(int keyCode);
    
    void show();
    void hide();
    bool isShowing();
    
    void addButton(UIButton* button);
    int getIndexForButton(UIButton* button);
    UIButton* getButtonForIndex(int index);
    void clearButtons();
    
private:
    enum SideMenuState
    {
        SideMenuClosed = 0,
        SideMenuClosing,
        SideMenuOpen,
        SideMenuOpening
    };
    void setState(SideMenuState state);
    
    void buttonAction(UIButton* button);
    void buttonIsSelected(UIButton* button);
    bool buttonShouldBeDeselectedOnExit(UIButton* button);
    void buttonWasToggled(UIToggle* button);
    
    UISideMenuListener* m_Listener;
    
    SideMenuState m_State;
    SideMenuOrientation m_Orientation;
    
    OpenGLColor m_BackgroundColor;
    
    float m_TargetX;
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;
    
    std::vector<UIButton*> m_Buttons;
    int m_SelectedButtonIndex;
};


class UISideMenuListener
{
public:
    virtual void sideMenuButtonAction(UISideMenuLeft* sideMenu, UIButton* button, int buttonIndex) {};
    virtual void sideMenuToggleAction(UISideMenuLeft* sideMenu, UIToggle* toggle, int toggleIndex) {};
};

#endif /* defined(__GAM_1514_OSX_Game__UISideMenuLeft__) */
