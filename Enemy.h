#ifndef ENEMY_H
#define ENEMY_H

#include "BaseUnit.h"
#include <math.h>
#include "AnimatedSprite.h"

#define DIR_LEFT (-1)
#define DIR_RIGHT (1)

struct Boundary
{
    int left, right, height;
};

class Enemy : public BaseUnit
{
// FUNCTIONS
public:
    Enemy();
    virtual ~Enemy();

    virtual void renderUnit();
    virtual void renderExtra();
    virtual void update();
    virtual void setUnitType(int type){m_EnemyType = type;}
    virtual void initImages();
    virtual void initBoundaries(int left, int right);

    virtual int getUnitType(){return m_EnemyType;}

    void kill(int direction);
    void turnToStone(Vector2di& pos, int& type);

private:
    void move(Vector2di offset);

// DATAMEMBERS

    int m_Counter, m_EnemyType;
    bool m_IsIdling, m_IsDying , m_IsDead, m_IsChasing, m_IsStoned;
    AnimatedSprite *m_bmpCurrentPtr, m_bmpMovingLeft, m_bmpMovingRight, m_bmpIdle, m_bmpDead, m_bmpStoned, m_bmpPoof;
    Boundary m_Boundary;
};

#endif // ENEMY_H
