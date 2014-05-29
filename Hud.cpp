//-----------------------------------------------------
// Defines
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Hud.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
Hud::Hud()
{

}
Hud::~Hud()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void Hud::init()
{
    m_Health = 5;
    m_Score = 0;
    m_Lifes = 3;

    m_bmpHud.loadSprite("images/HUD.png");
    m_bmpHud.setPosition(8, 8);

    m_bmpHud2.loadSprite("images/HUD2.png");
    m_bmpHud2.setPosition(629, 23);

    m_bmpHealth.loadSprite("images/Health.png");
    m_bmpHealth.setPosition(80, 35);

    m_bmpNumbers.loadImageSheet("images/NumberSheet.png", 10, 1);

    m_FPS.setPosition(8, 480);
    m_FPS.loadFont("Fonts/FrancoisOne.ttf");
    m_FPS.setFontSize(20);
}
void Hud::render()
{
    m_bmpHud.render();
    m_bmpHud2.render();

    int s1 = m_Score / 1000000;
    int s2 = (m_Score / 100000) - (s1*10);
    int s3 = (m_Score / 10000) - (s1*100) - (s2*10);
    int s4 = (m_Score / 1000) - (s1*1000) - (s2*100) - (s3*10);
    int s5 = (m_Score / 100) - (s1*10000) - (s2*1000) - (s3*100) - (s4*10);
    int s6 = (m_Score / 10) - (s1*100000) - (s2*10000) - (s3*1000) - (s4*100) - (s5*10);
    int s7 = m_Score - (s1*1000000) - (s2*100000) - (s3*10000) - (s4*1000) - (s5*100) - (s6*10);

    m_bmpNumbers.renderImage(s1, 651, 36);
    m_bmpNumbers.renderImage(s2, 667, 36);
    m_bmpNumbers.renderImage(s3, 683, 36);
    m_bmpNumbers.renderImage(s4, 699, 36);
    m_bmpNumbers.renderImage(s5, 715, 36);
    m_bmpNumbers.renderImage(s6, 731, 36);
    m_bmpNumbers.renderImage(s7, 747, 36);

    m_bmpNumbers.renderImage(m_Lifes, 73, 64);

    int pos = 80;

    for(int i = 0; i < m_Health; i += 1)
    {
        m_bmpHealth.setPosition(pos, 35);
        m_bmpHealth.render();
        pos += 17;
    }
}
void Hud::update()
{

}
void Hud::setHealth(int value)
{
    if(m_Health < 5) m_Health += value;
    else if(m_Health == 5 && value < 0) m_Health += value;
}
float Hud::calcFPS()
{
    static float fps = 0.0f;
    static float lastTime = 0.0f;
    #ifndef PENJIN_SYS_TIMER
        float currentTime = SDL_GetTicks();
    #else
        float currentTime = clock();
    #endif
    fps = fps*0.9f+(100.0f/max(currentTime - lastTime,1.0f));
    lastTime = currentTime;
    return fps;
}
