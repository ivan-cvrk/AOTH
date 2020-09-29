#pragma once
#include "Objective.h"
#include "Spells.h"
#include <vector>
#include <map>

const enum class eItem { NOTHING = 0, TOWER, SLOWSPELL, BOMB, INFERNO };
// TREBA NAPISAT DECONSTRUCTOR, DODAT BOMBE I DRUGI TOURET
typedef struct table
{	
	float x;
	float y;
	eItem eObj;
	olc::Sprite *spr;
	table(float X, float Y, eItem eObj, olc::Sprite *spr = nullptr) : x(X), y(Y), eObj(eObj), spr(spr)
	{}
}sTableShopItem;

class Selection {
private:
	int nMoney;
	Objective *oSelected;
	eItem eTypeSel;
	Spells *oSpell;
	std::vector<std::unique_ptr<sTableShopItem>> Table;
	std::weak_ptr<Objective> TourToShow;
	std::map<eItem, int> mPrices{
		{eItem::TOWER, 50},
		{eItem::SLOWSPELL, 150},
		{eItem::BOMB, 10},
		{eItem::INFERNO, 500}
	};
public:
	bool bPlaced = true;
	bool bToBeShown = false;

	Selection();
	void ChangeSelect(eItem eSlct);
	void DrawShopTable(olc::PixelGameEngine *pge);
	bool CheckWhatSel(int MousePosX, int MousePosY, std::list<std::shared_ptr<Objective>> &listTower);
	void ShowTourData(olc::PixelGameEngine *pge);
	
	inline void AddGold(int gold)
	{
		nMoney += gold;
	}

	float distance(float x1, float y1, float x2, float y2) {
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}

	inline int Money()
	{
		return nMoney;
	}

	inline Objective* GetSelectedObj()
	{
		return oSelected;
	}
	inline Spells* GetSelectedSpell()
	{
		return oSpell;
	}
	inline eItem GetSelType()
	{
		return eTypeSel;
	}
	void ChangePrice(eItem item, int newPrice)
	{
		mPrices[item] = newPrice;
	}
	int GetPrice(eItem item)
	{
		return mPrices[item];
	}

	bool Pay(int price)
	{
		if (nMoney - price >= 0)
		{
			nMoney -= price;
			return true;
		}
		return false;
	}
	bool Pay(eItem item)
	{
		if (nMoney - mPrices[item] >= 0)
		{
			nMoney -= mPrices[item];
			return true;
		}
		return false;
	}
	~Selection();
};