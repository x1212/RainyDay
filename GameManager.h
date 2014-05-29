#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define GAMEMANAGER (GameManager::getSingleton())

#define SOUNDSYSTEM (GAMEMANAGER->getSoundSystem())
#define EFFECTSYSTEM (GAMEMANAGER->getEffectSystem())
#define INPUT (GAMEMANAGER->getInput())
#define CAMERA (GAMEMANAGER->getCamera())
#define HUD (GAMEMANAGER->getHud())
#define HERO (GAMEMANAGER->getHero())

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Enemy.h"
#include "CollisionMap.h"
#include "Sprite.h"
#include "HitRegion.h"
#include "Vector2di.h"
#include "Item.h"
#include "Container.h"
#include "BaseUnit.h"

#include "SoundSystem.h"
#include "EffectSystem.h"
#include "Input.h"
#include "Camera.h"
#include "Hud.h"
#include "Hero.h"

#include <iostream>
#include <fstream>

//-----------------------------------------------------
// Direction Defines
//-----------------------------------------------------
#define NEXT (-1000)
#define PREVIOUS (-1001)

//-----------------------------------------------------
// GameManager Class
//-----------------------------------------------------
struct Level
{
    string name;
    int currentPart, nextPart, prevPart;
    Vector2di dimensions, nextHeroPos, prevHeroPos;
    Sprite layer0, layer1, layer2, layer3;
    CollisionMap* mask;

    vector<BaseUnit*> units;
};

class GameManager
{
private:
	GameManager();			// Constructor
	static GameManager* m_GameManagerPtr;

public:
	virtual ~GameManager();		// Destructor

	//-------------------------------------------------
	// Eigen methoden
	//-------------------------------------------------

	static GameManager* getSingleton();

    void init();

    void loadImages();
	void render();
	void update();

	CollisionMap* getHitRegion(){return m_CurrentLevel.mask;}

    int getPartWidth(){return m_CurrentLevel.dimensions.x;}
    int getPartHeight(){return m_CurrentLevel.dimensions.y;}

    void setPosition(int x, int y){m_Position = Vector2di(x, y);}
    Vector2di getPosition(){return m_Position;}

    void changeLocation(int part);
    bool IsChangingLocation(){return m_IsChangingLocation;}

    Vector2di getNewHeroPosition(int direction);

    bool checkUnitCollision(const HitRegion &region, string name = "", int direction = 0);
    void spawnItem(int type, int amount, Vector2di position);

    void initHeroPosition(Vector2di &position){m_HeroPositionPtr = &position;}
    Vector2di* getHeroPosition(){return m_HeroPositionPtr;}

    int getCapturedColour(){return m_CapturedColour;}
    void setCapturedColour(int colour){m_CapturedColour = colour;}

    SoundSystem* getSoundSystem(){return m_SoundSystem;}
    EffectSystem* getEffectSystem(){return m_EffectSystem;}
    Input* getInput(){return m_Input;}
    Camera* getCamera(){return m_Camera;}
    Hud* getHud(){return m_Hud;}
    Hero* getHero(){return m_Hero;}

private:

    void loadLevelData(int level);
    void initPartData();
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

    int m_PartEnteringDirection, m_CapturedColour;
    bool m_IsChangingLocation;

	Vector2di m_Position;
	Vector2di* m_HeroPositionPtr;

	Level m_CurrentLevel;
	string m_LevelData;

	SoundSystem* m_SoundSystem;
	EffectSystem* m_EffectSystem;
	Input* m_Input;
	Camera* m_Camera;
	Hud* m_Hud;
	Hero* m_Hero;
};

#endif	//  GAMEMANAGER_H
