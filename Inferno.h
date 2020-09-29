#pragma once
#include "MouseSelection.h"

class Inferno : public Objective{
private:
	float fDmgLvLscale;
	float dmgpSec;
	int nRange;
	float fTimer;
	int nLevel;
	int nUpgradeCost;
	eItem eType;
	std::weak_ptr<Minion> oTarget;
	TouretInfo *inf;
	float fShotX;
	float fShotY;
public:
	Inferno();
	Inferno(float x, float y);
	void DrawSelf(olc::PixelGameEngine *pge) override;
	void CheckTarget(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) override;
	void Bullet(olc::PixelGameEngine *pge, float fElapsedTime) override;
	void Upgrade() override;

	void FindTarget(std::list<std::shared_ptr<Minion>> &listEnemy);
	bool HitTarget(std::shared_ptr<Minion> &Target, float fElapsedTime);

	float distance(float x1, float y1, float x2, float y2)
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}

	eItem GeteType() override
	{
		return eType;
	}
	TouretInfo* GetTouretInfo() override { return inf; }
};