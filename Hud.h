//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef HUD_H
#define HUD_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Sprite.h"
#include "Text.h"

//-----------------------------------------------------
// Hud Class
//-----------------------------------------------------
class Hud
{
public:
    Hud();			// Constructor
    virtual ~Hud();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
	void init();

    void render();
    void update();

    void setHealth(int value);
    void setLifes(int value){m_Lifes += value;}
    void setScore(int value){m_Score += value;}
    void setColour(int value){m_Colour += value;}

    int getHealth(){return m_Health;}
    int getColour(){return m_Colour;}

    float calcFPS();

private:

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

    int m_Health, m_Lifes, m_Score, m_Colour;

    Sprite m_bmpHud, m_bmpHud2, m_bmpHealth;
    Image m_bmpNumbers;
    Text m_FPS;
};

#endif // HUD_H
