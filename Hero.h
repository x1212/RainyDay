#ifndef HERO_H
#define HERO_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "HitRegion.h"
#include "AnimatedSprite.h"
#include "Vector2di.h"
#include "SimpleJoy.h"
#include "Sound.h"
#include "Beam.h"

//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#define DIR_LEFT (-1)
#define DIR_RIGHT (1)

class Hero
{
public:
	Hero();
	virtual ~Hero();

    void init();

	void render();
	void update();
	void userInput();

	void setInput(SimpleJoy* j){input = j;}
	void setNewPosition(Vector2di position){m_NewPosition = position;}
	void setCarryingColour(int colour);

    Vector2di getPosition(){return m_Position;}
	HitRegion getRegion(){return m_rgnBody;}

private:

	void move(int x, int y);

	Vector2di m_Position, m_NewPosition, m_Speed, m_ImpactPos;
	int m_Direction, m_InvincibleCounter, m_CarryingColour;
	bool m_FallThrough, m_ShowImpact, m_ShowBeam, m_CheckSwitch;
	AnimatedSprite *m_bmpCurrentPtr, m_bmpStandingLeft, m_bmpStandingRight, m_bmpWalkingLeft, m_bmpWalkingRight,
	                m_bmpJumpingLeft, m_bmpJumpingRight, m_bmpFallingLeft, m_bmpFallingRight,
	                m_bmpAttackLeft, m_bmpAttackRight, m_bmpAttackJumpLeft, m_bmpAttackJumpRight,
	                m_bmpShootLeft, m_bmpShootRight, m_bmpShootJumpLeft, m_bmpShootJumpRight,
	                m_bmpPain, m_bmpImpact, m_bmpCarryingColour;

	HitRegion m_rgnFeet, m_rgnBody, m_rgnHead;
	bool m_IsWalking, m_IsInAir, m_IsAttacking, m_IsShooting, m_IsInvincible, m_IsShown;

	SimpleJoy *input;

	bool m_PlayStep, m_SoundFix, m_UmbrellaHasHit;

	Beam m_Beam;
};

#endif	//	HERO_H
