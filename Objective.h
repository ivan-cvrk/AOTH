#pragma once
#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"
#include "Minion.h"

enum class eItem;

class Minion;
typedef struct TouretInfo
{
	int nLevel;
	float fDamage;
	float fAttackRate;
	int nRange;
	int nUpgradeCost;
}TouretInfo;

class Objective{
protected: 
	// Objectives coordinates and picture
	float fX;
	float fY;

public:	olc::Sprite *spr;
		static bool bShowRange;
	
public:
	Objective() : fX(0), fY(0)
	{
	}
	virtual void DrawSelf(olc::PixelGameEngine *pge) = 0;
	virtual void CheckTarget(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) = 0;
	virtual void Bullet(olc::PixelGameEngine *pge, float fElapsedTime) = 0;
	virtual eItem GeteType() = 0;
	virtual TouretInfo* GetTouretInfo() = 0;
	virtual void Upgrade() = 0;

	inline void SetSpr(olc::Sprite *p) // Sets sprite, called by subclass
	{
		spr = p;
	}
	// Getters and settlers
	inline float GetX() const noexcept { return fX; } 
	inline float GetY() const noexcept { return fY; }
	inline void SetX(float x) { fX = x; }
	inline void SetY(float y) { fY = y; }
	~Objective() {
		delete spr;
	}
};