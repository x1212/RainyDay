//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#define FCHECK (m_rgnCollision.hitTest(GAMEMANAGER->getHitRegion(), 32, 0))

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Enemy.h"
#include "GameManager.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
Enemy::Enemy()
{
    m_Type = UNIT_ENEMY;

    m_Speed.y = 0;

    m_bmpPoof.loadFrames("images/Effects/Poof.png", 6, 1);
	m_bmpPoof.setLooping(false);
    m_bmpPoof.setTransparentColour(MAGENTA);
    m_bmpPoof.setTimerScaler((float)1000 / 20.0f);

    m_bmpCurrentPtr = &m_bmpMovingLeft;

    m_IsIdling = false;
    m_IsDying = false;
    m_IsDead = false;
    m_IsChasing = false;
    m_IsStoned = false;

    m_Counter = 0;
}
Enemy::~Enemy()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void Enemy::initImages()
{
    string enemyName;
    int idleFrames = 0;

    //Check enemy type and change string
    switch(m_EnemyType)
    {
        case 1:
        {
            enemyName = "BasicBlue";
            idleFrames = 12;
            m_Speed.x = -6;

            m_rgnCollision.init(m_Position.x - 32, m_Position.y - 64, 64, 64);
        }
        break;

        case 2:
        {
            enemyName = "BasicYellow";
            m_Speed.x = -4;

            m_rgnCollision.init(m_Position.x - 50, m_Position.y - 50, 100, 100);
        }
        break;

        case 3:
        {
            enemyName = "BasicRed";
            m_Speed.x = -12;
            idleFrames = 4;

            m_rgnCollision.init(m_Position.x - 40, m_Position.y - 80, 80, 80);
        }
        break;
    }

    //Apply string to image loading
    m_bmpMovingLeft.loadFrames("images/Enemies/Enemy_" + enemyName + "_MovingLeft.png", 4, 1);
	m_bmpMovingLeft.setLooping(true);
    m_bmpMovingLeft.setTransparentColour(MAGENTA);
    m_bmpMovingLeft.setTimerScaler((float)1000 / 20.0f);

	m_bmpMovingRight.loadFrames("images/Enemies/Enemy_" + enemyName + "_MovingRight.png", 4, 1);
	m_bmpMovingRight.setLooping(true);
    m_bmpMovingRight.setTransparentColour(MAGENTA);
    m_bmpMovingRight.setTimerScaler((float)1000 / 20.0f);

    if(m_EnemyType == 1 || m_EnemyType == 3)
    {
        m_bmpIdle.loadFrames("images/Enemies/Enemy_" + enemyName + "_Idle.png", idleFrames, 1);
        m_bmpIdle.setLooping(true);
        m_bmpIdle.setTransparentColour(MAGENTA);
        m_bmpIdle.setTimerScaler((float)1000 / 20.0f);
    }

    m_bmpDead.loadFrames("images/Enemies/Enemy_" + enemyName + "_Dead.png", 2, 1);
	m_bmpDead.setLooping(false);
    m_bmpDead.setTransparentColour(MAGENTA);

    m_bmpStoned.loadFrames("images/Enemies/Enemy_" + enemyName + "_Stoned.png", 1, 1);
	m_bmpStoned.setLooping(false);
    m_bmpStoned.setTransparentColour(MAGENTA);
}
void Enemy::initBoundaries(int left, int right)
{
    m_Boundary.left = left + 32;
    m_Boundary.right = right - 32;
    m_Boundary.height = m_Position.y;
}
void Enemy::renderUnit()
{
    if(!m_IsDead) m_bmpCurrentPtr->render();

    //m_rgnCollision.render(CAMERA->getPosition().x, CAMERA->getPosition().y);
}
void Enemy::renderExtra()
{
    if(m_IsDead) m_bmpCurrentPtr->render();
}
void Enemy::update()
{
    //------------------------------------
    // Normal State
    //------------------------------------
    if(!m_IsStoned)
    {
        //BASIC BLUE
        if(m_EnemyType == 1)
        {
            if(!m_IsDying)
            {
                m_bmpCurrentPtr->update();

                if(m_Counter == 0 && rand() % 50 == 1 && !m_IsIdling)
                {
                    m_bmpCurrentPtr = &m_bmpIdle;
                    m_IsIdling = true;
                }

                if(m_IsIdling)
                {
                    if(m_bmpCurrentPtr->getCurrentFrame() == 11)
                    {
                        m_IsIdling = false;
                        m_bmpCurrentPtr->setCurrentFrame(0);

                        if(m_Speed.x < 0) m_bmpCurrentPtr = &m_bmpMovingLeft;
                        else if(m_Speed.x > 0) m_bmpCurrentPtr = &m_bmpMovingRight;

                        m_Counter = 32;
                    }
                }
                else
                {
                    if(m_Counter != 0) m_Counter -= 1;

                    move(m_Speed);

                    if(m_Position.x < m_Boundary.left || m_Position.x > m_Boundary.right)
                    {
                        m_Speed.x *= -1;
                        move(m_Speed);
                    }

                    if(m_Speed.x < 0) m_bmpCurrentPtr = &m_bmpMovingLeft;
                    else if(m_Speed.x > 0) m_bmpCurrentPtr = &m_bmpMovingRight;
                }
            }
            else if(!m_IsDead)
            {
                m_Speed.y += 2;
                move(m_Speed);

                if(m_rgnCollision.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))
                {
                    m_IsDead = true;
                    m_bmpCurrentPtr = &m_bmpPoof;
                    SOUNDSYSTEM->playSound(POOF);

                    GAMEMANAGER->spawnItem(3, 3, m_Position - Vector2di(0, 64 + 16));
                }
            }
            else if(m_IsDead)
            {
                if(m_bmpCurrentPtr->getCurrentFrame() == 5) m_IsGone = true;
                m_bmpCurrentPtr->update();
            }

            if(m_IsDead) m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 18, m_Position.y - CAMERA->getPosition().y -18);
            else m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 32, m_Position.y - CAMERA->getPosition().y - 64);
        }
        //BASIC YELLOW
        else if(m_EnemyType == 2)
        {
            if(!m_IsDying)
            {
                m_bmpCurrentPtr->update();

                //Chase Hero
                if(m_IsChasing)
                {
                    Vector2df v = Vector2df(GAMEMANAGER->getHeroPosition()->x + 90 - m_Position.x, GAMEMANAGER->getHeroPosition()->y + 72 - m_Position.y);
                    int distance = sqrt((v.x * v.x) + (v.y * v.y));

                    if(distance > 250) m_IsChasing = false;
                    else
                    {
                        v.normalise();
                        m_Speed = v * 5;

                        move(m_Speed);

                        if(v.x < 0) m_bmpCurrentPtr = &m_bmpMovingLeft;
                        else if(v.x > 0) m_bmpCurrentPtr = &m_bmpMovingRight;
                    }
                }
                else
                {
                    Vector2df v = Vector2df(GAMEMANAGER->getHeroPosition()->x + 90 - m_Position.x, GAMEMANAGER->getHeroPosition()->y + 72 - m_Position.y);
                    int distance = sqrt((v.x * v.x) + (v.y * v.y));

                    if(distance < 200 && ((m_Speed.x < 0 && GAMEMANAGER->getHeroPosition()->x < m_Position.x) || (m_Speed.x > 0 && GAMEMANAGER->getHeroPosition()->x > m_Position.x))) m_IsChasing = true;
                    else
                    {
                        if(m_Position.y == m_Boundary.height)
                        {
                            if(m_Position.x < m_Boundary.left) m_Speed.x = 4;
                            else if(m_Position.x > m_Boundary.right) m_Speed.x = -4;

                            move(m_Speed);
                        }
                        else
                        {
                            if(m_Position.y < m_Boundary.height) m_Speed.y = 1;
                            else if(m_Position.y > m_Boundary.height) m_Speed.y = -1;

                            move(Vector2di(m_Speed.x, 0));
                            for(int i = 0; i < 4; i++)
                            {
                                move(Vector2di(0, m_Speed.y));
                                if(m_Position.y == m_Boundary.height) break;
                            }
                        }

                        if(m_Speed.x < 0) m_bmpCurrentPtr = &m_bmpMovingLeft;
                        else if(m_Speed.x > 0) m_bmpCurrentPtr = &m_bmpMovingRight;
                    }
                }
            }
            else if(!m_IsDead)
            {
                m_Speed.y += 2;
                move(m_Speed);

                if(m_rgnCollision.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))
                {
                    m_IsDead = true;
                    m_bmpCurrentPtr = &m_bmpPoof;
                    SOUNDSYSTEM->playSound(POOF);

                    GAMEMANAGER->spawnItem(3, 3, m_Position - Vector2di(0, 50 + 16));
                }
            }
            else if(m_IsDead)
            {
                if(m_bmpCurrentPtr->getCurrentFrame() == 5) m_IsGone = true;
                m_bmpCurrentPtr->update();
            }

            if(m_IsDead) m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 18, m_Position.y - CAMERA->getPosition().y -18);
            else
            {
                int height = 0;

                //Hovering motion for flying enemies
                if(m_Counter < 12) m_Counter += 1;
                else m_Counter = 0;

                switch(m_Counter)
                {
                    case 0: {height = 0;} break;
                    case 1: {height = 2;} break;
                    case 2: {height = 4;} break;
                    case 3: {height = 6;} break;
                    case 4: {height = 4;} break;
                    case 5: {height = 2;} break;
                    case 6: {height = 0;} break;
                    case 7: {height = -2;} break;
                    case 8: {height = -4;} break;
                    case 9: {height = -6;} break;
                    case 10: {height = -4;} break;
                    case 11: {height = -2;} break;
                }
                m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 50, m_Position.y - CAMERA->getPosition().y - 50 + height);
            }
        }
        //BASIC RED
        else if(m_EnemyType == 3)
        {
            if(!m_IsDying)
            {
                m_bmpCurrentPtr->update();

                m_Counter -= 1;

                if(m_IsIdling)
                {
                    if(m_Counter == 0)
                    {
                        m_IsIdling = false;

                        if(m_Speed.x == 0)
                        {
                            m_Speed.x = -12;
                            if(rand() % 2 == 0) m_Speed.x *= -1;
                        }

                        if(m_Speed.x < 0) m_bmpCurrentPtr = &m_bmpMovingLeft;
                        else if(m_Speed.x > 0) m_bmpCurrentPtr = &m_bmpMovingRight;

                        m_Counter = 10 + rand() % 20;
                    }
                }
                else
                {
                    if(m_Counter == 0)
                    {
                        m_bmpCurrentPtr = &m_bmpIdle;
                        m_IsIdling = true;
                        m_Speed.x = 0;

                        m_Counter = 24;
                    }
                    else
                    {
                        move(m_Speed);

                        if(m_Position.x < m_Boundary.left || m_Position.x > m_Boundary.right)
                        {
                            if(m_Position.x < m_Boundary.left) m_Speed.x = 12;
                            if(m_Position.x > m_Boundary.right) m_Speed.x = -12;

                            move(m_Speed);

                            m_bmpCurrentPtr = &m_bmpIdle;
                            m_IsIdling = true;

                            m_Counter = 24;
                        }
                    }
                }
            }
            else if(!m_IsDead)
            {
                m_Speed.y += 2;
                move(m_Speed);

                if(m_rgnCollision.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))
                {
                    m_IsDead = true;
                    m_bmpCurrentPtr = &m_bmpPoof;
                    SOUNDSYSTEM->playSound(POOF);

                    GAMEMANAGER->spawnItem(3, 3, m_Position - Vector2di(0, 40 + 16));
                }
            }
            else if(m_IsDead)
            {
                if(m_bmpCurrentPtr->getCurrentFrame() == 5) m_IsGone = true;
                m_bmpCurrentPtr->update();
            }

            if(m_IsDead) m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 18, m_Position.y - CAMERA->getPosition().y - 18 - 100);
            else m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 40, m_Position.y - CAMERA->getPosition().y - 80);
        }
    }

    //------------------------------------
    // Stoned State
    //------------------------------------
    else
    {
        m_bmpCurrentPtr->setPosition(m_Position.x - CAMERA->getPosition().x - 40, m_Position.y - CAMERA->getPosition().y - 80);
    }
}
void Enemy::kill(int direction)
{
    if(!m_IsDying)
    {
        HUD->setScore(500);
        SOUNDSYSTEM->playSound(KILL);
        m_IsDying = true;
        m_bmpCurrentPtr = &m_bmpDead;
        if(direction == DIR_LEFT)
        {
            m_Speed.x = -16;
            m_bmpCurrentPtr->setCurrentFrame(1);
        }
        else if(direction == DIR_RIGHT)
        {
            m_Speed.x = 16;
            m_bmpCurrentPtr->setCurrentFrame(0);
        }
        m_Speed.y = -14;
    }
}
void Enemy::turnToStone(Vector2di& pos, int& type)
{
    if(!m_IsDying)
    {
        pos = m_Position;
        type = m_EnemyType;

        switch(m_EnemyType)
        {
            case 1:
                pos.y -= (64 + 36);
            break;

            case 2:
                pos.y -= 50;
            break;

            case 3:
                pos.x -= 50;
                pos.y -= 100;
            break;
        }
        m_IsGone = true;
    }
}
void Enemy::move(Vector2di offset)
{
    m_Position += offset;
    m_rgnCollision.move(offset.x, offset.y);
}
