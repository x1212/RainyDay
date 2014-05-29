//----------------------------------------
// Defines
//----------------------------------------

//----------------------------------------
// Includes
//----------------------------------------
#include "StateStory.h"

//----------------------------------------
// Constructor & Destructor
//----------------------------------------
StateStory::StateStory()
{

}
StateStory::~StateStory()
{

}
//----------------------------------------
// Methods
//----------------------------------------
void StateStory::init()
{
    m_bmpBackground.loadBackground("images/Story.png");
    m_bmpBackground.disableTransparentColour();
    m_bmpBackground.setPosition(Vector2di(0, 0));

    m_IsEnd = false;

    m_Counter = 64;
}
void StateStory::render()
{
    m_bmpBackground.render();

    EFFECTSYSTEM->renderFade();
}
void StateStory::update()
{
    EFFECTSYSTEM->update();

    if(m_Counter == 0) EFFECTSYSTEM->fadeIn(8);
    if(m_Counter != -1) m_Counter -= 1;

    if(EFFECTSYSTEM->getFadeAlpha() == 255 && m_IsEnd) setNextState(STATE_LEVEL);
}
void StateStory::userInput()
{
    input->update();
    if(input->isQuit() || input->isSelect())
        nullifyState();

    if(EFFECTSYSTEM->getFadeAlpha() == 0 && (input->isStart() || input->isA() || input->isB() || input->isX() || input->isY()))
    {
        m_IsEnd = true;
        EFFECTSYSTEM->fadeOut(8);
    }
}
