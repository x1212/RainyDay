#ifndef MYGAME_H
#define MYGAME_H
#include "Engine.h"

class MyGame : public Engine
{
	public:
		MyGame();

		//virtual PENJIN_ERRORS argHandler(int argc, char** argv);
		virtual PENJIN_ERRORS init();
		virtual void stateManagement();

    private:

};

#endif	//MYGAME_H
