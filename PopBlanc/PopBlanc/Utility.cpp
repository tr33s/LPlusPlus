#include "Utility.h"
#include "PluginData.h"
#include "PluginSDK.h"

std::vector<IUnit*> enemies;
std::vector<IUnit*> allies;
IUnit* player;

Utility::Utility()
{
	enemies = GEntityList->GetAllHeros(false, true);
	allies = GEntityList->GetAllHeros(true, false);
	player = GEntityList->Player();
}


Utility::~Utility()
{
}

bool Utility::InRange(IUnit* unit, float range)
{
	return (unit->ServerPosition() - player->ServerPosition()).Length() <= range;
}

int Utility::CountBuffs(std::vector<IUnit*> units, const char* buff)
{
	if (units.empty())
	{
		return 0;
	}

	auto count = 0;
	for (auto unit : units)
	{
		if (unit != nullptr && unit->HasBuff(buff))
		{
			count++;
		}
	}

	return count;
}

int Utility::CountMinionsInRange(const Vec3 position, float range)
{
	auto count = 0;
	for (auto obj : GEntityList->GetAllMinions(false, true, false))
	{
		if (obj != nullptr && obj->IsValidObject() && (obj->ServerPosition() - position).Length() <= range)
		{
			count++;
		}
	}

	return count;
}

std::vector<IUnit*> Utility::GetEnemiesInRange(IUnit* unit, float range)
{
	return GetInRange(unit, range, enemies);
}

std::vector<IUnit*> Utility::GetAlliesInRange(IUnit* unit, float range)
{
	return GetInRange(unit, range, allies);
}

std::vector<IUnit*> Utility::GetInRange(IUnit* unit, float range, std::vector<IUnit*> units)
{
	std::vector<IUnit*> inRange;

	if (units.empty())
	{
		return inRange;
	}

	auto networkId = unit->GetNetworkId();

	for (auto obj : units)
	{
		if (obj != nullptr && obj->IsValidObject() && !obj->IsDead() && obj->GetNetworkId() != networkId && (obj->ServerPosition() - unit->ServerPosition()).Length() <= range)
		{
			inRange.push_back(obj);
		}
	}

	return inRange;
}

int Utility::CountEnemiesInRange(IUnit* unit, float range)
{
	return CountInRange(unit, range, enemies);
}

int Utility::CountAlliesInRange(IUnit* unit, float range)
{
	return CountInRange(unit, range, allies);
}

int Utility::CountInRange(IUnit* unit, float range, std::vector<IUnit*> units)
{
	return GetInRange(unit, range, units).size();
}

