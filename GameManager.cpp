//---------------------------
// Includes
//---------------------------
#include "GameManager.h"

//---------------------------
// Static
//---------------------------
GameManager* GameManager::m_GameManagerPtr = NULL;

//---------------------------
// Constructor & Destructor
//---------------------------
GameManager::GameManager()
{

}
GameManager::~GameManager()
{
    for(int i = m_CurrentLevel.units.size()-1; i >= 0; --i)
        delete m_CurrentLevel.units[i];
}
GameManager* GameManager::getSingleton()
{
    if(m_GameManagerPtr == 0)
    {
        m_GameManagerPtr = new GameManager();
        m_GameManagerPtr->init();
    }
	return m_GameManagerPtr;
}
void GameManager::init()
{
    m_SoundSystem = new SoundSystem();
    m_SoundSystem->init();

    m_EffectSystem = new EffectSystem();
    m_EffectSystem->init();

    m_Input = new Input();
    m_Input->init();

    m_Camera = new Camera();
    m_Camera->init();

    m_Hud = new Hud();
    m_Hud->init();

    m_Hero = new Hero();
    m_Hero->init();

    m_IsChangingLocation = false;

    m_Position = Vector2di(0, 0);

    loadLevelData(1);
    initPartData();

    m_CurrentLevel.layer1.setTransparentColour(MAGENTA);

    m_CapturedColour = 0;
}
void GameManager::render()
{
    m_CurrentLevel.layer3.render();
    m_CurrentLevel.layer2.render();
    m_CurrentLevel.layer1.render();

    for (int i = m_CurrentLevel.units.size()-1; i >= 0; --i)
    {
        if(m_CurrentLevel.units[i])
            m_CurrentLevel.units[i]->renderUnit();
    }
    for (int i = m_CurrentLevel.units.size()-1; i >= 0; --i)
    {
        if(m_CurrentLevel.units[i])
            m_CurrentLevel.units[i]->renderExtra();
    }

    m_Hero->render();

    m_CurrentLevel.layer0.render();

    m_EffectSystem->renderRain();

    m_Hud->render();

    m_EffectSystem->renderFade();
}
void GameManager::update()
{
    m_Position = Vector2di(0 - CAMERA->getPosition().x, 0 - CAMERA->getPosition().y);

    m_CurrentLevel.layer1.setPosition(m_Position);
    m_CurrentLevel.layer0.setPosition(Vector2di(m_Position.x * 1.3 + 180, m_Position.y * 1.3 + 180));
    m_CurrentLevel.layer2.setPosition(Vector2di(m_Position.x * 0.7 + 180, m_Position.y * 0.7 - 160));

    if(m_IsChangingLocation && EFFECTSYSTEM->getFadeAlpha() == 255)
    {
        initPartData();

        m_IsChangingLocation = false;
        EFFECTSYSTEM->fadeIn(20);
    }

    for (int i = m_CurrentLevel.units.size()-1; i >= 0; --i)
    {
        if(m_CurrentLevel.units[i])
        {
            if(m_CurrentLevel.units[i]->isGone())
            {
                delete m_CurrentLevel.units[i];
                m_CurrentLevel.units[i] = 0;
            }
            else m_CurrentLevel.units[i]->update();
        }
    }
}
void GameManager::loadLevelData(int level)
{
    m_CurrentLevel.name = "";
    m_CurrentLevel.currentPart = 1;

    ifstream file;
    string buffer;

    file.open("levels/Level1.lvl");

    //Put the complete Database in memory
    while(file.good())
    {
      getline (file, buffer);
      m_LevelData += buffer;
    }

    size_t pos = m_LevelData.find("Name");
    pos += 6;

    while(m_LevelData.at(pos) != '"')
    {
        m_CurrentLevel.name += m_LevelData.at(pos);
        pos += 1;
    }
}
void GameManager::initPartData()
{
    //m_CurrentLevel.enemies[0].setPosition(Vector2di(920, 950));
    //m_CurrentLevel.enemies[1].setPosition(Vector2di(1575, 865));
    //m_CurrentLevel.enemies[2].setPosition(Vector2di(644, 326));

    string ts;
    stringstream ss;

    ss << m_CurrentLevel.currentPart;
    ss >> ts;

    size_t pos = m_LevelData.find("PART" + ts);

    //----------------------------------------------------
    //  INIT DIMENSIONS
    //----------------------------------------------------

    string number;

    pos = m_LevelData.find("dimensions", pos);
    pos += 12;

    while(m_LevelData.at(pos) != ',')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.dimensions.x = atoi(number.c_str());

    number = "";
    pos += 1;

    while(m_LevelData.at(pos) != ')')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.dimensions.y = atoi(number.c_str());

    //----------------------------------------------------
    //  INIT NEXT & PREVIOUS
    //----------------------------------------------------

    //Next Part
    number = "";

    pos = m_LevelData.find("next", pos);
    pos += 6;

    while(m_LevelData.at(pos) != ')')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.nextPart = atoi(number.c_str());

    //Previous Part
    number = "";

    pos = m_LevelData.find("previous", pos);
    pos += 10;

    while(m_LevelData.at(pos) != ')')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.prevPart = atoi(number.c_str());

    //Next Hero Position
    number = "";

    pos = m_LevelData.find("nextHeroPos", pos);
    pos += 13;

    while(m_LevelData.at(pos) != ',')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.nextHeroPos.x = atoi(number.c_str());

    number = "";
    pos += 1;

    while(m_LevelData.at(pos) != ')')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.nextHeroPos.y = atoi(number.c_str());

    //Previous Hero Position
    number = "";

    pos = m_LevelData.find("prevHeroPos", pos);
    pos += 13;

    while(m_LevelData.at(pos) != ',')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.prevHeroPos.x = atoi(number.c_str());

    number = "";
    pos += 1;

    while(m_LevelData.at(pos) != ')')
    {
        number += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.prevHeroPos.y = atoi(number.c_str());


    //----------------------------------------------------
    //  INIT IMAGES
    //----------------------------------------------------

    //Layer0
    string path;

    pos = m_LevelData.find("layer0", pos);
    pos += 8;

    while(m_LevelData.at(pos) != '"')
    {
        path += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.layer0.loadSprite(path);
    m_CurrentLevel.layer0.setTransparentColour(MAGENTA);

    //Layer1
    path = "";

    pos = m_LevelData.find("layer1", pos);
    pos += 8;

    while(m_LevelData.at(pos) != '"')
    {
        path += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.layer1.loadSprite(path);
    m_CurrentLevel.layer1.setPosition(m_Position.x, 220);

    //Layer2
    path = "";

    pos = m_LevelData.find("layer2", pos);
    pos += 8;

    while(m_LevelData.at(pos) != '"')
    {
        path += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.layer2.loadSprite(path);
    m_CurrentLevel.layer2.setTransparentColour(MAGENTA);

    //Layer3
    path = "";

    pos = m_LevelData.find("layer3", pos);
    pos += 8;

    while(m_LevelData.at(pos) != '"')
    {
        path += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.layer3.loadSprite(path);
    m_CurrentLevel.layer3.setTransparentColour(MAGENTA);

    //Mask
    path = "";

    pos = m_LevelData.find("mask", pos);
    pos += 6;

    while(m_LevelData.at(pos) != '"')
    {
        path += m_LevelData.at(pos);
        pos += 1;
    }
    m_CurrentLevel.mask = new CollisionMap();
    m_CurrentLevel.mask->loadImage(path);

    //----------------------------------------------------
    //  INIT UNITS - CONTAINERS
    //----------------------------------------------------

    pos = m_LevelData.find("containers", pos);
    pos += 12;

    while(true) //I know this seems dangerous but don't worry, I know what I'm doing :)
    {
        string type;
        string unitX;
        string unitY;
        string contentType;
        string contentAmount;
        BaseUnit* container = new Container("images/containers.png");

        //Get Type
        type += m_LevelData.at(pos);

        pos += 2;

        //Get Unit Xpos
        while(m_LevelData.at(pos) != ',')
        {
            unitX += m_LevelData.at(pos);
            pos += 1;
        }

        pos += 1;

        //Get Unit Ypos
        while(m_LevelData.at(pos) != ',' && m_LevelData.at(pos) != ')')
        {
            unitY += m_LevelData.at(pos);
            pos += 1;
        }

        if(m_LevelData.at(pos) == ',')
        {
            pos += 1;

            //Get Container Content Type
            while(m_LevelData.at(pos) != ',')
            {
                contentType += m_LevelData.at(pos);
                pos += 1;
            }

            pos += 1;

            //Get Container Content Amount
            while(m_LevelData.at(pos) != ')')
            {
                contentAmount += m_LevelData.at(pos);
                pos += 1;
            }

            ((Container*)container)->setContent(atoi(contentType.c_str()), atoi(contentAmount.c_str()));
        }
        else ((Container*)container)->setContent(0, 0);

        container->init(Vector2di(atoi(unitX.c_str()), atoi(unitY.c_str())));
        container->setUnitType(atoi(type.c_str()));
        m_CurrentLevel.units.push_back(container);

        pos += 1;
        if(m_LevelData.at(pos) != '(') break;
        else pos += 1;
    }

    //----------------------------------------------------
    //  INIT UNITS - MONSTERS
    //----------------------------------------------------

    pos = m_LevelData.find("enemies", pos);
    pos += 9;

    while(true) //I know this seems dangerous but don't worry, I know what I'm doing :)
    {
        string type;
        string unitX;
        string unitY;
        string bndLeft;
        string bndRight;
        BaseUnit* enemy = new Enemy();

        //Get Type
        type += m_LevelData.at(pos);

        pos += 2;

        //Get Unit Xpos
        while(m_LevelData.at(pos) != ',')
        {
            unitX += m_LevelData.at(pos);
            pos += 1;
        }

        pos += 1;

        //Get Unit Ypos
        while(m_LevelData.at(pos) != ',' && m_LevelData.at(pos) != ')')
        {
            unitY += m_LevelData.at(pos);
            pos += 1;
        }

        if(m_LevelData.at(pos) == ',')
        {
            pos += 1;

            //Get Enemy left boundary
            while(m_LevelData.at(pos) != ',')
            {
                bndLeft += m_LevelData.at(pos);
                pos += 1;
            }

            pos += 1;

            //Get Enemy right boundary
            while(m_LevelData.at(pos) != ')')
            {
                bndRight += m_LevelData.at(pos);
                pos += 1;
            }
        }


        enemy->init(Vector2di(atoi(unitX.c_str()), atoi(unitY.c_str())));
        enemy->setUnitType(atoi(type.c_str()));
        ((Enemy*)enemy)->initImages();
        ((Enemy*)enemy)->initBoundaries(atoi(bndLeft.c_str()), atoi(bndRight.c_str()));
        m_CurrentLevel.units.push_back(enemy);

        pos += 1;
        if(m_LevelData.at(pos) != '(') break;
        else pos += 1;
    }
}
void GameManager::changeLocation(int part)
{
    if(part == NEXT) m_CurrentLevel.currentPart = m_CurrentLevel.nextPart;
    else if(part == PREVIOUS) m_CurrentLevel.currentPart = m_CurrentLevel.prevPart;
    else m_CurrentLevel.currentPart = part;

    m_IsChangingLocation = true;
    EFFECTSYSTEM->fadeOut(20);
}
Vector2di GameManager::getNewHeroPosition(int direction)
{
    if(direction == NEXT) return m_CurrentLevel.nextHeroPos;
    else if(direction == PREVIOUS) return m_CurrentLevel.prevHeroPos;
}
bool GameManager::checkUnitCollision(const HitRegion &region, string name, int direction)
{
    for(int i = m_CurrentLevel.units.size()-1; i >= 0; --i)
    {
        if(m_CurrentLevel.units[i])
        {
            //CONTAINER
            if(m_CurrentLevel.units[i]->getType() == UNIT_CONTAINER)
            {
                if(m_CurrentLevel.units[i]->getHitRegion()->hitTest(&region))
                {
                    if(name == "HERO") return true; // If the hero touches the container
                    else if(name == "UMBRELLA") // If you hit the container with the umbrella
                    {
                        //Spawn Items
                        if(!((Container*)m_CurrentLevel.units[i])->getContentAmount() == 0)
                        {
                            int type = ((Container*)m_CurrentLevel.units[i])->getContentType();
                            int amount = ((Container*)m_CurrentLevel.units[i])->getContentAmount();
                            Vector2di pos = Vector2di(m_CurrentLevel.units[i]->getPosition().x, m_CurrentLevel.units[i]->getPosition().y - 16);

                            spawnItem(type, amount, pos);
                        }

                        //Destroy Container
                        ((Container*)m_CurrentLevel.units[i])->destroy();
                    }
                }
            }
            //ITEM
            else if(m_CurrentLevel.units[i]->getType() == UNIT_ITEM)
            {
                if(m_CurrentLevel.units[i]->getHitRegion()->hitTest(&region))
                {
                    if(name == "UMBRELLA" || name == "BODY") // If the hero or the umbrella touches the item
                    {
                        ((Item*)m_CurrentLevel.units[i])->collect();
                    }
                }
            }
            //ENEMY
            else if(m_CurrentLevel.units[i]->getType() == UNIT_ENEMY)
            {
                if(m_CurrentLevel.units[i]->getHitRegion()->hitTest(&region))
                {
                    if(name == "UMBRELLA") // If you hit the enemy with the umbrella
                    {
                        ((Enemy*)m_CurrentLevel.units[i])->kill(direction);
                    }
                    else if(name == "GRABBEAM") // If the enemy is hit by the grabbeam
                    {
                        int type;
                        Vector2di pos;
                        m_CapturedColour = ((Enemy*)m_CurrentLevel.units[i])->getUnitType();
                        ((Enemy*)m_CurrentLevel.units[i])->turnToStone(pos, type);
                        cout << type << " | " << pos << endl;
                        BaseUnit* frozenEnemy = new Container("images/Enemies/Enemies_Frozen.png");
                        frozenEnemy->init(pos);
                        frozenEnemy->setUnitType(type);
                        frozenEnemy->getHitRegion()->init(0, 0, 100, 100);
                        m_CurrentLevel.units.push_back(frozenEnemy);
                    }
                    else if(name == "BODY") // If the hero touches the enemy
                    {
                        return true;
                    }
                    else return false;
                }
            }
        }
    }

    return false;
}
void GameManager::spawnItem(int type, int amount, Vector2di position)
{
    //Spawn Items
    for(int i = 0; i < amount; i++)
    {
        BaseUnit* item = new Item();
        item->init(position);
        item->setUnitType(type);

        //Set random speed en direction
        switch (i)
        {
            case 0: item->setSpeed(Vector2di(2, -12)); break;
            case 1: item->setSpeed(Vector2di(-2, -11)); break;
            case 2: item->setSpeed(Vector2di(0, -13)); break;
            default: item->setSpeed(Vector2di((rand() % 9) - 4, ((rand() % 3) + 11) * -1)); break;
        }

        m_CurrentLevel.units.push_back(item);
    }
}
