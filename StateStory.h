#ifndef STATESTORY_H
#define STATESTORY_H

//----------------------------------------
// Includes
//----------------------------------------
#include "PenjinStates.h"
#include "Background.h"

//----------------------------------------
// State Class
//----------------------------------------
class StateStory : public BaseState
{
public:

    StateStory();
    virtual ~StateStory();

    virtual void init();
    virtual void render();
    virtual void update();
    virtual void userInput();

private:

    int m_Counter;
    Background m_bmpBackground;
    bool m_IsEnd;
};

#endif // STATESTORY_H
