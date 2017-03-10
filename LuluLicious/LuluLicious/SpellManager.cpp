#include "SpellManager.h"
#include "Utility.h"

IUnit* SpellManager::player;
ISpell2* SpellManager::Q;
ISpell2* SpellManager::W;
ISpell2* SpellManager::E;
ISpell2* SpellManager::R;
ISpell2* SpellManager::Pix;
std::map<int, std::map<ISpell2*, IMenuOption*>> SpellManager::spellMap;

void SpellManager::Initialize(IPluginSDK* sdk)
{
	Q = sdk->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	W = sdk->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	E = sdk->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	R = sdk->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	Pix = sdk->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	player = GEntityList->Player();
}

bool SpellManager::InRange(ISpell2* spell, IUnit* unit)
{
	return Utility::d(player, unit) < spell->Range();
}

double SpellManager::GetDamage(ISpell2* spell, IUnit* unit, int stage)
{
	return GDamage->GetSpellDamage(player, unit, spell->GetSlot(), stage);
}

std::pair<Vec3, int> SpellManager::GetAoePrediction(ISpell2* spell, bool includeMinions, bool includeHeroes)
{
	int count;
	Vec3 pos;
	spell->FindBestCastPosition(includeMinions, includeHeroes, pos, count);
	return std::make_pair(pos, count);
}

boolean SpellManager::CanKill(ISpell2* spell, IUnit* unit)
{
	return GetDamage(spell, unit) > unit->GetHealth();
}

void SpellManager::SetMap(int mode, std::map<ISpell2*, IMenuOption*> map)
{
	spellMap.insert(make_pair(mode, map));
}
