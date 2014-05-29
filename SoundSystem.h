//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#define FOOTSTEP (0)
#define LAND (4)
#define ATTACK (5)
#define JUMP (9)
#define ITEMTAKE (13)
#define THUNDER1 (14)
#define THUNDER2 (15)
#define THUNDER3 (16)
#define THUNDER4 (17)
#define PAIN (18)
#define KILL (19)
#define CRATE (20)
#define POT (21)
#define BARREL (22)
#define ITEMHIT (23)
#define GRABBEAM (24)
#define SHOOT (25)
#define POOF (26)

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Sound.h"

//-----------------------------------------------------
// SoundSystem Class
//-----------------------------------------------------
class SoundSystem
{
public:
    SoundSystem();   //Constructor
    virtual ~SoundSystem();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
    void init();
    void playSound(int sound);
    void stopSound(int sound);

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

    Sound m_sndArray[32];

};

#endif // SOUNDSYSTEM_H
