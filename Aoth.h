#pragma once
#include "olcPixelGameEngine.h"
#include "ScanLineSprite.h"
#include "MouseSelection.h"
#include "Objective.h"
#include "Minion.h"
#include "Spells.h"


typedef struct Entrence
{
	int passage;
	float timer;
	float elapser;
	int stage;
}Entrence;

//class Selection;
class Aoth : public olc::PixelGameEngine
{
private:
	// Map Data
	int nMapWidth;
	int nMapHeight;
	int nSize;
	int Lives;
	bool GameOver;
	bool Victory;
	bool End;
	float DefTimer;

	std::string sMap;
	std::list<Entrence*> listEnter;
	// Enemies on Map
	std::list<std::shared_ptr<Minion>> listEnemy;
	// Towers on Map
	std::list<std::shared_ptr<Objective>> listTower;
	// Spells
	std::list<std::unique_ptr<Spells>> listSpells;
	// Select
	Selection *Selected;
	ScanLineSprite *map;

public:
	Aoth()
	{
		sAppName = "AOTH";
	}
private:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	bool LoadMap(); 
	void DrawMap();
	void UserInput();
	void MinionWaves(float fElapsedTime);
public:
	inline char OnMap(float X, float Y)
	{
		return sMap[(int)(Y / nSize) * nMapWidth + (int)(X / nSize)];
	}
	~Aoth()
	{
		listEnter.clear();
		listEnemy.clear();
		listTower.clear();
		listSpells.clear();
		delete Selected;
		delete map;
	}
};
