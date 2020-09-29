#include "Towers.h"
#include <cmath>


Tower::Tower() : nDamage(30), fAttackRate(1.2f), nRange(100), fTimer(0.0f), nLevel(1), nUpgradeCost(100)
{
	inf = new TouretInfo{ nLevel, (float)nDamage, fAttackRate, nRange, nUpgradeCost };
	olc::Sprite *spr = new olc::Sprite("ArcherTow1.png");
	SetSpr(spr);
}
Tower::Tower(float x, float y) : nDamage(30), fAttackRate(1.2f), nRange(100), fTimer(0.0f), nLevel(1), nUpgradeCost(100)
{
	inf = new TouretInfo{ nLevel, (float)nDamage, fAttackRate, nRange, nUpgradeCost };
	olc::Sprite *spr = new olc::Sprite("ArcherTow1.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
}
Tower::~Tower()
{
	listBullet.clear();
	delete inf;
} 

bool Objective::bShowRange = false;

void Tower::CheckTarget(std::list<std::shared_ptr<Minion>> &listEnemy, float fElapsedTime) {
	if (auto oTarget_shared = oTarget.lock()) {
		if (distance(oTarget_shared->GetX(), oTarget_shared->GetY(), this->GetX(), this->GetY() - (int)((this->spr->height)*0.2f)) > nRange)
			oTarget.reset();
		else
		{
			HitTarget(oTarget_shared, fElapsedTime);
		}
	}
	else {
		FindTarget(listEnemy);// if we get here it means that the shared_ptr in the list was deleted.
	}
}

void Tower::FindTarget(std::list<std::shared_ptr<Minion>> &listEnemy)
{
	float fLowestDist = (float)nRange;
	for (auto &a : listEnemy)
	{
		float fDist = distance(a->GetX(), a->GetY(), this->GetX(), this->GetY() - (int)((this->spr->height)*0.2f));
		if (fDist < fLowestDist)
		{
			fLowestDist = fDist;
			oTarget = a;
		}
	}
}

bool Tower::HitTarget(std::shared_ptr<Minion> &Target, float fElapsedTime)
{
	fTimer -= fElapsedTime;
	if (fTimer < 0)
	{
		fTimer = fAttackRate;
		if (!oTarget.expired())
		{
			if(nLevel < 3)
				listBullet.push_back(std::unique_ptr<BULLET>(new BULLET{ Target->GetX(), Target->GetY(), this->fX - 4, this->fY - this->spr->height / 2.0f, 200.0f, oTarget }));
			else if(nLevel >= 3 && nLevel < 6)
				listBullet.push_back(std::unique_ptr<BULLET>(new BULLET{ Target->GetX(), Target->GetY(), this->fX - 4, this->fY - this->spr->height / 2.0f - 30, 200.0f, oTarget }));
			else
				listBullet.push_back(std::unique_ptr<BULLET>(new BULLET{ Target->GetX(), Target->GetY(), this->fX - 7, this->fY - this->spr->height / 2.0f - 50, 200.0f, oTarget }));
		}
		return true;
	}
	return false;
}

void Tower::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height) * 0.95f);
	transformation.Scale(2, 2);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	if(bShowRange)
	pge->DrawCircle((int)this->GetX(), (int)this->GetY() - (int)((this->spr->height)*0.2f), nRange, olc::WHITE);
	pge->SetPixelMode(olc::Pixel::NORMAL);
}

void Tower::Bullet(olc::PixelGameEngine *pge, float fElapsedTime)
{
	for (auto &sBullet : listBullet)
	{
		if (auto oTarget_shared = sBullet->bullTarget.lock()) {
			sBullet->fTargetX = oTarget_shared->GetX();
			sBullet->fTargetY = oTarget_shared->GetY();
			sBullet->fBulletX += ((sBullet->fTargetX - sBullet->fBulletX) /
				distance(sBullet->fBulletX, sBullet->fBulletY, sBullet->fTargetX, sBullet->fTargetY))*sBullet->fBulletSpeed * fElapsedTime;
			sBullet->fBulletY += ((sBullet->fTargetY - sBullet->fBulletY) /
				distance(sBullet->fBulletX, sBullet->fBulletY, sBullet->fTargetX, sBullet->fTargetY))*sBullet->fBulletSpeed * fElapsedTime;
			if(nLevel < 3)
				pge->FillCircle((int32_t)sBullet->fBulletX, (int32_t)sBullet->fBulletY, 2, olc::YELLOW);
			else if(nLevel >= 3 && nLevel < 6)
				pge->FillCircle((int32_t)sBullet->fBulletX, (int32_t)sBullet->fBulletY, 2, olc::RED);
			else 
				pge->FillCircle((int32_t)sBullet->fBulletX, (int32_t)sBullet->fBulletY, 3, olc::Pixel(218, 0, 247));
		}
	}
	listBullet.remove_if([&](std::unique_ptr<BULLET> &bullet) {
		if (distance(bullet->fBulletX, bullet->fBulletY, bullet->fTargetX, bullet->fTargetY) < 3.0f)
		{
			if (auto oTarget_shared = bullet->bullTarget.lock())
			{
				oTarget_shared->TakeDamage((float)nDamage);
			}
			return true;
		}
		else if (bullet->bullTarget.expired())
		{
			return true;
		}
		else
			return false;
	});
}


void Tower::Upgrade()
{
	nLevel++;
	switch (nLevel)
	{
	case 2:
		nUpgradeCost = 150;
		nDamage = 35;
		fAttackRate = 1.11f;
		
		break;
	case 3:
		nUpgradeCost = 250;
		nDamage = 45;
		fAttackRate = 0.9f;
		nRange = 125;
		delete spr;
		spr = new olc::Sprite("ArcherTow2.png");

		break;
	case 4:
		nUpgradeCost = 400;
		nDamage = 50;
		fAttackRate = 0.66f; 

		break;
	case 5:
		nUpgradeCost = 700;
		nDamage = 55;
		fAttackRate = 0.55f;

		break;
	case 6:
		nDamage = 65;
		fAttackRate = 0.35f;
		nRange = 150;
		delete spr;
		spr = new olc::Sprite("ArcherTow3.png");
		nUpgradeCost = -1;

		break;
	}
	//Update inf to show
	inf->nLevel = nLevel;
	inf->fDamage = (float)nDamage;
	inf->fAttackRate = fAttackRate;
	inf->nRange = nRange;
	inf->nUpgradeCost = nUpgradeCost;
}