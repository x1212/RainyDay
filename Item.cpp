#include "Item.h"
#include "GameManager.h"

#define CCHECK (m_rgnCollision.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))

Item::Item()
{
    m_Type = UNIT_ITEM;
    m_HitPosition = 0;

    m_SpriteSheet.loadImageSheet("images/Items.png", 6, 1);
    m_bmpBling.loadFrames("images/Effects/Bling.png", 4, 1);
    m_bmpBling.setTimerScaler((float)1000 / 20.0f);
    m_bmpBling.setLooping(3);

    m_bmpRaindrop.loadFrames(SURFACE_CACHE->loadSurface("images/Tokens_Raindrop.png"), 6, 1, 0, 6);
    m_bmpRaindrop.setTimerScaler((float)1000 / 22.0f);
    m_bmpRaindrop.setLooping(true);
    m_bmpRaindrop.setCurrentFrame(rand() % 6);

    m_rgnCollision.init(0, 0, 40, 40);

    m_IsStatic = false;
}
Item::~Item()
{

}
void Item::renderUnit()
{
    if(m_ItemType > 0 && m_ItemType != 3) m_SpriteSheet.renderImage(m_ItemType - 1, m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y);
    if(m_ItemType == 3)
    {
        m_bmpRaindrop.setPosition(m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y);
        m_bmpRaindrop.render();
    }

    if(m_ItemType == 0)
    {
        m_bmpBling.setPosition(m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y);
        m_bmpBling.render();
    }
}
void Item::update()
{
    if(!m_IsStatic && !m_ItemType == 0)
    {
        if(m_Speed.y <= 16) m_Speed.y += 2;
        m_Position += m_Speed;
        m_rgnCollision.moveTo(m_Position.x, m_Position.y);

        if(m_HitPosition == 0)
        {
            if(CCHECK)
            {
                while(CCHECK)
                {
                    m_Position.y -= 1;
                    m_rgnCollision.move(0, -1);
                }
                m_HitPosition = m_Position.y;
                m_Speed.x = 0;
                m_BounceSpeed = m_Speed.y;
                m_Speed.y = (m_BounceSpeed * -1) + 2;

                SOUNDSYSTEM->playSound(ITEMHIT);
            }
        }
        else if(m_HitPosition == m_Position.y)
        {
            m_BounceSpeed -= 6;
            SOUNDSYSTEM->playSound(ITEMHIT);

            if(m_BounceSpeed > 1) m_Speed.y = m_BounceSpeed * -1;
            else m_IsStatic = true;
        }
    }

    if(m_ItemType == 3) m_bmpRaindrop.update();

    if(m_ItemType == 0)
    {
        m_bmpBling.update();

        if(m_bmpBling.hasFinished()) m_IsGone = true;
    }
}
void Item::collect()
{
    if(m_ItemType != 0)
    {
        if(m_ItemType == 3)HUD->setScore(10);
        m_ItemType = 0;
        SOUNDSYSTEM->playSound(ITEMTAKE);
    }
}
