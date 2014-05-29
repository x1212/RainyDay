//----------------------------------------
// Defines
//----------------------------------------

//----------------------------------------
// Includes
//----------------------------------------
#include "StateTitle.h"

//----------------------------------------
// Constructor & Destructor
//----------------------------------------
StateTitle::StateTitle()
{

}
StateTitle::~StateTitle()
{

}
//----------------------------------------
// Methods
//----------------------------------------
void StateTitle::init()
{
    SOUNDSYSTEM->init();

    m_CurrentScreen = 0;
    m_Counter = 0;

    m_bmpBackgroundArr[0].loadBackground("images/Astolat.png");
    m_bmpBackgroundArr[1].loadBackground("images/Penjin.png");
    m_bmpBackgroundArr[2].loadBackground("images/Title_Background.png");

    m_bmpTitle.loadSprite("images/Title_Logo.png");
    m_bmpTitle.setPosition(0, 0);

    m_bmpPressStart.loadSprite("images/Title_PressStart.png");
    m_bmpPressStart.setAlpha(0);
    m_bmpPressStart.setPosition(320, 368);

    m_IsEnd = false;

    m_FadeDir = 5;

    for(int i = 0; i < 3; i += 1)
    {
        m_bmpBackgroundArr[i].disableTransparentColour();
        m_bmpBackgroundArr[i].setPosition(Vector2di(0, 0));
    }

    m_mscAmbient.loadMusic("sounds/Rain.ogg");
    m_mscAmbient.setLooping(true);
    m_mscAmbient.play();
    m_mscAmbient.setVolume(20);

    m_mscTitle.loadSound("music/Title.ogg");
    m_mscTitle.setLoops(-1);

    m_rctThunder.setColour(WHITE);
    m_rctThunder.setPosition(0, 0);
    m_rctThunder.setDimensions(800, 480);
    m_rctThunder.setAlpha(0);

    m_ThunderAlpha = 0;

    EFFECTSYSTEM->fadeIn(8);
}
void StateTitle::render()
{
    m_bmpBackgroundArr[m_CurrentScreen].render();

    EFFECTSYSTEM->renderRain();

    if(m_CurrentScreen == 2)
    {
        m_bmpTitle.render();
        m_bmpPressStart.render();
    }

    m_rctThunder.render();

    EFFECTSYSTEM->renderFade();
}
void StateTitle::update()
{
    EFFECTSYSTEM->update();

    if(m_IsEnd && m_ThunderAlpha != 255)
    {
        m_ThunderAlpha += 75;
        if(m_mscAmbient.getVolume() != 0) m_mscAmbient.setVolume(m_mscAmbient.getVolume() - 75);

        if(m_ThunderAlpha > 255) m_ThunderAlpha = 255;
        m_rctThunder.setAlpha(m_ThunderAlpha);
    }

    if(EFFECTSYSTEM->getFadeAlpha() == 255 && m_IsEnd) setNextState(STATE_STORY);

    if(m_CurrentScreen != 2)
    {
        if(EFFECTSYSTEM->getFadeAlpha() == 0) m_Counter +=1;

        if(m_Counter >= 64)
        {
            if(m_Counter == 64) EFFECTSYSTEM->fadeOut(8);

            if(EFFECTSYSTEM->getFadeAlpha() == 255)
            {
                m_CurrentScreen += 1;

                //SOUNDSYSTEM->playSound(THUNDER2);

                EFFECTSYSTEM->fadeIn(8);
            }

            m_Counter +=1;

            if(EFFECTSYSTEM->getFadeAlpha() == 0 && EFFECTSYSTEM->getFadeDirection() == -1) m_Counter = 0;
        }

        if(m_Counter == 0 && m_CurrentScreen == 0)
        {
            //SOUNDSYSTEM->playSound(THUNDER1);
        }
    }

    if(m_CurrentScreen == 2)
    {
        if(!EFFECTSYSTEM->isRaining())
        {
            m_mscTitle.play();
            EFFECTSYSTEM->setRain(true);
        }

        m_bmpPressStart.setAlpha(m_bmpPressStart.getAlpha() + m_FadeDir);
        if(m_bmpPressStart.getAlpha() == 0 || m_bmpPressStart.getAlpha() == 255) m_FadeDir *= -1;
    }

    if(m_mscAmbient.getVolume() != 100 && !m_IsEnd) m_mscAmbient.setVolume(m_mscAmbient.getVolume() + 2);
}
void StateTitle::userInput()
{
    input->update();
    if(input->isQuit() || input->isSelect())
        nullifyState();

    if(EFFECTSYSTEM->getFadeAlpha() == 0 && m_CurrentScreen == 2 && input->isStart())
    {
        m_IsEnd = true;

        EFFECTSYSTEM->fadeOut(4);

        SOUNDSYSTEM->playSound(THUNDER4);
    }
}
