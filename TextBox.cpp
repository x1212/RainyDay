#include "TextBox.h"

TextBox* TextBox::m_TextBoxPtr = NULL;

TextBox::TextBox()
{

}
TextBox::~TextBox()
{

}
TextBox* TextBox::getSingleton()
{
	if(m_TextBoxPtr == NULL) m_TextBoxPtr = new TextBox();
	return m_TextBoxPtr;
}
void TextBox::init()
{
    m_sndVoice[0].loadSound("sounds/Moth1.ogg");
    m_sndVoice[1].loadSound("sounds/Moth2.ogg");
    m_sndVoice[2].loadSound("sounds/Moth3.ogg");
    m_sndVoice[3].loadSound("sounds/Moth4.ogg");

    ifstream file;
    string buffer;

    m_TextDatabase = "";

    file.open("text/Text_Database.txt");

    //Put the complete Text Database in memory
    while(file.good())
    {
      getline (file, buffer);
      m_TextDatabase += buffer;
    }

    //cout << m_TextDatabase << endl;

    m_CurrentLetter = 0;
    m_CurrentLine = 0;
    m_Delay = 0;
    m_Counter = 0;
    m_IsWriting = false;
    m_IsWaiting = false;

    m_TextBuffer[0] = "";
    m_TextBuffer[1] = "";
    m_TextBuffer[2] = "";

    m_TextToWrite = new TextBlock();

    m_TextToWrite->line[0] = "";
    m_TextToWrite->line[1] = "";
    m_TextToWrite->line[2] = "";

    m_renderText[0].setPosition(10, 8);
    m_renderText[0].loadFont("Fonts/FrancoisOne.ttf");
    m_renderText[0].setFontSize(20);

    m_renderText[1].setPosition(10, 36);
    m_renderText[1].loadFont("Fonts/FrancoisOne.ttf");
    m_renderText[1].setFontSize(20);

    m_renderText[2].setPosition(10, 64);
    m_renderText[2].loadFont("Fonts/FrancoisOne.ttf");
    m_renderText[2].setFontSize(20);
}
void TextBox::render()
{
    if (!m_IsWriting  && !m_IsWaiting) return;

    m_renderText[0].print(m_TextBuffer[0]);
    m_renderText[1].print(m_TextBuffer[1]);
    m_renderText[2].print(m_TextBuffer[2]);
}
void TextBox::userInput()
{

}
void TextBox::update()
{
    if (!m_IsWriting) return;
    if(m_Counter != m_Delay)
    {
        m_Counter += 1;
        return;
    }
    else m_Counter = 0;

    char t = m_TextToWrite->line[m_CurrentLine][m_CurrentLetter];

    if(isspace(t)) m_TextBuffer[m_CurrentLine] += " ";
    else
    {
        string tc;
        stringstream ss;

        ss << t;
        ss >> tc;

        m_TextBuffer[m_CurrentLine] += tc;

        m_sndVoice[rand() % 4].play();
    }

    if(m_CurrentLetter == m_TextToWrite->line[m_CurrentLine].size() - 1)
    {
        if(m_CurrentLine == 2 || m_TextToWrite->line[m_CurrentLine + 1] == "")
        {
            m_CurrentLine = 0;
            m_CurrentLetter = 0;
            m_IsWriting = false;
            m_IsWaiting = true;
        }
        else
        {
            m_CurrentLine += 1;
            m_CurrentLetter = 0;
        }
    }
    else m_CurrentLetter += 1;
}
void TextBox::displayText(string name)
{
    m_TextBuffer[0] = "";
    m_TextBuffer[1] = "";
    m_TextBuffer[2] = "";

    m_TextToWrite->line[0] = "";
    m_TextToWrite->line[1] = "";
    m_TextToWrite->line[2] = "";

    m_CurrentLetter = 0;
    m_IsWriting = true;

    size_t pos = m_TextDatabase.find(name);
    pos += name.size() + 2;

    while(pos != m_TextDatabase.size())
    {
        char t = m_TextDatabase[pos];

        if(t == '"')
        {
            pos += 2;
            if(m_TextDatabase[pos] == '"' || pos > m_TextDatabase.size() - 1)
            {
                m_CurrentLine = 0;
                m_CurrentLetter = 0;
                return;
            }
            else
            {
                m_CurrentLine += 1;
                char t = m_TextDatabase[pos];
                pos -= 1;
            }
        }
        else if(isspace(t)) m_TextToWrite->line[m_CurrentLine] += " ";
        else
        {
            string tc;
            stringstream ss;

            ss << t;
            ss >> tc;

            m_TextToWrite->line[m_CurrentLine] += tc;
        }

        pos += 1;
    }
}
void TextBox::setPosition(Vector2di position)
{
    m_renderText[0].setPosition(position.x + 8, position.y + 8);
    m_renderText[1].setPosition(position.x + 8, position.y + 36);
    m_renderText[2].setPosition(position.x + 8, position.y + 64);
}
