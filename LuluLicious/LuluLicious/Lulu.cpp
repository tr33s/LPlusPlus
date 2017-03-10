#include "PluginSDK.h"
#include "Pix.h"
#include "Utility.h"
#include "SpellManager.h"
#include "DamageTracker.h"
#include <string>
#include <iostream>
#include "EventManager.h"

PluginSetup("LuluLicious - Trees");

IMenu* Menu;
IMenu *QMenu, *WMenu, *EMenu, *RMenu, *PixMenu, *DrawMenu;

IMenuOption *ComboQ, *HarassQ, *FarmQ;
IMenuOption *InterruptW, *GapcloserW;
IMenuOption *SmartR, *KnockupR, *KnockupRCount, *InterruptR;
IMenuOption *PixQ, *PixEQ, *PixHarass;
IMenuOption *DrawQ, *DrawW, *DrawR, *DrawPix;

IUnit* player;
DamageTracker* damage;

std::map<IMenuOption*, ISpell2*> drawMap;

boolean PixLogic(IUnit* target)
{
	if (!PixQ->Enabled() && !PixEQ->Enabled())
	{
		return false;
	}

	if (!PixHarass->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		return false;
	}

	if (!SpellManager::Q->IsReady())
	{
		return false;
	}

	auto targ = target == nullptr ? Pix::GetTarget(PixEQ->Enabled() && SpellManager::E->IsReady()) : target;

	if (targ == nullptr)
	{
		return false;
	}

	auto pix = Pix::GetPix();

	if (Utility::d(targ, pix) > SpellManager::Q->Range())
	{
		auto eTarget = Pix::GetETarget(targ);
		if (eTarget != nullptr && SpellManager::E->CastOnTarget(eTarget))
		{
			GUtility->LogConsole("[Pix] EQ");
			return true;
		}
		return false;
	}

	if (SpellManager::Pix->CastOnTarget(targ))
	{
		GUtility->LogConsole("[Pix] Q");
		return true;
	}

	return false;
}

void OnInterruptible(InterruptibleSpell* spell)
{
	auto data = spell->Data;
	auto caster = GSpellData->GetCaster(data);

	if (InterruptW->Enabled() && SpellManager::W->IsReady() && SpellManager::InRange(SpellManager::W, caster) && SpellManager::W->CastOnUnit(caster))
	{
		return;
	}

	if (!InterruptR->Enabled() || !SpellManager::R->IsReady())
	{
		return;
	}

	for (auto hero : GEntityList->GetAllHeros(true, false))
	{
		if (hero != nullptr && hero->IsValidObject() && !hero->IsDead() && SpellManager::InRange(SpellManager::R, hero) && Utility::d(hero, caster) < 350 && SpellManager::R->CastOnUnit(hero))
		{
			return;
		}
	}
}

void OnGapCloser(GapCloserSpell* spell)
{
	if (!GapcloserW->Enabled() || !SpellManager::W->IsReady())
	{
		return;
	}

	auto data = spell->Data;
	auto caster = GSpellData->GetCaster(data);

	if (player->IsValidTarget(caster, SpellManager::W->Range()))
	{
		SpellManager::W->CastOnUnit(caster);
	}
}

void Combo()
{
	auto targ = GTargetSelector->FindTarget(LeastCasts, SpellDamage, SpellManager::Q->Range());
	auto target = targ != nullptr ? targ : Pix::GetTarget(false);

	if (target == nullptr)
	{
		PixLogic(target);
		return;
	}

	if (!player->IsValidTarget(target, SpellManager::Q->Range()))
	{
		PixLogic(target);
		return;
	}

	if (ComboQ->Enabled() && SpellManager::Q->IsReady())
	{
		if (SpellManager::InRange(SpellManager::Q, target) && SpellManager::Q->CastOnTarget(target))
		{
			GUtility->LogConsole("Q");
			return;
		}

		if (PixQ->Enabled() && Pix::IsPixValid() && Utility::d(target, Pix::GetPix()) < SpellManager::Q->Range() && SpellManager::Pix->CastOnTarget(target))
		{
			GUtility->LogConsole("[Pix] Q");
		}
	}
}

bool Farm()
{
	if (!FarmQ->Enabled() || !SpellManager::Q->IsReady())
	{
		return false;
	}

	auto pred = SpellManager::GetAoePrediction(SpellManager::Q, true, true);
	return pred.second >= 3 && SpellManager::Q->CastOnPosition(pred.first);
}

