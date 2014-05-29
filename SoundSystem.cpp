//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "SoundSystem.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
SoundSystem::SoundSystem()
{

}
SoundSystem::~SoundSystem()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void SoundSystem::init()
{
    //FOOTSTEP
    m_sndArray[0].loadSound("sounds/Step1.ogg");
	m_sndArray[1].loadSound("sounds/Step2.ogg");
	m_sndArray[2].loadSound("sounds/Step3.ogg");
	m_sndArray[3].loadSound("sounds/Step4.ogg");

    //LAND
	m_sndArray[4].loadSound("sounds/Land.ogg");

	//ATTACK
    m_sndArray[5].loadSound("sounds/Attack1.ogg");
	m_sndArray[6].loadSound("sounds/Attack2.ogg");
	m_sndArray[7].loadSound("sounds/Attack3.ogg");
	m_sndArray[8].loadSound("sounds/Attack4.ogg");

	//JUMP
    m_sndArray[9].loadSound("sounds/Jump1.ogg");
	m_sndArray[10].loadSound("sounds/Jump2.ogg");
	m_sndArray[11].loadSound("sounds/Jump3.ogg");
	m_sndArray[12].loadSound("sounds/Jump4.ogg");

    //ITEM
	m_sndArray[13].loadSound("sounds/ItemTake.ogg");

	//THUNDER
	m_sndArray[14].loadSound("sounds/Thunder1.ogg");
	m_sndArray[15].loadSound("sounds/Thunder2.ogg");
	m_sndArray[16].loadSound("sounds/Thunder3.ogg");
	m_sndArray[17].loadSound("sounds/Thunder4.ogg");

	m_sndArray[18].loadSound("sounds/Pain.ogg");
	m_sndArray[19].loadSound("sounds/Kill.ogg");

	//CONTAINERS
	m_sndArray[20].loadSound("sounds/Crate.ogg");
	m_sndArray[21].loadSound("sounds/Pot.ogg");
	m_sndArray[22].loadSound("sounds/Barrel.ogg");

	m_sndArray[23].loadSound("sounds/ItemHit.ogg");

	m_sndArray[24].loadSound("sounds/GrabBeam.ogg");
	m_sndArray[25].loadSound("sounds/Shoot.ogg");

	m_sndArray[26].loadSound("sounds/Poof.ogg");
}
void SoundSystem::playSound(int sound)
{
    if(sound == FOOTSTEP || sound == ATTACK || sound == JUMP)
    {
        int i = (rand() % 4) + sound;
        m_sndArray[i].play();
    }
    else m_sndArray[sound].play();
}
void SoundSystem::stopSound(int sound)
{
    m_sndArray[sound].stop();
}
