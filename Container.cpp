#include "Container.h"
#include "GameManager.h"
#include "Enemy.h"

Container::Container(string path)
{
    m_Type = UNIT_CONTAINER;

    m_bmpContainers.loadImageSheet(SURFACE_CACHE->loadSurface(path), 5, 3, 0, 15);
    m_bmpContainers.setTransparentColour(Colour(255, 0, 255));

    m_rgnCollision.init(0, 0, 56, 56);

    for(int i = 0; i < 6; i += 1)
    {
        m_arrPieces[i].visible = false;
        m_arrPieces[i].type = i + 1;
        if(m_arrPieces[i].type > 4) m_arrPieces[i].type -= 3;
    }

    m_isDestroyed = false;

    m_ContentType = 0;
    m_ContentAmount = 0;
}
Container::~Container()
{

}
void Container::renderUnit()
{
    if(!m_isDestroyed) m_bmpContainers.renderImage((m_ContainerType -1) * 5, m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y);
}
void Container::renderExtra()
{
    for(int i = 0; i < 6; i += 1)
    {
        if(m_arrPieces[i].visible)
            m_bmpContainers.renderImage((m_ContainerType -1) * 5 + m_arrPieces[i].type, m_arrPieces[i].position.x - CAMERA->getPosition().x, m_arrPieces[i].position.y - CAMERA->getPosition().y);
    }
}
void Container::update()
{

    if(!m_isDestroyed) m_rgnCollision.moveTo(m_Position.x, m_Position.y);
    else
    {
        for(int i = 0; i < 6; i += 1)
        {
            if(m_arrPieces[i].visible)
            {
                if(m_arrPieces[i].speed.y < 0) m_arrPieces[i].speed.y += 2;
                else m_arrPieces[i].speed.y += 3;
                m_arrPieces[i].position += m_arrPieces[i].speed;

                if(m_arrPieces[i].position.y - CAMERA->getPosition().y > 480) m_arrPieces[i].visible = false;
            }
        }

        if(!(m_arrPieces[0].visible && m_arrPieces[1].visible && m_arrPieces[2].visible && m_arrPieces[3].visible && m_arrPieces[4].visible && m_arrPieces[5].visible)) m_IsGone = true;
    }
}
void Container::destroy()
{
    if(!m_isDestroyed)
    {
        m_rgnCollision.init(0, 0, 0, 0);

        m_isDestroyed = true;

        if(m_ContainerType == 1) SOUNDSYSTEM->playSound(CRATE);
        else if(m_ContainerType == 2) SOUNDSYSTEM->playSound(BARREL);
        else if(m_ContainerType == 3) SOUNDSYSTEM->playSound(POT);

        for(int i = 0; i < 6; i += 1)
        {
            m_arrPieces[i].visible = true;
            m_arrPieces[i].position = m_Position;

            if(i == 0) m_arrPieces[i].speed.x = 8;
            else if(i == 1) m_arrPieces[i].speed.x = -8;
            else if(i == 2) m_arrPieces[i].speed.x = 1;
            else m_arrPieces[i].speed.x = (rand() % 12) - 6;

            m_arrPieces[i].speed.y = -12 - (rand() % 6);
        }
    }
}
void Container::setContent(int type, int amount)
{
    m_ContentType = type;
    m_ContentAmount = amount;
}
