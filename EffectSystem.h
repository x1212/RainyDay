//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef EFFECTSYSTEM_H
#define EFFECTSYSTEM_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Rectangle.h"
#include "Colour.h"
#include "AnimatedSprite.h"
#include "Line.h"
#include "Camera.h"
#include "HitRegion.h"

//-----------------------------------------------------
// EffectSystem Class
//-----------------------------------------------------
struct RainDrop
{
    Vector2df position;
    Vector2df size;
    Vector2df sizeNormalised;
};

class EffectSystem
{
public:
    EffectSystem();			// Constructor
    virtual ~EffectSystem();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
	void init();

    void render();
    void renderRain();
    void renderFade();

    void update();

    void fadeIn(int speed);
    void fadeOut(int speed, Colour colour = Colour(BLACK));
    int getFadeAlpha(){return m_FadeAlpha;}
    int getFadeDirection(){return m_FadeDir;}

    void setRain(bool state){m_isRaining = state;}
    bool isRaining(){return m_isRaining;}

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

	//FADE
	Rectangle m_Fade;
    int m_FadeDir, m_FadeAlpha, m_FadeSpeed;

    //RAIN
    bool m_isRaining;
    static const int RAINMAX = 128;
	RainDrop m_RainArr[RAINMAX];
};

#endif // EFFECTSYSTEM_H
