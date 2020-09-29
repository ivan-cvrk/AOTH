#include "Enemies.h"

/*****************VIKING****VIKING*****VIKING***********************************/

Viking::Viking() : fHealthMax(180.0f), fVelocity(70.0f), GoldWorth(30)
{
	olc::Sprite *spr = new olc::Sprite("VIKING.png");
	SetSpr(spr);
	fHealth = fHealthMax;
}
Viking::Viking(float x, float y) : fHealthMax(180.0f), fVelocity(70.0f), GoldWorth(30)
{
	olc::Sprite *spr = new olc::Sprite("VIKING.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fHealth = fHealthMax;
}
void Viking::TakeDamage(float fDamage)
{
	fHealth -= fDamage;
}
void Viking::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height / 2.0f));
	if (bSwapSide)
		transformation.Scale(-1, 1);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation); 
	pge->SetPixelMode(olc::Pixel::NORMAL);
	if (fHealth < fHealthMax && fHealth > 0)
	{
		pge->FillRect((int)(fX - spr->width / 2), (int)(fY - spr->height / 2 - 3), (int)(spr->width * (fHealth/fHealthMax)), 2, olc::Pixel(94, 255, 36));
		pge->FillRect((int)(fX - spr->width / 2 + (spr->width * (fHealth / fHealthMax))), (int)(fY - spr->height / 2 - 3), (int)(spr->width - spr->width * (fHealth / fHealthMax)), 2, olc::RED);
	}
}


/***********************WARRIOR****WARRIOR****WARRIOR********************************/

Warrior::Warrior() : fHealthMax(250.0f), fVelocity(80.0f), GoldWorth(40)
{
	olc::Sprite *spr = new olc::Sprite("WARRIOR.png");
	SetSpr(spr);
	fHealth = fHealthMax;
}
Warrior::Warrior(float x, float y) : fHealthMax(250.0f), fVelocity(80.0f), GoldWorth(40)
{
	olc::Sprite *spr = new olc::Sprite("WARRIOR.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fHealth = fHealthMax;
}
void Warrior::TakeDamage(float fDamage)
{
	fHealth -= fDamage;
}
void Warrior::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height / 2.0f));
	if (bSwapSide)
		transformation.Scale(-1, 1);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	pge->SetPixelMode(olc::Pixel::NORMAL);
	if (fHealth < fHealthMax && fHealth > 0)
	{
		pge->FillRect((int)(fX - spr->width / 2), (int)(fY - spr->height / 2 - 3), (int)(spr->width * (fHealth / fHealthMax)), 2, olc::Pixel(94, 255, 36));
		pge->FillRect((int)(fX - spr->width / 2 + (spr->width * (fHealth / fHealthMax))), (int)(fY - spr->height / 2 - 3), (int)(spr->width - spr->width * (fHealth / fHealthMax)), 2, olc::RED);
	}
}

/**************BLUEBLOB*************BLUEBLOB********************************/

BlueBlob::BlueBlob() : fHealthMax(90.0f), fVelocity(50.0f), GoldWorth(15)
{
	olc::Sprite *spr = new olc::Sprite("BLUEBLOB.png");
	SetSpr(spr);
	fHealth = fHealthMax;
}
BlueBlob::BlueBlob(float x, float y) : fHealthMax(90.0f), fVelocity(50.0f), GoldWorth(15)
{
	olc::Sprite *spr = new olc::Sprite("BLUEBLOB.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fHealth = fHealthMax;
}
void BlueBlob::TakeDamage(float fDamage)
{
	fHealth -= fDamage;
}
void BlueBlob::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height / 2.0f));
	if (bSwapSide)
		transformation.Scale(-1, 1);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	pge->SetPixelMode(olc::Pixel::NORMAL);
	if (fHealth < fHealthMax && fHealth > 0)
	{
		pge->FillRect((int)(fX - spr->width / 2), (int)(fY - spr->height / 2 - 3), (int)(spr->width * (fHealth / fHealthMax)), 2, olc::Pixel(94, 255, 36));
		pge->FillRect((int)(fX - spr->width / 2 + (spr->width * (fHealth / fHealthMax))), (int)(fY - spr->height / 2 - 3), (int)(spr->width - spr->width * (fHealth / fHealthMax)), 2, olc::RED);
	}
}

/**********************GHOST******************GHOST*********************************/

Ghost::Ghost() : fHealthMax(200.0f), fVelocity(125.0f), GoldWorth(60)
{
	olc::Sprite *spr = new olc::Sprite("GHOST.png");
	SetSpr(spr);
	fHealth = fHealthMax;
}
Ghost::Ghost(float x, float y) : fHealthMax(200.0f), fVelocity(125.0f), GoldWorth(60)
{
	olc::Sprite *spr = new olc::Sprite("GHOST.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fHealth = fHealthMax;
}
void Ghost::TakeDamage(float fDamage)
{
	fHealth -= fDamage;
}
void Ghost::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height / 2.0f));
	if (bSwapSide)
		transformation.Scale(-1, 1);
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	pge->SetPixelMode(olc::Pixel::NORMAL);
	if (fHealth < fHealthMax && fHealth > 0)
	{
		pge->FillRect((int)(fX - spr->width / 2), (int)(fY - spr->height / 2 - 3), (int)(spr->width * (fHealth / fHealthMax)), 2, olc::Pixel(94, 255, 36));
		pge->FillRect((int)(fX - spr->width / 2 + (spr->width * (fHealth / fHealthMax))), (int)(fY - spr->height / 2 - 3), (int)(spr->width - spr->width * (fHealth / fHealthMax)), 2, olc::RED);
	}
}

/***************************************EVIL**WIZZARD****************************************/

EvilWizzard::EvilWizzard() : fHealthMax(1000.0f), fVelocity(80.0f), GoldWorth(100)
{
	olc::Sprite *spr = new olc::Sprite("EVILWIZZARD.png");
	SetSpr(spr);
	fHealth = fHealthMax;
}
EvilWizzard::EvilWizzard(float x, float y) : fHealthMax(1000.0f), fVelocity(50.0f), GoldWorth(100)
{
	olc::Sprite *spr = new olc::Sprite("EVILWIZZARD.png");
	SetSpr(spr);
	SetX(x);
	SetY(y);
	fHealth = fHealthMax;
}
void EvilWizzard::TakeDamage(float fDamage)
{
	fHealth -= fDamage;
}
void EvilWizzard::DrawSelf(olc::PixelGameEngine *pge)
{
	olc::GFX2D::Transform2D transformation;
	transformation.Translate(-(spr->width / 2.0f), -(spr->height / 2.0f));
	if (!bSwapSide)
		transformation.Scale(-1, 1);
	transformation.Scale(1.5, 1.5); 
	transformation.Translate(fX, fY);
	pge->SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::DrawSprite(spr, transformation);
	pge->SetPixelMode(olc::Pixel::NORMAL);
	if (fHealth < fHealthMax && fHealth > 0)
	{
		pge->FillRect((int)(fX - spr->width / 2), (int)(fY - spr->height / 2 - 12), (int)(spr->width * (fHealth / fHealthMax)), 2, olc::Pixel(94, 255, 36));
		pge->FillRect((int)(fX - spr->width / 2 + (spr->width * (fHealth / fHealthMax))), (int)(fY - spr->height / 2 - 12), (int)(spr->width - spr->width * (fHealth / fHealthMax)), 2, olc::RED);
	}
}
