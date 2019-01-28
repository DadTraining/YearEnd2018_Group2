#pragma once
class Model
{
private:

public:
	Model();
 	virtual ~Model();

	virtual void Update() = 0;
	virtual void Init() = 0;
};

