#ifndef STATETITLE_H
#define STATETITLE_H

//----------------------------------------
// Includes
//----------------------------------------
#include "PenjinStates.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "Background.h"
#include "Rectangle.h"

//----------------------------------------
// State Class
//----------------------------------------
class StateTitle : public BaseState
{
public:

    StateTitle();
    virtual ~StateTitle();

    virtual void init();
    virtual void render();
    virtual void update();
    virtual void userInput();

private:

    int m_CurrentScreen, m_Counter, m_FadeDir, m_ThunderAlpha;
    Background m_bmpBackgroundArr[3];
    Sprite m_bmpTitle, m_bmpPressStart;
    bool m_IsEnd;

    Music m_mscAmbient;
    Sound m_mscTitle;

    Rectangle m_rctThunder;
};

#endif // STATETITLE_H
