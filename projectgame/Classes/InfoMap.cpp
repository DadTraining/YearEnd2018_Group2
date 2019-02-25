#include "InfoMap.h"

int InfoMap::SHARK_PHASE_1ST = 0;
int InfoMap::SHARK_PHASE_2ND = 0;
int InfoMap::SHARK_PHASE_3RD = 0;
std::vector<Shark*> InfoMap::listShark;
std::vector<Bullet*> InfoMap::listBullet;


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

void InfoMap::AddShark(Shark * shark)
{
	listShark.push_back(shark);
}

std::vector<Shark*> InfoMap::getSharkList()
{
	return listShark;
}

void InfoMap::AddBullet(Bullet * bullet)
{
	listBullet.push_back(bullet);
}

std::vector<Bullet*> InfoMap::getBulletList()
{
	return listBullet;
}



