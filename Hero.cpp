//---------------------------
// Includes
//---------------------------
#include "Hero.h"
#include "GameManager.h"

//---------------------------
// Defines
//---------------------------
#define HCHECK (m_rgnHead.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))
#define BCHECK (GAMEMANAGER->checkUnitCollision(m_rgnBody, "HERO") || m_rgnBody.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))
#define FCHECK (GAMEMANAGER->checkUnitCollision(m_rgnFeet, "HERO") || m_rgnFeet.hitTest(GAMEMANAGER->getHitRegion(), 0, 0))

#define FCHECK_S1 (m_rgnFeet.colourTest(GAMEMANAGER->getHitRegion(), 0, 24) == Colour(WHITE))
#define FCHECK_S2 (m_rgnFeet.colourTest(GAMEMANAGER->getHitRegion(), 30, 24) == Colour(WHITE))
#define FCHECK_S3 (m_rgnFeet.colourTest(GAMEMANAGER->getHitRegion(), 60, 24) == Colour(WHITE))

//---------------------------
// Constructor & Destructor
//---------------------------
Hero::Hero()
{

}

Hero::~Hero()
{

}

//---------------------------
// Eigen methoden
//---------------------------
void Hero::init()
{
    m_Position.x = 420;
    m_Position.y = 871;
    GAMEMANAGER->initHeroPosition(m_Position);

    m_Speed.x = 0;
    m_Speed.y = 16;

    m_FallThrough = false;
    m_ShowBeam = false;

    m_NewPosition = Vector2di(-1, -1);

    //STANDING
	m_bmpStandingLeft.loadFrames("images/Hero/Hero_StandingLeft.png", 4, 1);
	m_bmpStandingLeft.setLooping(true);
    m_bmpStandingLeft.setTransparentColour(MAGENTA);
    m_bmpStandingLeft.setFrameRate(DECI_SECONDS);

	m_bmpStandingRight.loadFrames("images/Hero/Hero_StandingRight.png", 4, 1);
	m_bmpStandingRight.setLooping(true);
    m_bmpStandingRight.setTransparentColour(MAGENTA);
    m_bmpStandingRight.setFrameRate(DECI_SECONDS);

    //WALKING
	m_bmpWalkingLeft.loadFrames("images/Hero/Hero_WalkingLeft.png", 8, 1);
	m_bmpWalkingLeft.setLooping(true);
    m_bmpWalkingLeft.setTransparentColour(MAGENTA);
    m_bmpWalkingLeft.setTimerScaler((float)1000 / 20.0f);

	m_bmpWalkingRight.loadFrames("images/Hero/Hero_WalkingRight.png", 8, 1);
	m_bmpWalkingRight.setLooping(true);
    m_bmpWalkingRight.setTransparentColour(MAGENTA);
    m_bmpWalkingRight.setTimerScaler((float)1000 / 20.0f);

    //JUMPING
    m_bmpJumpingLeft.loadFrames("images/Hero/Hero_JumpingLeft.png", 4, 1);
	m_bmpJumpingLeft.setLooping(true);
    m_bmpJumpingLeft.setTransparentColour(MAGENTA);
    m_bmpJumpingLeft.setFrameRate(DECI_SECONDS);

    m_bmpJumpingRight.loadFrames("images/Hero/Hero_JumpingRight.png", 4, 1);
	m_bmpJumpingRight.setLooping(true);
    m_bmpJumpingRight.setTransparentColour(MAGENTA);
    m_bmpJumpingRight.setFrameRate(DECI_SECONDS);

    //FALLING
    m_bmpFallingLeft.loadFrames("images/Hero/Hero_FallingLeft.png", 4, 1);
	m_bmpFallingLeft.setLooping(true);
    m_bmpFallingLeft.setTransparentColour(MAGENTA);
    m_bmpFallingLeft.setFrameRate(DECI_SECONDS);

    m_bmpFallingRight.loadFrames("images/Hero/Hero_FallingRight.png", 4, 1);
	m_bmpFallingRight.setLooping(true);
    m_bmpFallingRight.setTransparentColour(MAGENTA);
    m_bmpFallingRight.setFrameRate(DECI_SECONDS);

    //ATTACKING
    m_bmpAttackLeft.loadFrames("images/Hero/Hero_AttackLeft.png", 8, 1);
	m_bmpAttackLeft.setLooping(false);
    m_bmpAttackLeft.setTransparentColour(MAGENTA);
    m_bmpAttackLeft.setTimerScaler((float)1000 / 20.0f);

    m_bmpAttackRight.loadFrames("images/Hero/Hero_AttackRight.png", 8, 1);
	m_bmpAttackRight.setLooping(false);
    m_bmpAttackRight.setTransparentColour(MAGENTA);
    m_bmpAttackRight.setTimerScaler((float)1000 / 20.0f);

    //ATTACKJUMPING
    m_bmpAttackJumpLeft.loadFrames("images/Hero/Hero_AttackJumpLeft.png", 8, 1);
	m_bmpAttackJumpLeft.setLooping(false);
    m_bmpAttackJumpLeft.setTransparentColour(MAGENTA);
    m_bmpAttackJumpLeft.setTimerScaler((float)1000 / 20.0f);

    m_bmpAttackJumpRight.loadFrames("images/Hero/Hero_AttackJumpRight.png", 8, 1);
	m_bmpAttackJumpRight.setLooping(false);
    m_bmpAttackJumpRight.setTransparentColour(MAGENTA);
    m_bmpAttackJumpRight.setTimerScaler((float)1000 / 20.0f);

    //SHOOTING
    m_bmpShootLeft.loadFrames("images/Hero/Hero_ShootLeft.png", 8, 1);
	m_bmpShootLeft.setLooping(false);
    m_bmpShootLeft.setTransparentColour(MAGENTA);
    m_bmpShootLeft.setTimerScaler((float)1000 / 20.0f);

    m_bmpShootRight.loadFrames("images/Hero/Hero_ShootRight.png", 8, 1);
	m_bmpShootRight.setLooping(false);
    m_bmpShootRight.setTransparentColour(MAGENTA);
    m_bmpShootRight.setTimerScaler((float)1000 / 20.0f);

    //SHOOTJUMPING
    m_bmpShootJumpLeft.loadFrames("images/Hero/Hero_ShootJumpLeft.png", 8, 1);
	m_bmpShootJumpLeft.setLooping(false);
    m_bmpShootJumpLeft.setTransparentColour(MAGENTA);
    m_bmpShootJumpLeft.setTimerScaler((float)1000 / 20.0f);

    m_bmpShootJumpRight.loadFrames("images/Hero/Hero_ShootJumpRight.png", 8, 1);
	m_bmpShootJumpRight.setLooping(false);
    m_bmpShootJumpRight.setTransparentColour(MAGENTA);
    m_bmpShootJumpRight.setTimerScaler((float)1000 / 20.0f);

    //OTHER
    m_bmpPain.loadFrames("images/Hero/Hero_Pain.png", 2, 1);
	m_bmpPain.setLooping(false);
    m_bmpPain.setTransparentColour(MAGENTA);

    m_bmpImpact.loadFrame("images/Effects/Umbrella_Impact.png");
    m_bmpImpact.setTransparentColour(MAGENTA);

	m_bmpCurrentPtr = &m_bmpStandingRight;
	m_bmpCurrentPtr->setPosition(m_Position);

	m_Direction = DIR_RIGHT;
	m_IsWalking = false;
	m_IsInAir = true;
	m_IsAttacking = false;
	m_IsShooting = false;

	m_rgnHead.init(60, 0, 60, 12);
	m_rgnBody.init(60, 12, 60, 106);
	m_rgnFeet.init(60, 118, 60, 24);

	CAMERA->setPlayerDimensions(180, 144);

	m_PlayStep = true;
	m_SoundFix = false;
	m_CheckSwitch = false;
    m_UmbrellaHasHit = false;
	m_IsInvincible = false;

	m_InvincibleCounter = 0;
	m_CarryingColour = 0;
}
void Hero::render()
{
    if(m_IsInvincible)
    {
        if(m_IsShown)
        {
            m_bmpCurrentPtr->render();
            m_IsShown = false;
        }
        else m_IsShown = true;

        m_InvincibleCounter -= 1;
        if(m_InvincibleCounter == 0) m_IsInvincible = false;
    }
    else m_bmpCurrentPtr->render();

    if(m_ShowImpact) m_bmpImpact.render();
    cout << "ping" << endl;
    m_Beam.render();
    if(m_CarryingColour > 0)
    {
        m_bmpCarryingColour.render();
    }

    //m_rgnHead.render(CAMERA->getPosition().x, CAMERA->getPosition().y);
	//m_rgnBody.render(CAMERA->getPosition().x, CAMERA->getPosition().y);
	//m_rgnFeet.render(CAMERA->getPosition().x, CAMERA->getPosition().y);
}
void Hero::update()
{
    //LEVEL PART SWITCHING STUFF
    if(m_NewPosition.x > 0 && EFFECTSYSTEM->getFadeAlpha() >= 255)
    {
        if(m_Position.x - CAMERA->getPosition().x > 800) CAMERA->moveTo(Vector2di(180, 0));
        if(m_Position.x - CAMERA->getPosition().x < -180) CAMERA->moveTo(Vector2di(GAMEMANAGER->getPartWidth(), 0));
        m_Position = m_NewPosition;
        m_NewPosition = Vector2di(-1, -1);
        return;
    }
    else if(m_NewPosition.x > 0) return;

    //END OF ATTACKING ANIMATION
    if (m_IsAttacking && m_bmpCurrentPtr->getCurrentFrame() == 6)
    {
         m_bmpCurrentPtr->setCurrentFrame(0);

        if(!m_IsInAir)
        {
            //LEFT
            if(m_Direction == DIR_LEFT)
                m_bmpCurrentPtr = &m_bmpStandingLeft;

            //RIGHT
            else if(m_Direction == DIR_RIGHT)
                m_bmpCurrentPtr = &m_bmpStandingRight;
        }
        else
        {
            if(m_Speed.y <= 0)
            {
                //LEFT
                if(m_Direction == DIR_LEFT)
                    m_bmpCurrentPtr = &m_bmpJumpingLeft;

                //RIGHT
                else if(m_Direction == DIR_RIGHT)
                    m_bmpCurrentPtr = &m_bmpJumpingRight;
            }
            else
            {
                //LEFT
                if(m_Direction == DIR_LEFT)
                    m_bmpCurrentPtr = &m_bmpFallingLeft;

                //RIGHT
                else if(m_Direction == DIR_RIGHT)
                    m_bmpCurrentPtr = &m_bmpFallingRight;

                m_IsInAir = true;
            }
        }

        m_bmpCurrentPtr->setCurrentFrame(0);

        m_IsAttacking = false;
        m_IsShooting = false;
        m_UmbrellaHasHit = false;
    }
    else
    {
        //SETTING DIRECTION
        if(!m_IsAttacking)
        {
            //LEFT
            if(input->isLeft() && !input->isRight()) m_Direction = DIR_LEFT;

            //RIGHT
            else if(input->isRight() && !input->isLeft()) m_Direction = DIR_RIGHT;
        }

        if(m_Speed.y == 17)
        {
            //CHANGING ATTACK ANIMATION WHEN LANDING
            if(m_IsAttacking)
            {
                int frame = m_bmpCurrentPtr->getCurrentFrame();
                m_bmpCurrentPtr->setCurrentFrame(0);

                if(m_IsShooting)
                {
                    //LEFT
                    if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpShootLeft;
                    //RIGHT
                    else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpShootRight;
                }
                else
                {
                    //LEFT
                    if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpAttackLeft;
                    //RIGHT
                    else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpAttackRight;
                }

                m_bmpCurrentPtr->setCurrentFrame(frame);

                if(m_IsInAir) SOUNDSYSTEM->playSound(LAND);
            }
            else
            {
                if(m_IsInAir && m_SoundFix) SOUNDSYSTEM->playSound(LAND);
                if(!m_SoundFix) m_SoundFix = true;

                //STANDING

                //LEFT
                if(m_Direction == DIR_LEFT && (!input->isLeft() || input->isRight())) m_bmpCurrentPtr = &m_bmpStandingLeft;
                //RIGHT
                else if(m_Direction == DIR_RIGHT && (!input->isRight() || input->isLeft())) m_bmpCurrentPtr = &m_bmpStandingRight;

                //WALKING

                 //LEFT
                if(m_Direction == DIR_LEFT && input->isLeft() && !(input->isRight())) m_bmpCurrentPtr = &m_bmpWalkingLeft;
                //RIGHT
                else if(m_Direction == DIR_RIGHT && input->isRight() && !(input->isLeft())) m_bmpCurrentPtr = &m_bmpWalkingRight;
            }

             m_IsInAir = false;
        }
        else if(m_Speed.y <= 0)
        {
            m_IsInAir = true;

            if(!m_IsAttacking)
            {
                //LEFT
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpJumpingLeft;
                //RIGHT
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpJumpingRight;
            }
        }
        else if(m_Speed.y > 0 && m_Speed.y < 17)
        {
            m_IsInAir = true;

            if(!m_IsAttacking)
            {
                //LEFT
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpFallingLeft;
                //RIGHT
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpFallingRight;
            }
        }
    }

    if(m_CheckSwitch)
    {
        //PAIN COLLISION STUFF

        if(!m_IsInvincible)
        {
            HitRegion temp;
            temp.init(m_Position.x + 60, m_Position.y + 12, 60, 106);

            if(GAMEMANAGER->checkUnitCollision(temp, "BODY", m_Direction))
            {
                m_bmpCurrentPtr = &m_bmpPain;
                m_bmpCurrentPtr->setPosition(Vector2di(m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y));
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr->setCurrentFrame(0);
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr->setCurrentFrame(1);
                m_IsInvincible = true;
                HUD->setHealth(-1);
                m_InvincibleCounter = 48;
                m_IsShown = true;
                SOUNDSYSTEM->playSound(PAIN);
            }
        }

        //ITEM COLLISION
        HitRegion temp;
        temp.init(m_Position.x + 60, m_Position.y + 12, 60, 100);
        GAMEMANAGER->checkUnitCollision(temp, "BODY", m_Direction);

        m_CheckSwitch = false;
    }
    else m_CheckSwitch = true;

    m_bmpCurrentPtr->setPosition(Vector2di(m_Position.x - CAMERA->getPosition().x, m_Position.y - CAMERA->getPosition().y));

    if(m_Speed.y < 16) m_Speed.y += 2;
    move(0, m_Speed.y);

    if(FCHECK_S1 || FCHECK_S2 || FCHECK_S3)
    {
        if(m_Speed.y == 0) m_FallThrough = true;
        if(m_Speed.y > 0 && !m_FallThrough)
        {
            while(FCHECK_S1 || FCHECK_S2 || FCHECK_S3) move(0, -1);
            m_Speed.y = 17;
        }

        m_FallThrough = false;
    }
    else
    {
        if(FCHECK)
        {
            m_Speed.y = 17;
        }
        while(FCHECK) move(0, -1);
        if(m_Speed.y == 17)
        {
            move(0, 1);
            if(!FCHECK) m_Speed.y = 16;
            move(0, -1);

            m_FallThrough = false;
        }
    }

    if(m_InvincibleCounter < 47) m_bmpCurrentPtr->update();

    if(m_IsAttacking && !m_IsShooting)
        m_bmpCurrentPtr->setPosition(Vector2di(m_Position.x - CAMERA->getPosition().x - 30, m_Position.y - CAMERA->getPosition().y));

    //ATTACKING COLLISION STUFF
    if(m_IsAttacking)
    {
        if(m_bmpCurrentPtr->getCurrentFrame() > 2 && !m_UmbrellaHasHit && !m_IsShooting)
        {
            HitRegion temp;
            if(m_Direction == DIR_LEFT) temp.init(m_Position.x - 14, m_Position.y + 48, 64, 80);
            else if(m_Direction == DIR_RIGHT) temp.init(m_Position.x + 130, m_Position.y + 48, 64, 80);

            GAMEMANAGER->checkUnitCollision(temp, "UMBRELLA", m_Direction);

            m_UmbrellaHasHit = true;
        }
    }

    if(m_ShowImpact)
    {
        m_bmpImpact.setPosition(m_ImpactPos.x - CAMERA->getPosition().x, m_ImpactPos.y - CAMERA->getPosition().y);

        if(m_bmpCurrentPtr->getCurrentFrame() > 4) m_ShowImpact = false;
    }

    //BEAM
    if(m_Beam.getType() == 0)
    {
        HitRegion temp;
        temp.init(m_Beam.getPosition().x, m_Beam.getPosition().y, 52, 52);
        if(temp.hitTest(&m_rgnBody) && m_Beam.getSpeed() < 0)
        {
            m_Beam.setActive(false);
            m_ShowBeam = false;
            SOUNDSYSTEM->stopSound(GRABBEAM);
            m_CarryingColour = 0;
        }
        else
        {
            GAMEMANAGER->checkUnitCollision(temp, "GRABBEAM", m_Direction);
            setCarryingColour(GAMEMANAGER->getCapturedColour());
        }
    }
    else
    {
        if(m_Beam.getPosition().x - CAMERA->getPosition().x < 0  || m_Beam.getPosition().x - CAMERA->getPosition().x > 800)
        {
            m_Beam.setActive(false);
            m_ShowBeam = false;
        }
    }

    m_Beam.update();
    m_bmpCarryingColour.setPosition(m_Beam.getPosition() + Vector2di(8, 6) - CAMERA->getPosition());
    m_bmpCarryingColour.update();
}
void Hero::userInput()
{
    if((!m_IsInAir && !m_IsAttacking) || m_IsInAir)
    {
        //LEFT
        if(input->isLeft() && !input->isRight() && m_Direction == DIR_LEFT)
        {
            //FOOTSTEP SOUNDS
            if(!m_IsInAir & m_PlayStep)
            {
                SOUNDSYSTEM->playSound(FOOTSTEP);
                m_PlayStep = false;
            }
            else if(m_bmpCurrentPtr->getCurrentFrame() == 1 || m_bmpCurrentPtr->getCurrentFrame() == 5)
            {
                m_PlayStep = true;
            }

            //MOVEMENT
            move(-1, 0);
            if(BCHECK) move(1, 0);
            else
            {
                move(-11, 0);
                while(BCHECK) move(1, 0);
            }
        }
        //RIGHT
        else if(input->isRight() && !input->isLeft() && m_Direction == DIR_RIGHT)
        {
            //FOOTSTEP SOUNDS
            if(!m_IsInAir & m_PlayStep)
            {
                SOUNDSYSTEM->playSound(FOOTSTEP);
                m_PlayStep = false;
            }
            else if(m_bmpCurrentPtr->getCurrentFrame() == 1 || m_bmpCurrentPtr->getCurrentFrame() == 5)
            {
                m_PlayStep = true;
            }

            //MOVEMENT
            move(1, 0);
            if(BCHECK) move(-1, 0);
            else
            {
                move(11, 0);
                while(BCHECK) move(-1, 0);
            }
        }
    }

    if(!m_IsAttacking)
    {
        if(INPUT->isPressed(BTN_JUMP) && m_Speed.y == 17)
        {
            SOUNDSYSTEM->playSound(JUMP);
            m_Speed.y = -24;
            m_IsInAir = true;
            if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpJumpingLeft;
            else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpJumpingRight;
            INPUT->resetButton(BTN_JUMP);
        }

        if(INPUT->isPressed(BTN_ATTACK))
        {
            SOUNDSYSTEM->playSound(ATTACK);
            m_IsAttacking = true;
            m_Speed.x = 0;

            if(!m_IsInAir)
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpAttackLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpAttackRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }
            else
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpAttackJumpLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpAttackJumpRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }
            INPUT->resetButton(BTN_ATTACK);
        }
        else if(INPUT->isPressed(BTN_GRAB) && !m_ShowBeam)
        {
            SOUNDSYSTEM->playSound(SHOOT);
            SOUNDSYSTEM->playSound(GRABBEAM);
            m_IsAttacking = true;
            m_IsShooting = true;
            m_Speed.x = 0;

            m_ShowBeam = true;

            //SET POSITION
            if(m_Direction == DIR_LEFT) m_Beam.init(0, Vector2di(m_Position.x, m_Position.y + 84), -1);
            else if(m_Direction == DIR_RIGHT) m_Beam.init(0, Vector2di(m_Position.x + 140, m_Position.y + 84), 1);
            m_Beam.setActive(true);

            if(!m_IsInAir)
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpShootLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpShootRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }
            else
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpShootJumpLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpShootJumpRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }

            INPUT->resetButton(BTN_GRAB);
        }
        else if(INPUT->isPressed(BTN_SHOOT) && !m_ShowBeam)
        {
            SOUNDSYSTEM->playSound(SHOOT);
            //SOUNDSYSTEM->playSound(GRABBEAM);
            m_IsAttacking = true;
            m_IsShooting = true;
            m_Speed.x = 0;

            m_ShowBeam = true;

            //SET POSITION
            if(m_Direction == DIR_LEFT) m_Beam.init(1, Vector2di(m_Position.x, m_Position.y + 84), -1);
            else if(m_Direction == DIR_RIGHT) m_Beam.init(1, Vector2di(m_Position.x + 140, m_Position.y + 84), 1);
            m_Beam.setActive(true);

            if(!m_IsInAir)
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpShootLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpShootRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }
            else
            {
                if(m_Direction == DIR_LEFT) m_bmpCurrentPtr = &m_bmpShootJumpLeft;
                else if(m_Direction == DIR_RIGHT) m_bmpCurrentPtr = &m_bmpShootJumpRight;
                m_bmpCurrentPtr->setCurrentFrame(0);
            }

            INPUT->resetButton(BTN_SHOOT);
        }
    }

	if(HCHECK)
	{
	    while(HCHECK) move(0, 1);
	    if(m_Speed.y < 0) m_Speed.y = 0;
	}

    //Horizontal
    if(!(CAMERA->getPosition().x <= 180))
    {
        if((m_Position.x - CAMERA->getPosition().x) < CAMERA->getBoundingBox().left)
        {
            CAMERA->move(Vector2di(-12, 0));
        }
    }

    if(!(CAMERA->getPosition().x > GAMEMANAGER->getPartWidth() - 12))
    {
        if((m_Position.x - CAMERA->getPosition().x) > CAMERA->getBoundingBox().right)
        {
            CAMERA->move(Vector2di(12, 0));
        }
    }

    //Vertical
    if(CAMERA->getPosition().y != 0)
    {
        while((m_Position.y - CAMERA->getPosition().y) < CAMERA->getBoundingBox().top && CAMERA->getPosition().y != 0)
        {
            CAMERA->move(Vector2di(0, -1));
        }
    }

    if(!(CAMERA->getPosition().y > GAMEMANAGER->getPartHeight()))
    {
        while((m_Position.y - CAMERA->getPosition().y) > CAMERA->getBoundingBox().bottom)
        {
            CAMERA->move(Vector2di(0, 1));
        }
    }
}
void Hero::move(int x, int y)
{
	m_Position.x += x;
	m_Position.y += y;

    m_rgnHead.moveTo(m_Position.x + 60, m_Position.y);
	m_rgnBody.moveTo(m_Position.x + 60, m_Position.y + 12);
    m_rgnFeet.moveTo(m_Position.x + 60, m_Position.y + 118);
}
void Hero::setCarryingColour(int colour)
{
    if(colour > 0)
    {
        m_CarryingColour = colour;

        m_bmpCarryingColour.loadFrames(SURFACE_CACHE->loadSurface("images/EFFECTSYSTEMs/CarryingColours.png"), 4, 3, (colour-1) * 4, 2);

        GAMEMANAGER->setCapturedColour(0);
    }
}
