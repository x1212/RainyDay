#ifndef TextBox_H
#define TextBox_H

#include "Image.h"
#include "Text.h"
#include "SimpleJoy.h"
#include "Sound.h"

#include <iostream>
#include <fstream>

#define TEXTBOX (TextBox::getSingleton())

struct TextBlock
{
    string line[3];

    int nextText;
};

class TextBox
{
private:
	TextBox();
	static TextBox* m_TextBoxPtr;

public:
    virtual ~TextBox();

    static TextBox* getSingleton();

    void init();
    void render();
    void userInput();
    void update();
    void setInput(SimpleJoy* j){input = j;}
    void setPosition(Vector2di position);

    void displayText(string name);
    void setLetterDelay(int delay){m_Delay = delay;}

private:

    string m_TextDatabase;
    string m_TextBuffer[3];
    TextBlock *m_TextToWrite;
    int m_CurrentLetter, m_CurrentLine, m_Delay, m_Counter;
    bool m_IsWriting, m_IsWaiting;
    Text m_renderText[3];

    SimpleJoy *input;
    Sound m_sndVoice[4];

};

#endif // TextBox_H
