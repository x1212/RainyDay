//-----------------------------------------------------
// Defines
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EffectSystem.h"
#include "GameManager.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
EffectSystem::EffectSystem()
{

}
EffectSystem::~EffectSystem()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void EffectSystem::init()
{
    m_Fade.setColour(BLACK);
    m_Fade.setPosition(0, 0);
    m_Fade.setDimensions(800, 480);

    m_FadeDir = -1;
    m_FadeAlpha = 255;
    m_FadeSpeed = 20;

    for(int i = 0; i < RAINMAX; i += 1)
    {
        m_RainArr[i].position.x = -1000;
        m_RainArr[i].position.y = -1000;
    }

    m_isRaining = false;
}
void EffectSystem::render()
{
    //RAIN
    renderRain();

    //FADE
    if(m_FadeAlpha != 0) m_Fade.render();
}
void EffectSystem::renderRain()
{
    //RAIN
    if(m_isRaining)
    {
        //RAIN-LINES
        for(int i = 0; i < RAINMAX; i += 1)
        {
            if(m_RainArr[i].position.x != -1000)
            {
                //RENDER
                Vector2di startPos;
                startPos.x = m_RainArr[i].position.x + m_RainArr[i].size.x;
                startPos.y = m_RainArr[i].position.y - m_RainArr[i].size.y;

                Line l;
                l.setStartPosition(startPos);
                l.setEndPosition(m_RainArr[i].position);
                l.setColour(Colour(255, 255, 255, 104));
                l.render();

                //MOVE
                m_RainArr[i].position.x -= m_RainArr[i].sizeNormalised.x * 96;
                m_RainArr[i].position.y += m_RainArr[i].sizeNormalised.y * 96;

                //If out of sight -> destroy
                if(m_RainArr[i].position.y > 560)
                {
                    m_RainArr[i].position.x = -1000;
                    m_RainArr[i].position.y = -1000;
                }
            }
        }

        int temp = 0;

        for(int i = 0; i < RAINMAX; i += 1)
        {
            if(m_RainArr[i].position.x == -1000)
            {
                m_RainArr[i].position.x = rand() % 900;
                m_RainArr[i].position.y = rand() % 24 - 8;

                m_RainArr[i].size.x = rand() % 12 + 6;
                m_RainArr[i].size.y = rand() % 72 + 72;

                m_RainArr[i].sizeNormalised = m_RainArr[i].size;
                m_RainArr[i].sizeNormalised.normalise();

                temp += 1;
            }
            if(temp == 4) break;
        }
    }
}
void EffectSystem::renderFade()
{
    //FADE
    if(m_FadeAlpha != 0) m_Fade.render();
}
void EffectSystem::update()
{
    //FADE
    m_FadeAlpha += m_FadeDir * m_FadeSpeed;
    if(m_FadeDir < 0 && m_FadeAlpha <= 0) m_FadeAlpha = 0;
    else if(m_FadeDir > 0 && m_FadeAlpha >= 255) m_FadeAlpha = 255;
    else m_Fade.setAlpha(m_FadeAlpha);

}
void EffectSystem::fadeIn(int speed)
{
    m_FadeDir = -1;
    m_FadeSpeed = speed;
}
void EffectSystem::fadeOut(int speed, Colour colour)
{
    m_FadeDir = 1;
    m_FadeSpeed = speed;

    m_Fade.setColour(colour);
    m_Fade.setAlpha(m_FadeAlpha);
}
