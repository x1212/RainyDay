//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef INPUT_H
#define INPUT_H

#define BTN_JUMP (0)
#define BTN_ATTACK (1)
#define BTN_GRAB (2)
#define BTN_SHOOT (3)

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "SimpleJoy.h"

#include "Sprite.h"
#include "Text.h"

struct Button
{
    int id;
    char button;
};

class Input
{
public:
    Input(); // Constructor
    virtual ~Input(); //Destructor

	void init();

    void initInput(SimpleJoy* input){m_InputPtr = input;}
	bool isPressed(int button);
	bool resetButton(int button);

private:
    SimpleJoy* m_InputPtr;

	vector<Button> m_Buttons;
};

#endif // INPUT_H
