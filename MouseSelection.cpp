#include "MouseSelection.h"
#include "Towers.h"
#include "Inferno.h"

Selection::Selection() : nMoney(50), oSelected(nullptr), eTypeSel(eItem::NOTHING), oSpell(nullptr)
{
	Table.push_back(std::make_unique<sTableShopItem>( 995.0f, 210.0f, eItem::TOWER, new olc::Sprite("ArcherIcon.png") ));
	Table.push_back(std::make_unique<sTableShopItem>(993.0f, 200.0f + 80.0f, eItem::INFERNO, new olc::Sprite("InfernoIcon (1).png")));
	Table.push_back(std::make_unique<sTableShopItem>((62.5f * 16), 22.0f * 16, eItem::SLOWSPELL));
	Table.push_back(std::make_unique<sTableShopItem>( 60.0f * 16, 22.0f * 16, eItem::BOMB, new olc::Sprite("Bomb.png") ));
}

void Selection::ChangeSelect(eItem eSlct)
{
	if (GetSelectedObj() != nullptr)
	{
		delete oSelected;
		oSelected = nullptr;
	}
	if (oSpell != nullptr)
	{
		delete oSpell;
		oSpell = nullptr;
	}
	if (eSlct == eItem::NOTHING)
	{
		eTypeSel = eItem::NOTHING;
	}
	else if (eSlct == eItem::TOWER)
	{
		eTypeSel = eItem::TOWER;
		oSelected = new Tower;
		bPlaced = false;
	}
	else if (eSlct == eItem::INFERNO)
	{
		eTypeSel = eItem::INFERNO;
		oSelected = new Inferno;
		bPlaced = false;
	}
	else if (eSlct == eItem::SLOWSPELL)
	{
		eTypeSel = eItem::SLOWSPELL;
		oSpell = new SlowSpell;
		bPlaced = false;
	}
	else if (eSlct == eItem::BOMB)
	{
		eTypeSel = eItem::BOMB;
		oSpell = new Bomb;
		bPlaced = false;
	}
}

void Selection::DrawShopTable(olc::PixelGameEngine *pge)
{
	pge->DrawString(950, 150, std::to_string(nMoney) + "$", olc::YELLOW, 2);
	pge->DrawLine((int32_t)(1024 - 6 * 16), 175, 1024, 175, olc::Pixel(79, 35, 1));
	for (auto &Table : Table)
	{
		olc::GFX2D::Transform2D t;
		switch (Table->eObj)
		{
		case eItem::TOWER:
			t.Translate(-Table->spr->width / 2.0f, -Table->spr->height / 2.0f);
			t.Scale(1.5f, 1.5f);
			t.Translate(Table->x, Table->y);
			pge->SetPixelMode(olc::Pixel::ALPHA);
			olc::GFX2D::DrawSprite(Table->spr, t);
			pge->SetPixelMode(olc::Pixel::NORMAL);
			pge->DrawString((int32_t)Table->x - 60, (int32_t)Table->y - 5, std::to_string(mPrices[eItem::TOWER]) + "$", olc::YELLOW, 1);
			break;
		case eItem::INFERNO:
			t.Translate(-Table->spr->width / 2.0f, -Table->spr->height / 2.0f);
			t.Scale(1.5f, 1.5f);
			t.Translate(Table->x, Table->y);
			pge->SetPixelMode(olc::Pixel::ALPHA);
			olc::GFX2D::DrawSprite(Table->spr, t);
			pge->SetPixelMode(olc::Pixel::NORMAL);
			pge->DrawString((int32_t)Table->x - 60, (int32_t)Table->y - 5, std::to_string(mPrices[eItem::INFERNO]) + "$", olc::YELLOW, 1);
			break;
		case eItem::SLOWSPELL:
			pge->FillCircle((int32_t)Table->x, (int32_t)Table->y, 10, olc::CYAN);
			pge->DrawString((int32_t)Table->x - 10, (int32_t)Table->y + 20, std::to_string(mPrices[eItem::SLOWSPELL]) + "$", olc::YELLOW, 1);
			break;
		case eItem::BOMB:
			t.Translate(-Table->spr->width / 2.0f, -Table->spr->height / 2.0f);
			t.Translate(Table->x, Table->y);
			pge->SetPixelMode(olc::Pixel::ALPHA);
			olc::GFX2D::DrawSprite(Table->spr, t);
			pge->SetPixelMode(olc::Pixel::NORMAL);
			pge->DrawString((int32_t)Table->x - 10, (int32_t)Table->y + 20, std::to_string(mPrices[eItem::BOMB]) + "$", olc::YELLOW, 1);
			break;
		}
	}
}

