//----------------------------------------
// Defines
//----------------------------------------

//----------------------------------------
// Includes
//----------------------------------------
#include "StateLevel.h"

//----------------------------------------
// Constructor & Destructor
//----------------------------------------
StateLevel::StateLevel()
{

}
StateLevel::~StateLevel()
{

}
//----------------------------------------
// Methods
//----------------------------------------
void StateLevel::init()
{
    HERO->setInput(input);
    INPUT->initInput(input);

    CAMERA->setBoundingBox(120, 120, 280, 280);

    m_Ambient.loadMusic("sounds/RainAndThunder.ogg");
    m_Ambient.setLooping(true);
    m_Ambient.play();
    m_Ambient.setVolume(128);

    EFFECTSYSTEM->setRain(true);

    m_IsEnd = false;

    EFFECTSYSTEM->fadeIn(8);

    m_rctThunder.setColour(WHITE);
    m_rctThunder.setPosition(0, 0);
    m_rctThunder.setDimensions(800, 480);
    m_rctThunder.setAlpha(0);

    m_ThunderAlpha = 0;

    //MOTH
    m_bmpMoth.loadFrames("images/Moth_FlyingLeft.png", 8, 1);
	m_bmpMoth.setLooping(true);
    m_bmpMoth.setTransparentColour(MAGENTA);
    m_bmpMoth.setTimerScaler((float)1000 / 20.0f);

    m_didText = false;
    m_canPlay = false;
}
void StateLevel::render()
{
    GAMEMANAGER->render();

    if(HUD->getHealth() == 0 && m_IsEnd) m_rctThunder.render();
}
void StateLevel::update()
{
    if(m_IsEnd && m_ThunderAlpha != 255)
    {
        if(HUD->getHealth() == 0) m_ThunderAlpha += 75;
        if(m_Ambient.getVolume() != 0) m_Ambient.setVolume(m_Ambient.getVolume() - 75);

        if(HUD->getHealth() == 0)
        {
            if(m_ThunderAlpha > 255) m_ThunderAlpha = 255;
            m_rctThunder.setAlpha(m_ThunderAlpha);
        }
    }

    if(EFFECTSYSTEM->getFadeAlpha() == 255 && m_IsEnd) setNextState(STATE_CREDITS);

    if(!m_IsEnd)HERO->update();

    if(HUD->getHealth() == 0 && !m_IsEnd)
    {
        m_IsEnd = true;
        EFFECTSYSTEM->fadeOut(4);

        SOUNDSYSTEM->playSound(THUNDER4);
    }

    GAMEMANAGER->update();

    EFFECTSYSTEM->update();

    if(HERO->getPosition().x - CAMERA->getPosition().x < -180)
    {
        HERO->setNewPosition(GAMEMANAGER->getNewHeroPosition(PREVIOUS));
        GAMEMANAGER->changeLocation(PREVIOUS);
    }
    else if(HERO->getPosition().x - CAMERA->getPosition().x > 760)
    {
        //m_Hero.setNewPosition(GAMEMANAGER->getNewHeroPosition(NEXT));
        //GAMEMANAGER->changeLocation(NEXT);
        EFFECTSYSTEM->fadeOut(8);
        m_IsEnd = true;
    }

    m_bmpMoth.setPosition(600 - CAMERA->getPosition().x, 880 - CAMERA->getPosition().y);
    m_bmpMoth.update();
}
void StateLevel::userInput()
{
    input->update();
    if(input->isQuit() || input->isSelect())
        nullifyState();

    if(!m_IsEnd) HERO->userInput();
}
