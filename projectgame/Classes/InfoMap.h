#pragma once
#include "cocos2d.h"


class InfoMap 
{
private:
	static int SHARK_PHASE_1ST;
	static int SHARK_PHASE_2ND;
	static int SHARK_PHASE_3RD;
public:
	static void setSharPhases(int p1, int p2, int p3) {
		SHARK_PHASE_1ST = p1;
		SHARK_PHASE_2ND = p2;
		SHARK_PHASE_3RD = p3;
	}

	static int getPhase1();
	static int getPhase2();
	static int getPhase3();
};

