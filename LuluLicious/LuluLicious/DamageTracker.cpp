#include "DamageTracker.h"
#include "EventManager.h"
#include "lpputils.h"

DamageTracker::DamageTracker(IPluginSDK* sdk, bool trackSkillshots) : sdk(sdk), trackSkillshots(trackSkillshots)
{
	static auto game = this->sdk->GetGame();
	static auto spellDataReader = this->sdk->GetSpellDataReader();
	static auto entityList = this->sdk->GetEntityList();
	static auto damageCalc = this->sdk->GetDamage();
	static auto prediction = this->sdk->GetPrediction();

	for (auto unit : entityList->GetAllHeros(true, true))
	{
		this->damage[unit->GetNetworkId()] = 0.f;
	}

	eventmanager::GameEventManager::RegisterUpdateEvent([&](event_id_t) -> void
		{
			for (auto pair : this->damage)
			{
				this->damage[pair.first] = max(0.f, pair.second);
			}
		});

	eventmanager::UnitEventManager::RegisterDoCastEvent(
		[&](event_id_t id, const CastedSpell& spell) -> void
		{
			auto source = spellDataReader->GetCaster(spell.Data_);
			auto target = spellDataReader->GetTarget(spell.Data_);

			if (spellDataReader->IsAutoAttack(spell.Data_) && (source->IsHero() || source->IsTurret()) && target != nullptr && target->IsHero())
			{
				auto networkId = target->GetNetworkId();

				auto dmg = static_cast<float>(damageCalc->GetAutoAttackDamage(source, target, true));

				this->damage[networkId] += dmg;

				auto delay = spellDataReader->GetWindupTime(spell.Data_);

				if (!source->IsMelee())
				{
					delay += (target->GetPosition() - source->GetPosition()).Length() / spellDataReader->GetSpeed(spell.Data_);
				}

				LPPUtils::DelayActionGame(this->sdk, [&, networkId, dmg]() -> void
				                          {
					                          this->damage[networkId] = max(0.f, this->damage[networkId] - dmg);
				                          }, delay);
			}
		});

	eventmanager::UnitEventManager::RegisterProcessSpellCastEvent(
		[&](event_id_t id, const CastedSpell& spell) -> void
		{
			auto source = spellDataReader->GetCaster(spell.Data_);
			if (source->IsHero() || source->IsTurret())
			{
				auto sourcePos = source->GetPosition();

				auto target = spellDataReader->GetTarget(spell.Data_);

				auto start = spellDataReader->GetStartPosition(spell.Data_);
				auto end = spellDataReader->GetEndPosition(spell.Data_);

				auto range = spellDataReader->GetRange(spell.Data_);

				if ((sourcePos - end).Length() > range)
				{
					end = LPPUtils::Extend(sourcePos, end, range);
				}

				if (!spellDataReader->IsAutoAttack(spell.Data_))
				{
					auto slot = spellDataReader->GetSlot(spell.Data_);
					if (slot != kSlotUnknown)
					{
						if (spellDataReader->GetBaseDamage(spell.Data_) > 0.f)
						{
							if (target != nullptr && target->IsHero())
							{
								auto networkId = target->GetNetworkId();

								auto dmg = static_cast<float>(damageCalc->GetSpellDamage(source, target, slot));

								this->damage[networkId] += dmg;

								auto delay = spellDataReader->GetWindupTime(spell.Data_);
								auto speed = spellDataReader->GetSpeed(spell.Data_);

								if (speed > 500.f)
								{
									delay += (target->GetPosition() - source->GetPosition()).Length() / speed;
								}

								LPPUtils::DelayActionGame(this->sdk, [&, networkId, dmg]() -> void
								                          {
									                          this->damage[networkId] = max(0.f, this->damage[networkId] - dmg);
								                          }, delay);
							}
							else if (this->trackSkillshots)
							{
								auto angle = spellDataReader->CastConeAngle(spell.Data_);
								auto radius = spellDataReader->GetRadius(spell.Data_);

								for (auto unit : entityList->GetAllHeros(true, true))
								{
									if (unit->IsEnemy(source) && unit->IsVisible())
									{
										auto delay = spellDataReader->GetWindupTime(spell.Data_);
										auto speed = spellDataReader->GetSpeed(spell.Data_);

										if (speed > 500.f)
										{
											delay += (end - start).Length() / speed;
										}

										Vec3 pos;
										prediction->GetFutureUnitPosition(unit, delay, true, pos);

										if ((pos - start).Length() <= range)
										{
											if (radius == 210.f)
											{
												//broscience for the win
												radius = 100.f;
											}

											auto distnace = (pos - end).Length();
											auto fixedEnd = LPPUtils::Extend(source->GetPosition(), end, distnace);

											if ((radius != 210.f && (pos - fixedEnd).Length() <= radius)
												|| (angle != 90.f && static_cast<float>(LPPUtils::AngleBetween(pos, end)) <= angle))
											{
												auto networkId = unit->GetNetworkId();
												auto dmg = static_cast<float>(damageCalc->GetSpellDamage(source, unit, slot));

												this->damage[networkId] += dmg;

												LPPUtils::DelayActionGame(this->sdk, [&, networkId, dmg]() -> void
												                          {
													                          this->damage[networkId] = max(0.f, this->damage[networkId] - dmg);
												                          }, delay);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		});
}

float DamageTracker::getIncomingDamage(IUnit* unit) const
{
	auto networkId = unit->GetNetworkId();

	if (this->damage.count(networkId))
	{
		return this->damage.at(networkId);
	}

	return 0.f;
}

float DamageTracker::getIncomingDamagePercent(IUnit* unit) const
{
	return (this->getIncomingDamage(unit) / unit->GetHealth()) * 100.f;
}

bool DamageTracker::hasIncomingDamage(IUnit* unit) const
{
	return this->getIncomingDamage(unit) > 0.f;
}

bool DamageTracker::hasIncomingLethalDamage(IUnit* unit, float& extraDamage) const
{
	extraDamage = this->getIncomingDamage(unit) - unit->GetHealth();
	return extraDamage >= 0.f;
}
