#include "InfoMap.h"

int InfoMap::SHARK_PHASE_1ST = 0;
int InfoMap::SHARK_PHASE_2ND = 0;
int InfoMap::SHARK_PHASE_3RD = 0;
int InfoMap::MAP_LEVEL = 0;
int InfoMap::SCORE = 0;


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

void InfoMap::setScore(int score)
{
	SCORE = score;
}




