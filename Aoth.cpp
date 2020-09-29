#include <fstream>
#include "Aoth.h"
#include "Enemies.h"
#include "Towers.h"
#include "Inferno.h"

bool Aoth::OnUserCreate() 
{
	nMapWidth = 64;
	nMapHeight = 36;
	nSize = 16;
	Lives = 3;
	GameOver = false;
	End = false;
	
	DefTimer = 3.5f;

	listEnter.push_back(new Entrence{ 1, 3.0f, 0.1f, 1});

	map = new ScanLineSprite("BackgroundPicRemake.png");

	if (!LoadMap())
		return false;

	Selected = new Selection;

	return true;
}
/************************************************************************************/
bool Aoth::OnUserUpdate(float fElapsedTime) 
{
	if (Victory)
	{
		DrawString(325, 250, "VICTORY", olc::BLACK, 5);
		if (GetMouse(0).bPressed)
			return false;
	}
	else if (GameOver)
	{
		DrawString(300, 250, "GAME OVER", olc::BLACK, 5);
		if(GetMouse(0).bPressed)
		return false;
	}
	else
	{
		map->DrawOnTarget(GetDrawTarget(), 0, 0, olc::Pixel::NORMAL);
		DrawMap();

		if (IsFocused())
			UserInput();
		// Go Trough All Enemies Displayed
		MinionWaves(fElapsedTime);
		for (auto &a : listEnemy)
		{
			switch (OnMap(a->GetX(), a->GetY()))
			{
			case 'R':
				a->NewPosRight(a->GetVel(), fElapsedTime);
				break;
			case 'D':
				a->NewPosDown(a->GetVel(), fElapsedTime);
				break;
			case 'L':
				a->NewPosLeft(a->GetVel(), fElapsedTime);
				break;
			case 'U':
				a->NewPosUp(a->GetVel(), fElapsedTime);
				break;
			default:
				break;
			}
			a->DrawSelf(this);
		}
		listEnemy.remove_if([&](std::shared_ptr<Minion> &o) {
			if (o->GetHealth() <= 0)
			{
				Selected->AddGold(o->GetWorth());
				return true;
			}
			else if (o->GetX() <= 0)
				return true;
			else if (o->GetX() >= ScreenWidth())
			{
				if(--Lives <= 0)
				GameOver = true;
				return true;
			}
			else if (o->GetY() <= 0)
				return true;
			else if (o->GetY() >= ScreenHeight())
				return true;
			else return false;
		});

		listSpells.remove_if([&](std::unique_ptr<Spells> &spell) {
			if (spell->CheckSpell(listEnemy, fElapsedTime))
			{
				spell->DrawSelf(this);
				return false;
			}
			else
				return true;
		});

		// Touret Shooting
		for (auto &a : listTower)
		{
			a->DrawSelf(this);
			a->Bullet(this, fElapsedTime);
			a->CheckTarget(listEnemy, fElapsedTime); 
		}
		// Show Shop
		if(!Selected->bToBeShown)
		Selected->DrawShopTable(this);
		// Show Selected at Cursor
		if (Selected->GetSelectedObj() != nullptr && !Selected->bPlaced)
		{
			Selected->GetSelectedObj()->SetX((float)GetMouseX());
			Selected->GetSelectedObj()->SetY((float)GetMouseY());
			Selected->GetSelectedObj()->DrawSelf(this);
		}
		if (Selected->GetSelectedSpell() != nullptr && !Selected->bPlaced)
		{
			Selected->GetSelectedSpell()->SetX(GetMouseX());
			Selected->GetSelectedSpell()->SetY(GetMouseY());
			Selected->GetSelectedSpell()->DrawSelfNotCast(this);
		}
		// If Touret Selected
		if (Selected->bToBeShown)
		{
			Selected->ShowTourData(this);
		}
	}
	return true;
}

/**********************************************************************************************/

// Load Map From File
bool Aoth::LoadMap()
{
	std::string sPom;
	std::fstream file;
	file.open("AOTHmap3.txt");
	if (file.is_open())
	{
		while (getline(file, sPom))
		{
			sMap += sPom;
		}
	}
	else 
		return false;
	file.close();
	return true;
}

