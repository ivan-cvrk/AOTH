#include "Spells.h"

int SlowSpell::SlowActive = 0;

SlowSpell::SlowSpell() 
{
	nRadius = 50;
}
SlowSpell::SlowSpell(int x, int y) : fTimer(10.0f), fSlowProcentage(0.5f)
{
	nPosX = x;
	nPosY = y;
	nRadius = 50;
	SlowActive++;
}

void SlowSpell::DrawSelf(olc::PixelGameEngine* pge)
{
	pge->SetPixelMode(olc::Pixel::ALPHA);
	pge->FillCircle(nPosX, nPosY, nRadius, olc::Pixel(73, 252, 238, 100));
	pge->SetPixelMode(olc::Pixel::NORMAL);
}
void SlowSpell::DrawSelfNotCast(olc::PixelGameEngine* pge)
{
	pge->DrawCircle(nPosX, nPosY, nRadius, olc::CYAN);
}

bool SlowSpell::CheckSpell(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime)
{
	fTimer -= fElapsedTime;
	if (SlowActive > 1)
	{
		SlowActive--;
		return false;
	}
	if (fTimer > 0)
	{
		for (auto &minion : listEnemy)
		{
				if (!minion->Slowed() && Distance(minion->GetX(), minion->GetY(), (float)nPosX, (float)nPosY) <= nRadius)
				{
					minion->SetSlow(fSlowProcentage);
				}
				if (minion->Slowed() && Distance(minion->GetX(), minion->GetY(), (float)nPosX, (float)nPosY) > nRadius)
				{
					minion->SetSlow(1.0f / fSlowProcentage);
				}
		}
		return true;
	}
	else
	{
		for (auto &minion : listEnemy)
		{
			if (minion->Slowed())
			{
				minion->SetSlow(1.0f / fSlowProcentage);
				std::cout << "VISE NISAM SLOWAN" << std::endl;
			}
			std::cout << "NOVI MINION" << std::endl;
		}
		SlowActive--;
		return false;
	}
}

int Bomb::nDamage = 50;

Bomb::Bomb(): fGravity(1000.0f)
{
	nRadius = 100;
}

Bomb::Bomb(int x, int y): x(x), y(-30), fTimer(0.1f), fVelocity(0.0f), bExplosion(false), fElapsedT(0.0f), fGravity(1000.0f)
{
	spr = new olc::Sprite("Bomb.png");
	nRadius = 100;
	nPosX = x;
	nPosY = y;
}

bool Bomb::CheckSpell(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime)
{
	fVelocity += fGravity * fElapsedTime;
	y += (int)(fVelocity * fElapsedTime);
	if (y >= nPosY && !bExplosion)
	{
		bExplosion = true;
		DoDamage(listEnemy);
	}
	else if (bExplosion)
	{
		fElapsedT = fElapsedTime;
	}
	return (fTimer < 0) ? false : true;
}

void Bomb::DrawSelf(olc::PixelGameEngine* pge)
{
	if (!bExplosion)
	{
		pge->SetPixelMode(olc::Pixel::ALPHA);
		pge->DrawSprite(x, y, spr);
		pge->SetPixelMode(olc::Pixel::NORMAL);
	}
	else
	{
		fTimer -= fElapsedT;
		if (fTimer > 0)
		{
			pge->SetPixelMode(olc::Pixel::ALPHA);
			pge->FillCircle(nPosX, nPosY, nRadius, olc::Pixel(252, 219, 3, 100));
			pge->FillCircle(nPosX, nPosY, nRadius/2, olc::Pixel(255, 242, 140, 150));
			pge->SetPixelMode(olc::Pixel::NORMAL);
		}
	}
}
void Bomb::DrawSelfNotCast(olc::PixelGameEngine* pge)
{
	pge->DrawCircle(nPosX, nPosY, nRadius, olc::Pixel(255, 124, 10));
}

void Bomb::DoDamage(std::list<std::shared_ptr<Minion>> &listMinions)
{
	for (auto &minion : listMinions)
	{
		float dist = Distance(minion->GetX(), minion->GetY(), (float)nPosX, (float)nPosY);
		if (dist <= (float)nRadius)
		{
			minion->TakeDamage((float)nDamage * (nRadius/dist));
		}
	}
}