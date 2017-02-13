#include "PluginSDK.h"

PluginSetup("AutoLantern - Trees");

IMenu* Menu;

ISpell2* LanternSpell;

IUnit* Player;

bool IsLow()
{
	return Player->HealthPercent() <= Menu->GetOption("Low HP%")->GetFloat();
}

bool ThreshInGame()
{
	auto me = GEntityList->Player()->GetNetworkId();
	for (auto champion : GEntityList->GetAllHeros(true, false))
	{
		if (champion->GetNetworkId() != me && champion->ChampionName() == "Thresh")
		{
			return true;
		}
	}
	return false;
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!Menu->GetOption("Enabled")->Enabled())
	{
		return;
	}

	if (Player->IsDead() || !Player->GetSpellBook()->IsValidSpell(62) || !LanternSpell->IsReady() || Player->GetSpellSlot("LanternWAlly") == kSlotUnknown)
	{
		return;
	}

	if (IsLow() || Menu->GetOption("Hotkey")->Enabled())
	{
		for (auto obj : GEntityList->GetAllUnits())
		{
			if (obj != nullptr && obj->GetTeam() == Player->GetTeam() && obj->GetObjectName() == "ThreshLantern" && (obj->ServerPosition() - Player->ServerPosition()).Length() <= 500 && LanternSpell->CastOnUnit(obj))
			{
				return;
			}
		}
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	if (!ThreshInGame())
	{
		return;
	}

	Menu = GPluginSDK->AddMenu("Trees AutoLantern");
	Menu->CheckBox("Enabled", true);
	Menu->AddKey("Hotkey", 32);
	Menu->AddInteger("Low HP%", 0, 50, 20);

	Player = GEntityList->Player();
	LanternSpell = GPluginSDK->CreateSpell2(static_cast<eSpellSlot>(62), kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
}

PLUGIN_API void OnUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Menu->Remove();
}

