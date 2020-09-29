#include "Inferno.h"

Inferno::Inferno() : fDmgLvLscale(6.0f), dmgpSec(30.0f), nRange(100), fTimer(0.0f), nLevel(1), nUpgradeCost(800)
{
	olc::Sprite *spr = new olc::Sprite("InfernoTower.png");
	SetSpr(spr);
}

Inferno::Inferno(float x, float y) : fDmgLvLscale(6.0f), dmgpSec(30.0f), nRange(100), fTimer(0.0f), nLevel(1), nUpgradeCost(800)
{
	inf = new TouretInfo{ nLevel, fDmgLvLscale, 0, nRange, nUpgradeCost };
	olc::Sprite *spr = new olc::Sprite("InfernoTower.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fShotX = fX - 1;
	fShotY = fY - spr->height - 12;
}

void Inferno::CheckTarget(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) {
	if (auto oTarget_shared = oTarget.lock()) {
		if (distance(oTarget_shared->GetX(), oTarget_shared->GetY(), this->GetX(), this->GetY() - (int)((this->spr->height)*0.2f)) > nRange)
			oTarget.reset();
		else
		{
			HitTarget(oTarget_shared, fElapsedTime);
		}
	}
	else {
		FindTarget(listEnemy);
	}
}

void Inferno::FindTarget(std::list<std::shared_ptr<Minion>> &listEnemy)
{
	float fLowestDist = (float)nRange;
	for (auto &a : listEnemy)
	{
		float fDist = distance(a->GetX(), a->GetY(), this->GetX(), this->GetY() - (int)((this->spr->height)*0.2f));
		if (fDist < fLowestDist)
		{
			fLowestDist = fDist;
			oTarget = a;
			dmgpSec = a->GetHealth() / fDmgLvLscale;
		}
	}
}

bool Inferno::HitTarget(std::shared_ptr<Minion> &Target, float fElapsedTime)
{
		if (!oTarget.expired())
		{
			Target->TakeDamage(dmgpSec * fElapsedTime);
		}
		return true;
}

void Inferno::Bullet(olc::PixelGameEngine *pge, float fElapsedTime) 
{
	if (auto oTarget_shared = oTarget.lock())
	{
		pge->DrawLine((int32_t)fShotX, (int32_t)fShotY, (int32_t)oTarget_shared->GetX(), (int32_t)oTarget_shared->GetY(), olc::RED);
		pge->FillCircle((int32_t)oTarget_shared->GetX(), (int32_t)oTarget_shared->GetY(), 2, olc::RED);
	}
}

void Inferno::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height) * 0.95f);
	transformation.Scale(1.5f, 1.5f);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	if (bShowRange)
		pge->DrawCircle((int)this->GetX(), (int)this->GetY() - (int)((this->spr->height)*0.2f), nRange, olc::RED);
	pge->SetPixelMode(olc::Pixel::NORMAL);
}

void Inferno::Upgrade()
{
	nLevel++;
	switch (nLevel) {
	case 2:
		fDmgLvLscale = 4.0f;
		inf->fDamage = fDmgLvLscale;
		nRange = 125;
		inf->nRange = nRange;
		delete spr;
		spr = new olc::Sprite("InfernoTower2.png");
		nUpgradeCost = 2500;
		inf->nUpgradeCost = nUpgradeCost;
		break;
	case 3:
		nRange = 150;
		inf->nRange = nRange;
		fDmgLvLscale = 2.5f;
		inf->fDamage = fDmgLvLscale;
		delete spr;
		spr = new olc::Sprite("InfernoTower3.png");
		nUpgradeCost = -1;
		inf->nUpgradeCost = nUpgradeCost;
		break;
	}
	inf->nLevel = nLevel;
}