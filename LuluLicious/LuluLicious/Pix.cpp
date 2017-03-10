#include "Pix.h"
#include "PluginSDK.h"
#include "Utility.h"
#include "SpellManager.h"


IUnit* Pix::pix;
IUnit* Pix::player;
ISpell2* Pix::pixQ;
IMenuOption* Pix::draw;
std::vector<int> goodTypes{FL_HERO, FL_CREEP};

PLUGIN_EVENTD(void) Pix::OnGameUpdate()
{
	UpdatePix();
}

void Pix::Initialize(ISpell2* spell, IMenuOption* draw)
{
	Pix::pixQ = spell;
	Pix::draw = draw;
	player = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
}

PLUGIN_EVENTD(void) Pix::OnRender()
{
	if (draw->Enabled() && IsPixValid())
	{
		GRender->DrawCircle(pix->GetPosition(), 50, Vec4(128, 0, 128, 255));
	}
}

void Pix::Unload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
}

bool Pix::IsPixValid()
{
	return pix != nullptr && pix->IsValidObject() && Utility::d(pix, player) < 1900;
}

IUnit* Pix::GetPix()
{
	return pix;
}

IUnit* Pix::GetTarget(boolean eReady)
{
	if (!IsPixValid())
	{
		return nullptr;
	}

	auto pos = pix->ServerPosition();
	return GTargetSelector->FindTargetEx(QuickestKill, SpellDamage, pixQ->Range() + (eReady ? 600 : 0), &pos);
}

IUnit* Pix::GetETarget(IUnit* target)
{
	auto delay = SpellManager::E->GetDelay();
	for (auto obj : GEntityList->GetAllUnits())
	{
		if (obj != nullptr && obj->IsValidObject() && !obj->GetNetworkId() == player->GetNetworkId() && Utility::IsCastableType(obj) && Utility::d(obj, player) < 600)
		{
			//Vec3 targPos;
			//Vec3 unitPos;
			//GPrediction->GetFutureUnitPosition(obj, delay, true, unitPos);
			//GPrediction->GetFutureUnitPosition(target, delay + SpellManager::Q->GetDelay(), true, targPos);

			if (Utility::d(obj, target) > SpellManager::Q->Range())//Utility::d(unitPos, targPos) > 925)
			{
				continue;
			}

			if (!Utility::IsAlly(obj))
			{
				//auto health = GHealthPrediction->GetPredictedHealth(obj, kLastHitPrediction, 1000.f * (SpellManager::E->GetDelay() + SpellManager::Q->GetDelay()), 50);
				if (obj->GetHealth() - SpellManager::GetDamage(SpellManager::E, obj) <= 0)
				{
					continue;
				}
			}
			return obj;
		}
	}

	return nullptr;
}

void Pix::UpdatePix()
{
	if (IsPixValid())
	{
		pixQ->SetRangeCheckFrom(pix->ServerPosition());
		return;
	}

	for (auto obj : GEntityList->GetAllUnits())
	{
		if (obj != nullptr && obj->IsValidObject() && Utility::IsAlly(obj) && strcmp(obj->GetObjectName(), "RobotBuddy") == 0)
		{
			pix = obj;
			pixQ->SetRangeCheckFrom(pix->ServerPosition());
			return;
		}
	}

	pix = nullptr;
}