bool Selection::CheckWhatSel(int MousePosX, int MousePosY, std::list<std::shared_ptr<Objective>> &listTower)
{ 
	// IF IN SHOP COORDINATES
	if (MousePosX > 1024 - 6 * 16 && MousePosY > 8 * 16 && MousePosY < 26 * 16)
	{
		if (!bToBeShown)
		{
			for (auto &Table : Table)
			{
				if (distance((float)MousePosX, (float)MousePosY, Table->x, Table->y) < 15 || (Table->spr != nullptr && distance((float)MousePosX, (float)MousePosY, Table->x, Table->y) < Table->spr->width))
				{
					ChangeSelect(Table->eObj);
					bToBeShown = false;
					return true;
				}
			}
		}
		else
		{
			if (MousePosX > 1024 - 5.5 * 16 && MousePosX < 1024 - 0.5f * 16 && MousePosY > 22.5 * 16 && MousePosY < 24.5 * 16)
			{
				if (auto TourToShow_Shared = TourToShow.lock())
				{
					if(TourToShow_Shared->GetTouretInfo()->nLevel < 6 && Pay(TourToShow_Shared->GetTouretInfo()->nUpgradeCost))
					TourToShow_Shared->Upgrade();
					bToBeShown = true;
					return true;
				}
			}
		}
	}
	else
	{
		for (auto &a : listTower)
		{
			if (distance((float)MousePosX, (float)MousePosY, a->GetX(), a->GetY() - 20) < a->spr->width)
			{
				bToBeShown = true;
				TourToShow = a;
				if (a->GeteType() == eItem::TOWER)
				{
					eTypeSel = eItem::TOWER;
				}
				return true;
			}
		}
	}
	bToBeShown = false;
	return false;
}

void Selection::ShowTourData(olc::PixelGameEngine *pge)
{
	if (auto TourData = TourToShow.lock())
	{
		pge->FillTriangle((int32_t)(TourData->GetX() - 5), (int32_t)(TourData->GetY() + 15), (int32_t)(TourData->GetX()), (int32_t)(TourData->GetY() + 5), (int32_t)(TourData->GetX() + 5), (int32_t)(TourData->GetY() + 15), olc::Pixel(201, 13, 0));
		pge->DrawString(950, 150, std::to_string(nMoney) + "$", olc::YELLOW, 2);
		pge->DrawLine((int32_t)(1024 - 6 * 16), 175, 1024, 175, olc::Pixel(79, 35, 1));
		pge->DrawString((int32_t)(1024 - 5.5 * 16), (int32_t)(12 * 16), "lvl:" + std::to_string(TourData->GetTouretInfo()->nLevel), olc::GREY, 2);
		pge->DrawString((int32_t)(1024 - 5.5 * 16), (int32_t)(15 * 16), "Damage: " + std::to_string(TourData->GetTouretInfo()->fDamage), olc::GREY, 1);
		pge->DrawString((int32_t)(1024 - 5.5 * 16), (int32_t)(17 * 16), "ARate: " + std::to_string(TourData->GetTouretInfo()->fAttackRate), olc::GREY, 1);
		pge->DrawString((int32_t)(1024 - 5.5 * 16), (int32_t)(19 * 16), "Range: " + std::to_string(TourData->GetTouretInfo()->nRange), olc::GREY, 1);
		pge->DrawString((int32_t)(1024 - 5.5 * 16), (int32_t)(21.5 * 16), "UPGRADE: ", olc::GREY);
		pge->FillRect((int32_t)(1024 - 5.5 * 16), (int32_t)(22.5 * 16), 16 * 5, 16 * 2, olc::Pixel(79, 35, 1));
		if(TourData->GetTouretInfo()->nUpgradeCost == -1)
			pge->DrawString((int32_t)(1024 - 4.75 * 16), (int32_t)(23 * 16), "MAX", olc::RED, 2);
		else
			pge->DrawString((int32_t)(1024 - 4.75 * 16), (int32_t)(23 * 16), std::to_string(TourData->GetTouretInfo()->nUpgradeCost) + "$", olc::YELLOW, 2);
	}
}

Selection::~Selection() 
{
	mPrices.clear();
	Table.clear();
	if (oSpell != nullptr)
		delete oSpell;
	if (oSelected != nullptr)
		delete oSelected;
}