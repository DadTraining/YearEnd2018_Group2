#pragma once
#include "cocos2d.h"
#include "Shark.h"
#include "Bullet.h"
#include <vector>


class InfoMap 
{
private:
	static int SHARK_PHASE_1ST;
	static int SHARK_PHASE_2ND;
	static int SHARK_PHASE_3RD;
	static std::vector<Shark*> listShark;
	static std::vector<Bullet*> listBullet;


public:
	static void setSharPhases(int p1, int p2, int p3) {
		SHARK_PHASE_1ST = p1;
		SHARK_PHASE_2ND = p2;
		SHARK_PHASE_3RD = p3;
	}

	static int getPhase1();
	static int getPhase2();
	static int getPhase3();

	static void AddShark(Shark* shark);
	static std::vector<Shark*> getSharkList();
	
	static void AddBullet(Bullet* bullet);
	static std::vector<Bullet*> getBulletList();


};

