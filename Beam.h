//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef BEAM_H
#define BEAM_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "AnimatedSprite.h"
#include "SurfaceCache.h"

//-----------------------------------------------------
// Beam Class
//-----------------------------------------------------
class Beam
{
public:
    Beam();   //Constructor
    virtual ~Beam();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
    void init(int type, Vector2di Position, int direction);
    void render();
    void update();

    void setActive(bool active){m_isActive = active;}

    Vector2di getPosition(){return m_Position;}
    int getSpeed(){return m_Speed;}
    int getType(){return m_Type;}

private:

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    AnimatedSprite m_bmpImage;

    Vector2df m_Position;

    int m_Type, m_Direction, m_CarryingColour;
    float m_Speed;
    bool m_isActive;

};

#endif // BEAM_H
