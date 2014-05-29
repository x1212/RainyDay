//----------------------------------------
// Defines
//----------------------------------------

//----------------------------------------
// Includes
//----------------------------------------
#include "StateCredits.h"

//----------------------------------------
// Constructor & Destructor
//----------------------------------------
StateCredits::StateCredits()
{

}
StateCredits::~StateCredits()
{

}
//----------------------------------------
// Methods
//----------------------------------------
void StateCredits::init()
{
    m_CurrentScreen = 0;
    m_Counter = 0;

    m_bmpBackgroundArr[0].loadBackground("images/Credits1.png");
    m_bmpBackgroundArr[1].loadBackground("images/Credits2.png");
    m_bmpBackgroundArr[2].loadBackground("images/Credits3.png");
    m_bmpBackgroundArr[3].loadBackground("images/Credits4.png");
    m_bmpBackgroundArr[4].loadBackground("images/Credits5.png");


    for(int i = 0; i < 4; i += 1)
    {
        m_bmpBackgroundArr[i].disableTransparentColour();
        m_bmpBackgroundArr[i].setPosition(Vector2di(0, 0));
    }

    EFFECTSYSTEM->fadeIn(8);
}
void StateCredits::render()
{
    m_bmpBackgroundArr[m_CurrentScreen].render();

    EFFECTSYSTEM->renderFade();
}
void StateCredits::update()
{
    EFFECTSYSTEM->update();

    if(m_CurrentScreen != 5)
    {
        if(EFFECTSYSTEM->getFadeAlpha() == 0) m_Counter +=1;

        if(m_Counter >= 80)
        {
            if(m_Counter == 80) EFFECTSYSTEM->fadeOut(8);

            if(EFFECTSYSTEM->getFadeAlpha() == 255)
            {
                if(m_CurrentScreen != 4) m_CurrentScreen += 1;
                else nullifyState();

                EFFECTSYSTEM->fadeIn(8);
            }

            m_Counter +=1;

            if(EFFECTSYSTEM->getFadeAlpha() == 0 && EFFECTSYSTEM->getFadeDirection() == -1) m_Counter = 0;
        }
    }
}
void StateCredits::userInput()
{
    input->update();
    if(input->isQuit() || input->isSelect())
        nullifyState();

    //if(/*m_CurrentScreen == 3 &&*/ input->isStart()) setNextState(STATE_LEVEL);
}
