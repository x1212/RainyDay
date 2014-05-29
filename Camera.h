//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef Camera_H
#define Camera_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Vector2di.h"
#include "Sprite.h"

struct BOUNDINGBOX
{
    int top, bottom, left, right;
};

//-----------------------------------------------------
// Camera Class
//-----------------------------------------------------
class Camera
{
public:
    Camera();   //Constructor
    virtual ~Camera();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
	void init();

    void move(Vector2di offset);
    void moveTo(Vector2di position);

    void setBoundingBox(int t, int b, int l, int r);
    void setPlayerDimensions(int w, int h);

    Vector2di getPosition(){return m_position;}
    BOUNDINGBOX getBoundingBox(){return m_boundingBox;}

private:

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    Vector2di m_position;
    BOUNDINGBOX m_boundingBox;
    int m_playerWidth, m_playerHeight;
};

#endif // Camera_H
