#pragma once
#include <vector>
class Vec3;
class IUnit;

class Utility
{
public:
	Utility();
	~Utility();
	static float d(IUnit* unit, IUnit* unit2);
	static float d(IUnit* unit, Vec3 pos);
	static float d(Vec3 pos, Vec3 pos2);
	static bool IsCastableType(IUnit* unit, bool includeTurrets = false);
	static bool IsAlly(IUnit* unit);
	static bool IsEnemy(IUnit* unit);
	static int CountEnemiesInRange(IUnit* unit, float range);
private:
	static IUnit* player;
	static std::vector<int> goodTypes;
	static bool InVector(int obj, std::vector<int> vector);
};
