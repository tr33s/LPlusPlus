#pragma once
#include <map>
#include "PluginData.h"
#include "PluginSDK.h"

class SpellManager
{
public:
	static void Initialize(IPluginSDK* sdk);
	static ISpell2* Q;
	static ISpell2* W;
	static ISpell2* E;
	static ISpell2* R;
	static ISpell2* Pix;
	static bool InRange(ISpell2* spell, IUnit* unit);
	static double GetDamage(ISpell2* spell, IUnit* unit, int stage = 0);
	static std::pair<Vec3, int> GetAoePrediction(ISpell2* spell, bool includeMinions, bool includeHeroes);
	static boolean CanKill(ISpell2* spell, IUnit* unit);
	static void SetMap(int mode, std::map<ISpell2*, IMenuOption*> map);
private:
	static IUnit* player;
	static std::map<int, std::map<ISpell2*, IMenuOption*>> spellMap;
};
