//-----------------------------------------------------
// Defines
//-----------------------------------------------------

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Camera.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
Camera::Camera()
{

}
Camera::~Camera()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void Camera::init()
{
    m_position = Vector2di(180, 0);

    m_boundingBox.left = 0;
    m_boundingBox.top = 0;
    m_boundingBox.right = 800;
    m_boundingBox.bottom = 480;
}
void Camera::move(Vector2di offset)
{
    m_position.x += offset.x;
    if(m_position.x < 180) m_position.x = 180;

	m_position.y += offset.y;
	if(m_position.y < 0) m_position.y = 0;
}
void Camera::moveTo(Vector2di position)
{
    m_position.x = position.x;
	m_position.y = position.y;
}
void Camera::setBoundingBox(int t, int b, int l, int r)
{
    m_boundingBox.top = t;
    m_boundingBox.bottom = 480 - b - m_playerHeight;
    m_boundingBox.left = l;
    m_boundingBox.right = 800 - r - m_playerWidth;
}
 void Camera::setPlayerDimensions(int w, int h)
 {
    m_playerWidth = w;
    m_playerHeight = h;

    m_boundingBox.right -= m_playerWidth;
    m_boundingBox.bottom -= m_playerHeight;
 }