// Draw Map Pixel By Pixel Based Of Map Data
void Aoth::DrawMap()
{
	for (int y = 0; y < nMapHeight; y++)
	{
		for (int x = 0; x < nMapWidth; x++)
		{
			/*if (sMap[y*nMapWidth + x] == '.')
			for (int py = 0; py < nSize; py++)
				{
					for (int px = 0; px < nSize; px++)
					{
						Draw(x*nSize + px, y*nSize + py, olc::Pixel(2, 227, 32));
					}
				}
			else if (sMap[y*nMapWidth + x] != '.' && sMap[y*nMapWidth + x] != 'T' && sMap[y*nMapWidth + x] != 'S')
				for (int py = 0; py < nSize; py++)
				{
					for (int px = 0; px < nSize; px++)
					{
						Draw(x*nSize + px, y*nSize + py, olc::YELLOW);
					}
				}*/
			if (sMap[y*nMapWidth + x] == 'T')
				for (int py = 0; py < nSize; py++)
				{
					for (int px = 0; px < nSize; px++)
					{
						Draw(x*nSize + px, y*nSize + py, olc::DARK_GREEN);
					}
				}
			else if (sMap[y*nMapWidth + x] == 'S')
				for (int py = 0; py < nSize; py++)
				{
					for (int px = 0; px < nSize; px++)
					{
						Draw(x*nSize + px, y*nSize + py, olc::Pixel(138, 63, 12));
					}
				}
		}
	}
}
// Mouse Clicks
void Aoth::UserInput()
{
	if (GetMouse(0).bPressed)
	{
		if (!Selected->bPlaced && Selected->GetSelType() == eItem::TOWER && OnMap((float)GetMouseX(), (float)GetMouseY()) == 'T')
		{
			if (Selected->Pay(eItem::TOWER))
			{
				listTower.push_back(std::make_shared<Tower>((float)GetMouseX(), (float)GetMouseY()));
				sMap[(int)(GetMouseY() / nSize) * nMapWidth + (int)(GetMouseX() / nSize)] = '.';
			}
		}
		else if (!Selected->bPlaced && Selected->GetSelType() == eItem::INFERNO && OnMap((float)GetMouseX(), (float)GetMouseY()) == 'T')
		{
			if (Selected->Pay(eItem::INFERNO))
			{
				listTower.push_back(std::make_shared<Inferno>((float)GetMouseX(), (float)GetMouseY()));
				sMap[(int)(GetMouseY() / nSize) * nMapWidth + (int)(GetMouseX() / nSize)] = '.';
			}
		}
		else if (!Selected->bPlaced && Selected->GetSelType() == eItem::SLOWSPELL && OnMap((float)GetMouseX(), (float)GetMouseY()) != 'S')
		{
			if (Selected->Pay(eItem::SLOWSPELL))
			listSpells.push_back(std::make_unique<SlowSpell>(GetMouseX(), GetMouseY()));
		}
		else if (!Selected->bPlaced && Selected->GetSelType() == eItem::BOMB && OnMap((float)GetMouseX(), (float)GetMouseY()) != 'S')
		{
			if (Selected->Pay(eItem::BOMB))
			{
				listSpells.push_back(std::make_unique<Bomb>(GetMouseX(), GetMouseY()));
					Bomb bomb;
					bomb.nDamage += 10;
					Selected->ChangePrice(eItem::BOMB, Selected->GetPrice(eItem::BOMB) + 60);
			}
		}
		else if (Selected->bPlaced)
		{
			if(Selected->CheckWhatSel(GetMouseX(), GetMouseY(), listTower))
			return;
		}
		Selected->bPlaced = true;
		Selected->ChangeSelect(eItem::NOTHING);
	}
	if (GetMouse(1).bPressed)
	{
		if (Selected->GetSelType() != eItem::BOMB && Selected->GetSelType() != eItem::SLOWSPELL)
			Selected->ChangeSelect(eItem::BOMB);
		else
			Selected->ChangeSelect(eItem::NOTHING);
	}
	if (GetMouse(2).bPressed)
	{
		Tower tower;
		(tower.bShowRange) ? tower.bShowRange = false : tower.bShowRange = true;
	}
	if (GetKey(olc::Key::SPACE).bPressed)
	{
		Selected->ChangeSelect(eItem::INFERNO);
	}
}

void Aoth::MinionWaves(float fElapsedTime)
{
	for (auto Enter : listEnter)
	{
		Enter->timer -= fElapsedTime;

		if (Enter->timer < 0)
		{
			if (Enter->elapser < 2.5f)
			{
				int posX, posY;
				if (Enter->passage == 3 && Enter->stage == 5 && Enter->elapser + 0.1f >= 2.5f)
				{
					listEnter.clear();
					End = true;
					break;
				}
				if (!(Enter->stage == 5 && Enter->elapser + 0.1f >= 2.5f))
					Enter->elapser += 0.1f;
				Enter->timer = DefTimer - Enter->elapser;
				switch (Enter->passage) {
				case 1:
					posX = 5 * 16;
					posY = 1;
					break;
				case 2:
					posX = 55 * 16;
					posY = 1;
					break;
				case 3:
					posX = 1;
					posY = 20 * 16;
				}
				switch (Enter->stage)
				{
				case 1:
					listEnemy.push_back(std::shared_ptr<Minion>(new BlueBlob{ (float)posX, (float)posY }));
					//listEnemy.push_back(std::make_shared <BlueBlob>(posX, posY));
					break;
				case 2:
					listEnemy.push_back(std::shared_ptr<Minion>(new Viking{ (float)posX, (float)posY }));
					//listEnemy.push_back(std::make_shared<Viking>(posX, posY));
					break;
				case 3:
					listEnemy.push_back(std::shared_ptr<Minion>(new Warrior{ (float)posX, (float)posY }));
					//listEnemy.push_back(std::make_shared<Warrior>(posX, posY));
					break;
				case 4:
					listEnemy.push_back(std::shared_ptr<Minion>(new Ghost{ (float)posX, (float)posY }));
					//listEnemy.push_back(std::make_shared<Ghost>(posX, posY));
					break;
				case 5:
					listEnemy.push_back(std::shared_ptr<Minion>(new EvilWizzard{ (float)posX, (float)posY }));
					//listEnemy.push_back(std::make_shared<EvilWizzard>(posX, posY));
					break;
				}
			}
			else
			{
				Enter->stage++;
				Enter->elapser = 0.0f;
				Enter->timer = DefTimer;
				if(Enter->stage == 3 && listEnter.size() < 3)
					listEnter.push_back(new Entrence{ Enter->passage + 1, 3.0f, 0.1f, 1 });
			}
		}
	}
	if (End && listEnemy.size() == 0)
		Victory = true;
}