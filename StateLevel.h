#ifndef STATELEVEL_H
#define STATELEVEL_H

//----------------------------------------
// Includes
//----------------------------------------
#include "PenjinStates.h"
#include "Hero.h"
#include "GameManager.h"
#include "Music.h"
#include "Rectangle.h"
#include "Container.h"
#include "TextBox.h"

//----------------------------------------
// State Class
//----------------------------------------
class StateLevel : public BaseState
{
public:

    StateLevel();
    virtual ~StateLevel();

    virtual void init();
    virtual void render();
    virtual void update();
    virtual void userInput();

private:
    Music m_Ambient;
    bool m_IsEnd;

    int m_ThunderAlpha;
    Rectangle m_rctThunder;

    AnimatedSprite m_bmpMoth;
    bool m_didText, m_canPlay;
};

#endif // STATELEVEL_H
