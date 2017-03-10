#pragma once
#include <unordered_map>
#include "PluginSDK.h"

class IUnit;

class DamageTracker
{
public:
	explicit DamageTracker(IPluginSDK* sdk, bool trackSkillshots = true);

	float getIncomingDamage(IUnit* unit) const;
	float getIncomingDamagePercent(IUnit* unit) const;
	bool hasIncomingDamage(IUnit* unit) const;
	bool hasIncomingLethalDamage(IUnit* unit, float& extraDamage) const;

private:
	IPluginSDK* sdk;
	bool trackSkillshots;

	std::unordered_map<int, float> damage;
};
