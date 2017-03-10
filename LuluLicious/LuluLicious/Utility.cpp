#include "Utility.h"
#include "LPPConstants.h"
#include "PluginData.h"
#include "Pix.h"


std::vector<int> Utility::goodTypes = {FL_CREEP, FL_HERO};
IUnit* Utility::player;

Utility::Utility()
{
	player = GEntityList->Player();
}


Utility::~Utility()
{
}

float Utility::d(IUnit* unit, IUnit* unit2)
{
	auto pos = IsCastableType(unit) ? unit->ServerPosition() : unit->GetPosition();
	auto pos2 = IsCastableType(unit2) ? unit2->ServerPosition() : unit2->GetPosition();
	return d(pos, pos2);
}

float Utility::d(IUnit* unit, Vec3 pos)
{
	auto pos2 = IsCastableType(unit) ? unit->ServerPosition() : unit->GetPosition();
	return d(pos, pos2);
}

float Utility::d(Vec3 pos, Vec3 pos2)
{
	return (pos - pos2).Length();
}

bool Utility::IsCastableType(IUnit* unit, bool includeTurrets)
{
	auto type = unit->GetType();
	return InVector(type, goodTypes) || (includeTurrets && type == FL_TURRET);
}

bool Utility::IsAlly(IUnit* unit)
{
	return unit->GetTeam() == GEntityList->Player()->GetTeam();
}

bool Utility::IsEnemy(IUnit* unit)
{
	// will return true for neutral
	return unit->GetTeam() != player->GetTeam();
}

int Utility::CountEnemiesInRange(IUnit* unit, float range)
{
	auto count = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (unit->IsValidTarget(enemy, range))
		{
			count++;
		}
	}

	return count;
}

bool Utility::InVector(int obj, std::vector<int> vector)
{
	return find(vector.begin(), vector.end(), obj) != vector.end();
}