PLUGIN_EVENT(void) OnUpdate()
{
	if (player->IsDead())
	{
		return;
	}

	if (SpellManager::R->IsReady())
	{
		if (SmartR->Enabled())
		{
			int bHealth[] = {300, 450, 600};
			auto bonus = bHealth[player->GetSpellLevel(kSlotR)] + player->TotalMagicDamage() / 2.f;

			for (auto hero : GEntityList->GetAllHeros(true, false))
			{
				if (hero != nullptr && hero->IsValidObject() && !hero->IsDead() && SpellManager::InRange(SpellManager::R, hero))
				{
					auto dmg = damage->getIncomingDamage(hero);
					if (dmg == 0.f)
					{
						continue;
					}
					GUtility->LogConsole(std::to_string(dmg).c_str());
					if (dmg > hero->GetHealth() && dmg < hero->GetHealth() + bonus && SpellManager::R->CastOnUnit(hero))
					{
						return;
					}
				}
			}
		}

		if (KnockupR->Enabled())
		{
			auto count = KnockupRCount->GetInteger();
			for (auto ally : GEntityList->GetAllHeros(true, false))
			{
				if (ally != nullptr && ally->IsValidObject() && !ally->IsDead() && SpellManager::InRange(SpellManager::R, ally) && Utility::CountEnemiesInRange(ally, 350) >= count && SpellManager::R->CastOnUnit(ally))
				{
					return;
				}
			}
		}
	}

	switch (GOrbwalking->GetOrbwalkingMode())
	{
	case kModeCombo:
	case kModeMixed:
		Combo();
		break;
	case kModeLaneClear:
		Farm();
		break;
	}
}

PLUGIN_EVENT(void)OnRender()
{
	auto pos = player->GetPosition();
	for (auto pair : drawMap)
	{
		if (pair.first->Enabled() && pair.second->IsReady())
		{
			GRender->DrawCircle(pos, pair.second->Range(), Vec4(128, 0, 128, 255));
		}
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	Menu = GPluginSDK->AddMenu("LuluLicious");

	QMenu = Menu->AddMenu("Q");
	ComboQ = QMenu->CheckBox("Use in Combo\\Harass", true);
	FarmQ = QMenu->CheckBox("Use in Farm", true);

	WMenu = Menu->AddMenu("W");
	InterruptW = WMenu->CheckBox("Use to Interrupt", true);
	GapcloserW = WMenu->CheckBox("Use on Gapcloser", true);

	RMenu = Menu->AddMenu("R");
	SmartR = RMenu->CheckBox("Smart R to Save (WIP)", true);
	KnockupR = RMenu->CheckBox("Knockup with R", true);
	KnockupRCount = RMenu->AddInteger("Min Enemies to Knockup", 1, 5, 2);
	InterruptR = RMenu->CheckBox("Use to Interrupt", true);

	PixMenu = Menu->AddMenu("Pix");
	PixQ = PixMenu->CheckBox("Use Q with Pix", true);
	PixEQ = PixMenu->CheckBox("Use EQ with Pix", true);
	PixHarass = PixMenu->CheckBox("Use in Harass", true);

	DrawMenu = Menu->AddMenu("Draw");
	DrawQ = DrawMenu->CheckBox("Draw Q", true);
	DrawW = DrawMenu->CheckBox("Draw W", false);
	DrawR = DrawMenu->CheckBox("Draw R", false);
	DrawPix = DrawMenu->CheckBox("Draw Pix", true);

	SpellManager::Initialize(PluginSDK);

	std::map<ISpell2*, IMenuOption*> combo;
	combo.insert(std::make_pair(SpellManager::Q, ComboQ));
	SpellManager::SetMap(kModeCombo, combo);


	std::map<ISpell2*, IMenuOption*> harass;
	harass.insert(std::make_pair(SpellManager::Q, HarassQ));
	SpellManager::SetMap(kModeMixed, harass);

	drawMap.insert(std::make_pair(DrawQ, SpellManager::Q));
	drawMap.insert(std::make_pair(DrawW, SpellManager::W));
	drawMap.insert(std::make_pair(DrawR, SpellManager::R));

	Pix::Initialize(SpellManager::Pix, DrawPix);

	player = GEntityList->Player();

	eventmanager::RegisterEvents(PluginSDK->GetEventManager());
	damage = new DamageTracker(PluginSDK);

	GUtility->CreateDebugConsole();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnUpdate);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
}

PLUGIN_API void OnUnload()
{
	Pix::Unload();
	Menu->Remove();
	delete damage;

	eventmanager::UnregisterEvents(GPluginSDK->GetEventManager());
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
}
