#ifndef BASEUNIT_H
#define BASEUNIT_H

#include "Vector2di.h"
#include "Image.h"
#include "Camera.h"
#include "HitRegion.h"
#include "SurfaceCache.h"

#define UNIT_ITEM (1)
#define UNIT_CONTAINER (2)
#define UNIT_ENEMY (3)

class BaseUnit
{
// FUNCTIONS
public:
    BaseUnit();
    virtual ~BaseUnit();

    void init(Vector2di position);

    virtual void renderUnit() = 0;
    virtual void renderExtra() = 0;
    virtual void update() = 0;
    virtual void setUnitType(int type) = 0;

    bool isGone(){return m_IsGone;}

    void setPosition(Vector2di position){m_Position = position;}
    Vector2di getPosition(){return m_Position;}

    void setSpeed(Vector2di speed){m_Speed = speed;}
    Vector2di getSpeed(){return m_Speed;}

    int getType(){return m_Type;}
    bool isActive();

    HitRegion* getHitRegion(){return &m_rgnCollision;}

// DATAMEMBERS
protected:
    Vector2di m_Position, m_Speed;
    int m_Type;
    bool m_IsGone;
    HitRegion m_rgnCollision;
};

#endif // BASEUNIT_H
