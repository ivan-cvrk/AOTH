#pragma once
#include "Minion.h"

class Spells {
protected:
	int nPosX;
	int nPosY;
	int nRadius;
protected:
	float Distance(float x1, float y1, float x2, float y2) {
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
public:
	virtual void DrawSelf(olc::PixelGameEngine* pge) = 0;
	virtual void DrawSelfNotCast(olc::PixelGameEngine* pge) = 0;
	virtual bool CheckSpell(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) = 0;
	inline void SetX(int X)
	{
		nPosX = X;
	}
	inline void SetY(int Y)
	{
		nPosY = Y;
	}
};

class SlowSpell : public Spells{
private:
	float fTimer;
	float fSlowProcentage;
	static int SlowActive;
public:
	SlowSpell();
	SlowSpell(int x, int y);
	void DrawSelf(olc::PixelGameEngine* pge) override;
	void DrawSelfNotCast(olc::PixelGameEngine* pge) override;
	bool CheckSpell(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) override;
};

class Bomb : public Spells {
private:
	int x;
	int y;
	float fTimer;
	float fVelocity;
	bool bExplosion;
	float fElapsedT;
	const float fGravity;
	olc::Sprite *spr;

public:
	static int nDamage;
	static int cost;
	Bomb();
	Bomb(int x, int y);
	void DrawSelf(olc::PixelGameEngine* pge) override;
	void DrawSelfNotCast(olc::PixelGameEngine* pge) override;
	bool CheckSpell(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) override;
	void DoDamage(std::list<std::shared_ptr<Minion>> &listMinions);
	~Bomb()
	{
		delete spr;
	}
};