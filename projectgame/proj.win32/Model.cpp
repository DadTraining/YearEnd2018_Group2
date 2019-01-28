#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::SetVisible(bool vis)
{
	mSprite->setVisible(vis);
	mVisible = vis;
}

bool Model::IsVisible()
{
	return mVisible;
}
