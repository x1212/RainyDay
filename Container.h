#ifndef CONTAINER_H
#define CONTAINER_H

#include "BaseUnit.h"
#include "SurfaceCache.h"

struct Piece
{
    Vector2di position, speed;
    bool visible;
    int type;
};

class Container : public BaseUnit
{
// FUNCTIONS
public:
    Container(string path);
    virtual ~Container();

    virtual void renderUnit();
    virtual void renderExtra();
    virtual void update();
    virtual void setUnitType(int type){m_ContainerType = type;}

    void destroy();
    void setContent(int itemType, int amount);
    int getContentType(){return m_ContentType;}
    int getContentAmount(){return m_ContentAmount;}

// DATAMEMBERS
private:
    int m_ContainerType, m_ContentType, m_ContentAmount;
    bool m_isDestroyed;
    Image m_bmpContainers;
    Piece m_arrPieces[6];
};

#endif // CONTAINER_H
