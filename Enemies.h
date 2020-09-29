#pragma once
#include "Minion.h"

class Viking : public Minion {
private:
	// Stats
	const float fHealthMax;
	float fVelocity;
	const int GoldWorth;
	float fHealth;
public:
	Viking();
	Viking(float x, float y);
	void TakeDamage(float fDamage) override;
	void DrawSelf(olc::PixelGameEngine *pge) override;
	
	inline float GetHealth() const noexcept override
	{
		return fHealth;
	}
	inline int GetWorth() const noexcept override
	{
		return GoldWorth;
	}
	inline float GetVel() const noexcept override
	{
		return fVelocity;
	}
	void SetSlow(float fSlow) override
	{
		if (!bSlowed)
		{
			fVelocity *= fSlow;
			bSlowed = true;
		}
		else if (bSlowed && fSlow > 1)
		{
			fVelocity *= fSlow;
			bSlowed = false; 
		}
	}
};
// Warrior class
class Warrior : public Minion {
private:
	// Stats
	const float fHealthMax;
	float fVelocity;
	const int GoldWorth;
	float fHealth;
public:
	Warrior();
	Warrior(float x, float y);
	void TakeDamage(float fDamage) override;
	void DrawSelf(olc::PixelGameEngine *pge) override;
	
	inline float GetHealth() const noexcept override
	{
		return fHealth;
	}
	inline int GetWorth() const noexcept override
	{
		return GoldWorth;
	}
	inline float GetVel() const noexcept override
	{
		return fVelocity;
	}
	void SetSlow(float fSlow) override
	{
		if (!bSlowed)
		{
			fVelocity *= fSlow;
			bSlowed = true;
		}
		else if (bSlowed && fSlow > 1)
		{
			fVelocity *= fSlow;
			bSlowed = false;
		}
	}
};

// Blue Blob class
class BlueBlob : public Minion {
private:
	// Stats
	const float fHealthMax;
	float fVelocity;
	const int GoldWorth;
	float fHealth;
public:
	BlueBlob();
	BlueBlob(float x, float y);
	void TakeDamage(float fDamage) override;
	void DrawSelf(olc::PixelGameEngine *pge) override;

	inline float GetHealth() const noexcept override
	{
		return fHealth;
	}
	inline int GetWorth() const noexcept override
	{
		return GoldWorth;
	}
	inline float GetVel() const noexcept override
	{
		return fVelocity;
	}
	void SetSlow(float fSlow) override
	{
		if (!bSlowed)
		{
			fVelocity *= fSlow;
			bSlowed = true;
		}
		else if (bSlowed && fSlow > 1)
		{
			fVelocity *= fSlow;
			bSlowed = false;
		}
	}
};

//Ghost class
class Ghost : public Minion {
private:
	// Stats
	const float fHealthMax;
	float fVelocity;
	const int GoldWorth;
	float fHealth;
public:
	Ghost();
	Ghost(float x, float y);
	void TakeDamage(float fDamage) override;
	void DrawSelf(olc::PixelGameEngine *pge) override;

	inline float GetHealth() const noexcept override
	{
		return fHealth;
	}
	inline int GetWorth() const noexcept override
	{
		return GoldWorth;
	}
	inline float GetVel() const noexcept override
	{
		return fVelocity;
	}
	void SetSlow(float fSlow) override
	{
		if (!bSlowed)
		{
			fVelocity *= fSlow;
			bSlowed = true;
		}
		else if (bSlowed && fSlow > 1)
		{
			fVelocity *= fSlow;
			bSlowed = false;
		}
	}
};

//Evil Wizzard class
class EvilWizzard : public Minion {
private:
	// Stats
	const float fHealthMax;
	float fVelocity;
	const int GoldWorth;
	float fHealth;
public:
	EvilWizzard();
	EvilWizzard(float x, float y);
	void TakeDamage(float fDamage) override;
	void DrawSelf(olc::PixelGameEngine *pge) override;

	inline float GetHealth() const noexcept override
	{
		return fHealth;
	}
	inline int GetWorth() const noexcept override
	{
		return GoldWorth;
	}
	inline float GetVel() const noexcept override
	{
		return fVelocity;
	}
	void SetSlow(float fSlow) override
	{
		if (!bSlowed && fSlow < 1.0f)
		{
			fVelocity *= fSlow;
			bSlowed = true;
		}
		else if (bSlowed && fSlow > 1.0f)
		{
			fVelocity *= fSlow;
			bSlowed = false;
		}
	}
};