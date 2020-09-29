#pragma once
#include "MouseSelection.h"

typedef struct Bullet
{
	//BULLET
	float fTargetX;
	float fTargetY;
	float fBulletX;
	float fBulletY;
	float fBulletSpeed;
	std::weak_ptr<Minion> bullTarget;
}BULLET;

class Tower : public Objective
{
private:
	int nDamage;
	float fAttackRate;
	int nRange;
	float fTimer;
	int nLevel;
	int nUpgradeCost;
	TouretInfo *inf;
	std::list<std::unique_ptr<BULLET>> listBullet;
	std::weak_ptr<Minion> oTarget;
	eItem eType = eItem::TOWER;

public:
	Tower();
	Tower(float x, float y);
	~Tower();
	//Override
	void DrawSelf(olc::PixelGameEngine *pge) override;
	void CheckTarget(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) override;
	void Bullet(olc::PixelGameEngine *pge, float fElapsedTime) override;
	void Upgrade() override;
	//Not Override
	bool HitTarget(std::shared_ptr<Minion> &Target, float fElapsedTime);
	void FindTarget(std::list<std::shared_ptr<Minion>> &listEnemy);
	
	eItem GeteType() override 
	{
		return eType;
	}

	inline TouretInfo* GetTouretInfo() override 
	{
		return inf;
	}

	float distance(float x1, float y1, float x2, float y2) 
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
};