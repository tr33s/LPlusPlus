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

bool Utility::IsValidUnit(IUnit* unit)
{
	return unit != nullptr && unit->IsValidObject() && unit->GetType() != FL_INVALID && unit->GetType() != FL_TURRET && unit->GetType() != FL_MISSILE;
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
		if (IsValidUnit(obj) && (obj->ServerPosition() - position).Length() <= range)
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
		if (IsValidUnit(obj) && !obj->IsDead() && obj->GetNetworkId() != networkId && (obj->ServerPosition() - unit->ServerPosition()).Length() <= range)
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

void Utility::CreateConsoleWindow()
{
	AllocConsole();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	SetConsoleTitleA("Debug Console");
}

void Utility::LogConsole(char* Fmt, ...)
{
	DWORD dwBytes = 0;
	char szBuffer[1024] = {0};

	va_list va;
	va_start(va, Fmt);
	vsnprintf_s(szBuffer, sizeof(szBuffer), Fmt, va);
	va_end(va);

	strcat_s(szBuffer, "\n");

	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), szBuffer, strlen(szBuffer), &dwBytes, nullptr);
}

