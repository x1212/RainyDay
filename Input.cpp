//-----------------------------------------------------
// Defines
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Input.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
Input::Input()
{

}
Input::~Input()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void Input::init()
{
    Button b;

    //A
    b.id = BTN_JUMP;
    b.button = 'x';

    m_Buttons.push_back(b);

    //B
    b.id = BTN_ATTACK;
    b.button = 'a';

    m_Buttons.push_back(b);

    //X
    b.id = BTN_GRAB;
    b.button = 'l';

    m_Buttons.push_back(b);

    //Y
    b.id = BTN_SHOOT;
    b.button = 'r';

    m_Buttons.push_back(b);
}
bool Input::isPressed(int button)
{
    if(m_Buttons[button].button == 'a') return m_InputPtr->isA();
    if(m_Buttons[button].button == 'b') return m_InputPtr->isB();
    if(m_Buttons[button].button == 'x') return m_InputPtr->isX();
    if(m_Buttons[button].button == 'y') return m_InputPtr->isY();
    if(m_Buttons[button].button == 'l') return m_InputPtr->isL();
    if(m_Buttons[button].button == 'r') return m_InputPtr->isR();
}
bool Input::resetButton(int button)
{
    if(m_Buttons[button].button == 'a') m_InputPtr->resetA();
    if(m_Buttons[button].button == 'b') m_InputPtr->resetB();
    if(m_Buttons[button].button == 'x') m_InputPtr->resetX();
    if(m_Buttons[button].button == 'y') m_InputPtr->resetY();
    if(m_Buttons[button].button == 'l') m_InputPtr->resetL();
    if(m_Buttons[button].button == 'r') m_InputPtr->resetR();
}
