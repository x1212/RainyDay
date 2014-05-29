//-----------------------------------------------------
// Defines
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Beam.h"
#include "GameManager.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
Beam::Beam()
{
    m_isActive = false;
    m_Position.x = 0;
    m_Position.y = 0;
}
Beam::~Beam()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void Beam::init(int type, Vector2di position, int direction)
{
    m_isActive = true;

    m_Type = type;
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_bmpImage.setPosition(m_Position);
    m_Direction = direction;

    switch(m_Type)
    {
        case 0:
            if(direction == DIR_LEFT) m_bmpImage.loadFrames("images/Effects/GrabBeamLeft.png", 6, 1);
            else if(direction == DIR_RIGHT) m_bmpImage.loadFrames("images/Effects/GrabBeamRight.png", 6, 1);
        break;

        case 1:
            if(direction == DIR_LEFT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 0, 2);
            else if(direction == DIR_RIGHT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 2, 2);
        break;

        case 2:
            if(direction == DIR_LEFT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 4, 2);
            else if(direction == DIR_RIGHT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 6, 2);
        break;

        case 3:
            if(direction == DIR_LEFT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 8, 2);
            else if(direction == DIR_RIGHT) m_bmpImage.loadFrames(SURFACE_CACHE->loadSurface("images/Effects/Beams.png"), 4, 3, 10, 2);
        break;
    }

    m_Speed = 28;

	m_bmpImage.setLooping(true);
    m_bmpImage.setTransparentColour(Colour(255, 0, 255));
    m_bmpImage.setTimerScaler((float)1000 / 30.0f);
}
void Beam::render()
{
    if(m_isActive)
    {
        m_bmpImage.render();
    }
}
void Beam::update()
{
    if(m_isActive)
    {
        if(m_Type == 0)
        {
            m_Speed -= 2;

            if(m_Speed >= 0) m_Position.x += m_Speed * m_Direction;
            else
            {
                Vector2df v = Vector2df(m_Position.x - GAMEMANAGER->getHeroPosition()->x - 90 , m_Position.y - GAMEMANAGER->getHeroPosition()->y - 72);
                v.normalise();
                v *= (m_Speed * -1);

                m_Position -= v;
            }
        }
        else m_Position.x += m_Speed * m_Direction;

        m_bmpImage.setPosition(m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y);
        m_bmpImage.update();
    }

}
