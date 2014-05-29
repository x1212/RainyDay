#ifndef ITEM_H
#define ITEM_H

#include "BaseUnit.h"
#include "Image.h"
#include "AnimatedSprite.h"
#include "Vector2di.h"
#include "HitRegion.h"

class Item : public BaseUnit
{
public:
    Item();
    virtual ~Item();

    virtual void renderUnit();
    virtual void renderExtra(){}
    virtual void update();
    virtual void collect();
    virtual void setUnitType(int type){m_ItemType = type;}

private:

    int m_ItemType, m_HitPosition, m_BounceSpeed;
    bool m_IsStatic;
    Image m_SpriteSheet;

    AnimatedSprite m_bmpRaindrop;
    AnimatedSprite m_bmpBling;
};

#endif // ITEM_H
