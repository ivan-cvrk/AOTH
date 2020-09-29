#pragma once
#include "Objective.h"

class Minion {
protected:
	float fX;
	float fY;
	bool bSwapSide;
	bool bSlowed;

public:
	olc::Sprite *spr;
	
	Minion() : fX(0), fY(0), bSwapSide(false), bSlowed(false)
	{
	}

	virtual void DrawSelf(olc::PixelGameEngine *pge) = 0;
	virtual float GetVel() const noexcept = 0; 
	virtual void TakeDamage(float fDamage) = 0;
	virtual float GetHealth() const noexcept = 0;
	virtual int GetWorth() const noexcept = 0;
	virtual void SetSlow(float fSlow) = 0;
	// Getters and Settlers
	inline float GetX() const noexcept { return fX; }
	inline float GetY() const noexcept { return fY; }
	inline void SetX(float x) { fX = x; }
	inline void SetY(float y) { fY = y; }

	inline void SetSpr(olc::Sprite *p)
	{
		spr = p;
	}

	void NewPosUp(float fVelocity, float fElapsedTime)
	{
		fY -= fVelocity * fElapsedTime;
	}
	void NewPosLeft(float fVelocity, float fElapsedTime)
	{
		fX -= fVelocity * fElapsedTime;
		bSwapSide = false;
	}
	void NewPosDown(float fVelocity, float fElapsedTime)
	{
		fY += fVelocity * fElapsedTime;
	}
	void NewPosRight(float fVelocity, float fElapsedTime)
	{
		fX += fVelocity * fElapsedTime;
		bSwapSide = true;
	}
	bool Slowed()
	{
		return (bSlowed)? true : false;
	}
	~Minion()
	{
		delete spr;
	}
};