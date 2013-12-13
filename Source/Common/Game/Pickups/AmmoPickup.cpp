//
//  AmmoPickup.cpp
//  GAM-1514 OSX Game
//
//  Created by Gregory Fortier on 2013-11-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "AmmoPickup.h"

AmmoPickup::AmmoPickup(int ammoCount) : Pickup(PickupTypeAmmo),
    m_AmmoCount(ammoCount)
{
    //TODO the size should be that of the texture you use for the ammo pickup (or any pickup)
    setSize(24.0f, 24.0f);
}

AmmoPickup::~AmmoPickup()
{
    
}

void AmmoPickup::paint()
{
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
    OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight());
}

const char* AmmoPickup::getType()
{
    return AMMO_PICKUP_TYPE;
}

int AmmoPickup::getAmmoCount()
{
    return m_AmmoCount;
}