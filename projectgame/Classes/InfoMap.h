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
	static int MAP_LEVEL;
	static int SCORE;
public:
	static void setSharPhases(int p1, int p2, int p3) {
		SHARK_PHASE_1ST = p1;
		SHARK_PHASE_2ND = p2;
		SHARK_PHASE_3RD = p3;
	}

	static int getPhase1();
	static int getPhase2();
	static int getPhase3();
	static int getMapLevel() {
		return MAP_LEVEL;
	}
	static void setMapLevel(int map) {
		MAP_LEVEL = map + 1;
	}

	static void setScore(int score);
	static int getScore() {
		return SCORE;
	}
};

