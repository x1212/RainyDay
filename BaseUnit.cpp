#include "BaseUnit.h"
#include "GameManager.h"

BaseUnit::BaseUnit()
{

}
BaseUnit::~BaseUnit()
{

}
void BaseUnit::init(Vector2di position)
{
    m_Position = position;
    m_IsGone = false;
}
bool BaseUnit::isActive()
{
    if(m_Position.x - CAMERA->getPosition().x > -40 &&  m_Position.x - CAMERA->getPosition().x < 800 &&
       m_Position.y - CAMERA->getPosition().y > -50 && m_Position.y - CAMERA->getPosition().y < 490) return true;
    else return false;
}
