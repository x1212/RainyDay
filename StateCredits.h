#ifndef STATECREDITS_H
#define STATECREDITS_H

//----------------------------------------
// Includes
//----------------------------------------
#include "PenjinStates.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "Background.h"

//----------------------------------------
// State Class
//----------------------------------------
class StateCredits : public BaseState
{
public:

    StateCredits();
    virtual ~StateCredits();

    virtual void init();
    virtual void render();
    virtual void update();
    virtual void userInput();

private:

    int m_CurrentScreen, m_Counter;
    Background m_bmpBackgroundArr[5];
};

#endif // STATECREDITS_H
