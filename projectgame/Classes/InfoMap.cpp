#include "InfoMap.h"

int InfoMap::SHARK_PHASE_1ST = 0;
int InfoMap::SHARK_PHASE_2ND = 0;
int InfoMap::SHARK_PHASE_3RD = 0;
int InfoMap::SHARK_SKIN = 0;
int InfoMap::MAP_LEVEL = 0;
int InfoMap::SCORE = 0;
int InfoMap::SCORE_3STAR=0;
int InfoMap::SCORE_2STAR=0;


void InfoMap::setSharPhases(int p1, int p2, int p3, int skin, int star3, int star2)
{
	SHARK_PHASE_1ST = p1;
	SHARK_PHASE_2ND = p2;
	SHARK_PHASE_3RD = p3;
	SHARK_SKIN = skin;
	SCORE_3STAR = star3;
	SCORE_2STAR = star2;

}

int InfoMap::getPhase1()
{
	return SHARK_PHASE_1ST;
}

int InfoMap::getPhase2()
{
	return SHARK_PHASE_2ND;
}

int InfoMap::getPhase3()
{
	return SHARK_PHASE_3RD;
}

int InfoMap::getSharkSkin()
{
	return SHARK_SKIN;
}

void InfoMap::setScore(int score)
{
	SCORE = score;
}




