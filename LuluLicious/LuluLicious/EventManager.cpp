#include "EventManager.h"
#include "lpputils.h"

namespace eventmanager
{
	/**
	* OrbwalkerEventManager
	*/
	static std::vector<std::function<void(event_id_t, IUnit*)>> beforeAttackHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, IUnit*)>> attackHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, IUnit*)>> afterAttackHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, IUnit*)>> newTargetHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> nonKillableMinionHandlers;
	static std::vector<std::function<IUnit *(event_id_t)>> findTargetHandlers;

	event_id_t OrbwalkerEventManager::RegisterBeforeAttackEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		beforeAttackHandlers.push_back(func);

		return static_cast<event_id_t>(beforeAttackHandlers.size() - 1);
	}

	event_id_t OrbwalkerEventManager::RegisterAttackEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func)
	{
		attackHandlers.push_back(func);

		return static_cast<event_id_t>(attackHandlers.size() - 1);
	}

	event_id_t OrbwalkerEventManager::RegisterAfterAttackEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func)
	{
		afterAttackHandlers.push_back(func);

		return static_cast<event_id_t>(afterAttackHandlers.size() - 1);
	}

	event_id_t OrbwalkerEventManager::RegisterNewTargetEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func)
	{
		newTargetHandlers.push_back(func);

		return static_cast<event_id_t>(newTargetHandlers.size() - 1);
	}

	event_id_t OrbwalkerEventManager::RegisterNonKillableMinionEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		nonKillableMinionHandlers.push_back(func);

		return static_cast<event_id_t>(nonKillableMinionHandlers.size() - 1);
	}

	event_id_t OrbwalkerEventManager::RegisterFindTargetEvent(std::function<IUnit *(event_id_t)> func)
	{
		findTargetHandlers.push_back(func);

		return static_cast<event_id_t>(findTargetHandlers.size() - 1);
	}

	void OrbwalkerEventManager::UnregisterBeforeAttackEvent(event_id_t id)
	{
		if (id < beforeAttackHandlers.size())
		{
			beforeAttackHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void OrbwalkerEventManager::UnregisterAttackEvent(event_id_t id)
	{
		if (id < attackHandlers.size())
		{
			attackHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void OrbwalkerEventManager::UnregisterAfterAttackEvent(event_id_t id)
	{
		if (id < afterAttackHandlers.size())
		{
			afterAttackHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void OrbwalkerEventManager::UnregisterNewTargetEvent(event_id_t id)
	{
		if (id < newTargetHandlers.size())
		{
			newTargetHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void OrbwalkerEventManager::UnregisterNonKillableMinionEvent(event_id_t id)
	{
		if (id < nonKillableMinionHandlers.size())
		{
			nonKillableMinionHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void OrbwalkerEventManager::UnregisterFindTargetEvent(event_id_t id)
	{
		if (id < findTargetHandlers.size())
		{
			findTargetHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	/**
	* GameEventManager
	*/
	static std::vector<std::function<void(event_id_t)>> updateHandlers;
	static std::vector<std::function<void(event_id_t)>> endHandlers;
	static std::vector<std::function<bool(event_id_t, HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)>> wndProcHandlers;
	static std::vector<std::function<void(event_id_t, JungleNotifyData*)>> jungleNotifyHandlers;

	event_id_t GameEventManager::RegisterUpdateEvent(std::function<void(event_id_t)> func)
	{
		updateHandlers.push_back(func);

		return static_cast<event_id_t>(updateHandlers.size() - 1);
	}

	event_id_t GameEventManager::RegisterEndEvent(std::function<void(event_id_t)> func)
	{
		endHandlers.push_back(func);

		return static_cast<event_id_t>(endHandlers.size() - 1);
	}

	event_id_t GameEventManager::RegisterWndProcEvent(std::function<bool(event_id_t, HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)> func)
	{
		wndProcHandlers.push_back(func);

		return static_cast<event_id_t>(wndProcHandlers.size() - 1);
	}

	event_id_t GameEventManager::RegisterJungleNotifyEvent(std::function<void(event_id_t, JungleNotifyData*)> func)
	{
		jungleNotifyHandlers.push_back(func);

		return static_cast<event_id_t>(jungleNotifyHandlers.size() - 1);
	}

	void GameEventManager::UnregisterUpdateEvent(event_id_t id)
	{
		if (id < updateHandlers.size())
		{
			updateHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void GameEventManager::UnregisterEndEvent(event_id_t id)
	{
		if (id < endHandlers.size())
		{
			endHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void GameEventManager::UnregisterWndProcEvent(event_id_t id)
	{
		if (id < wndProcHandlers.size())
		{
			wndProcHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void GameEventManager::UnregisterJungleNotifyEvent(event_id_t id)
	{
		if (id < jungleNotifyHandlers.size())
		{
			jungleNotifyHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	/**
	* DrawEventManager
	*/
	static std::vector<std::function<void(event_id_t)>> renderHandlers;
	static std::vector<std::function<void(event_id_t)>> renderBehindHudEventHandlers;
	static std::vector<std::function<void(event_id_t)>> D3DPresentEventHandlers;
	static std::vector<std::function<void(event_id_t)>> D3DPreResetEventHandlers;
	static std::vector<std::function<void(event_id_t)>> D3DPostResetEventHandlers;

	event_id_t DrawEventManager::RegisterRenderEvent(std::function<void(event_id_t)> func)
	{
		renderHandlers.push_back(func);

		return static_cast<event_id_t>(renderHandlers.size() - 1);
	}

	event_id_t DrawEventManager::RegisterRenderBehindHudEvent(std::function<void(event_id_t)> func)
	{
		renderBehindHudEventHandlers.push_back(func);

		return static_cast<event_id_t>(renderBehindHudEventHandlers.size() - 1);
	}

	event_id_t DrawEventManager::RegisterD3DPresentEvent(std::function<void(event_id_t)> func)
	{
		D3DPresentEventHandlers.push_back(func);

		return static_cast<event_id_t>(D3DPresentEventHandlers.size() - 1);
	}

	event_id_t DrawEventManager::RegisterD3DPreResetEvent(std::function<void(event_id_t)> func)
	{
		D3DPreResetEventHandlers.push_back(func);

		return static_cast<event_id_t>(D3DPreResetEventHandlers.size() - 1);
	}

	event_id_t DrawEventManager::RegisterD3DPostResetEvent(std::function<void(event_id_t)> func)
	{
		D3DPostResetEventHandlers.push_back(func);

		return static_cast<event_id_t>(D3DPostResetEventHandlers.size() - 1);
	}

	void DrawEventManager::UnregisterRenderEvent(event_id_t id)
	{
		if (id < renderHandlers.size())
		{
			renderHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void DrawEventManager::UnregisterRenderBehindHudEvent(event_id_t id)
	{
		if (id < renderBehindHudEventHandlers.size())
		{
			renderBehindHudEventHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void DrawEventManager::UnregisterD3DPresentEvent(event_id_t id)
	{
		if (id < D3DPresentEventHandlers.size())
		{
			D3DPresentEventHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void DrawEventManager::UnregisterD3DPreResetEvent(event_id_t id)
	{
		if (id < D3DPreResetEventHandlers.size())
		{
			D3DPreResetEventHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void DrawEventManager::UnregisterD3DPostResetEvent(event_id_t id)
	{
		if (id < D3DPostResetEventHandlers.size())
		{
			D3DPostResetEventHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	/**
	* UnitEventManager
	*/
	static std::vector<std::function<void(event_id_t, IUnit*)>> createHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> destroyHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> deathHandlers;
	static std::vector<std::function<bool(event_id_t, IUnit*, int, Vec3*, IUnit*)>> issueOrderHandlers;
	static std::vector<std::function<bool(event_id_t, int, IUnit*, Vec3*, Vec3*)>> preCastHandlers;
	static std::vector<std::function<void(event_id_t, int, Vec3*, bool*, bool*)>> updateChargedSpellHandlers;
	static std::vector<std::function<void(event_id_t, CastedSpell const&)>> processSpellCastHandlers;
	static std::vector<std::function<void(event_id_t, CastedSpell const&)>> doCastHandlers;
	static std::vector<std::function<void(event_id_t, InterruptibleSpell const&)>> processInterruptibleSpellHandlers;
	static std::vector<std::function<void(event_id_t, GapCloserSpell const&)>> processGapCloserSpellHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, void*)>> buffAddHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, void*)>> buffRemoveHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, int)>> levelUpHandlers;
	static std::vector<std::function<void(event_id_t, UnitDash*)>> dashHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> enterVisibilityHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> exitVisibilityHandlers;
	static std::vector<std::function<bool(event_id_t, IUnit*, std::string const)>> playAnimationHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*)>> pauseAnimationHandlers;
	static std::vector<std::function<void(event_id_t, IUnit*, std::vector<Vec3> const&)>> newPathEventHandlers;


	event_id_t UnitEventManager::RegisterCreateEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		createHandlers.push_back(func);

		return static_cast<event_id_t>(createHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterDestroyEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		destroyHandlers.push_back(func);

		return static_cast<event_id_t>(destroyHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterDeathEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		deathHandlers.push_back(func);

		return static_cast<event_id_t>(deathHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterIssueOrderEvent(std::function<bool(event_id_t, IUnit*, int, Vec3*, IUnit*)> func)
	{
		issueOrderHandlers.push_back(func);

		return static_cast<event_id_t>(issueOrderHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterPreCastEvent(std::function<bool(event_id_t, int, IUnit*, Vec3*, Vec3*)> func)
	{
		preCastHandlers.push_back(func);

		return static_cast<event_id_t>(preCastHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterUpdateChargedSpellEvent(std::function<void(event_id_t, int, Vec3*, bool*, bool*)> func)
	{
		updateChargedSpellHandlers.push_back(func);

		return static_cast<event_id_t>(updateChargedSpellHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterProcessSpellCastEvent(std::function<void(event_id_t, CastedSpell const&)> func)
	{
		processSpellCastHandlers.push_back(func);

		return static_cast<event_id_t>(processSpellCastHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterDoCastEvent(std::function<void(event_id_t, CastedSpell const&)> func)
	{
		doCastHandlers.push_back(func);

		return static_cast<event_id_t>(doCastHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterProcessInterruptibleSpellEvent(std::function<void(event_id_t, InterruptibleSpell const&)> func)
	{
		processInterruptibleSpellHandlers.push_back(func);

		return static_cast<event_id_t>(processInterruptibleSpellHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterProcessGapCloserSpellEvent(std::function<void(event_id_t, GapCloserSpell const&)> func)
	{
		processGapCloserSpellHandlers.push_back(func);

		return static_cast<event_id_t>(processGapCloserSpellHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterBuffAddEvent(std::function<void(event_id_t, IUnit*, void*)> func)
	{
		buffAddHandlers.push_back(func);

		return static_cast<event_id_t>(buffAddHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterBuffRemoveEvent(std::function<void(event_id_t, IUnit*, void*)> func)
	{
		buffRemoveHandlers.push_back(func);

		return static_cast<event_id_t>(buffRemoveHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterLevelUpEvent(std::function<void(event_id_t, IUnit*, int)> func)
	{
		levelUpHandlers.push_back(func);

		return static_cast<event_id_t>(levelUpHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterDashEvent(std::function<void(event_id_t, UnitDash*)> func)
	{
		dashHandlers.push_back(func);

		return static_cast<event_id_t>(dashHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterEnterVisibilityEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		enterVisibilityHandlers.push_back(func);

		return static_cast<event_id_t>(enterVisibilityHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterExitVisibilityEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		exitVisibilityHandlers.push_back(func);

		return static_cast<event_id_t>(exitVisibilityHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterPlayAnimationEvent(std::function<bool(event_id_t, IUnit*, std::string const)> func)
	{
		playAnimationHandlers.push_back(func);

		return static_cast<event_id_t>(playAnimationHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterPauseAnimationEvent(std::function<void(event_id_t, IUnit*)> func)
	{
		pauseAnimationHandlers.push_back(func);

		return static_cast<event_id_t>(pauseAnimationHandlers.size() - 1);
	}

	event_id_t UnitEventManager::RegisterNewPathEvent(std::function<void(event_id_t, IUnit*, std::vector<Vec3> const&)> func)
	{
		newPathEventHandlers.push_back(func);

		return static_cast<event_id_t>(newPathEventHandlers.size() - 1);
	}

	void UnitEventManager::UnregisterCreateEvent(event_id_t id)
	{
		if (id < createHandlers.size())
		{
			createHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterDestroyEvent(event_id_t id)
	{
		if (id < destroyHandlers.size())
		{
			destroyHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterDeathEvent(event_id_t id)
	{
		if (id < deathHandlers.size())
		{
			deathHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterIssueOrderEvent(event_id_t id)
	{
		if (id < issueOrderHandlers.size())
		{
			issueOrderHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterPreCastEvent(event_id_t id)
	{
		if (id < preCastHandlers.size())
		{
			preCastHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterUpdateChargedSpellEvent(event_id_t id)
	{
		if (id < updateChargedSpellHandlers.size())
		{
			updateChargedSpellHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterProcessSpellCastEvent(event_id_t id)
	{
		if (id < processSpellCastHandlers.size())
		{
			processSpellCastHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterDoCastEvent(event_id_t id)
	{
		if (id < doCastHandlers.size())
		{
			doCastHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterProcessInterruptibleSpellEvent(event_id_t id)
	{
		if (id < processInterruptibleSpellHandlers.size())
		{
			processInterruptibleSpellHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterProcessGapCloserSpellEvent(event_id_t id)
	{
		if (id < processGapCloserSpellHandlers.size())
		{
			processGapCloserSpellHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterBuffAddEvent(event_id_t id)
	{
		if (id < buffAddHandlers.size())
		{
			buffAddHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterBuffRemoveEvent(event_id_t id)
	{
		if (id < buffRemoveHandlers.size())
		{
			buffRemoveHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterLevelUpEvent(event_id_t id)
	{
		if (id < levelUpHandlers.size())
		{
			levelUpHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterDashEvent(event_id_t id)
	{
		if (id < dashHandlers.size())
		{
			dashHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterEnterVisibilityEvent(event_id_t id)
	{
		if (id < enterVisibilityHandlers.size())
		{
			enterVisibilityHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterExitVisibilityEvent(event_id_t id)
	{
		if (id < exitVisibilityHandlers.size())
		{
			exitVisibilityHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterPlayAnimationEvent(event_id_t id)
	{
		if (id < playAnimationHandlers.size())
		{
			playAnimationHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterPauseAnimationEvent(event_id_t id)
	{
		if (id < pauseAnimationHandlers.size())
		{
			pauseAnimationHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	void UnitEventManager::UnregisterNewPathEvent(event_id_t id)
	{
		if (id < newPathEventHandlers.size())
		{
			newPathEventHandlers[static_cast<unsigned int>(id)] = nullptr;
		}
	}

	PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* target)
	{
		for (event_id_t i = 0; i < beforeAttackHandlers.size(); i++)
		{
			if (beforeAttackHandlers[i] != nullptr)
			{
				beforeAttackHandlers[i](i, target);
			}
		}
	}

	PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* source, IUnit* target)
	{
		for (event_id_t i = 0; i < attackHandlers.size(); i++)
		{
			if (attackHandlers[i] != nullptr)
			{
				attackHandlers[i](i, source, target);
			}
		}
	}

	PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* source, IUnit* target)
	{
		for (event_id_t i = 0; i < afterAttackHandlers.size(); i++)
		{
			if (afterAttackHandlers[i] != nullptr)
			{
				afterAttackHandlers[i](i, source, target);
			}
		}
	}

	PLUGIN_EVENT(void) OnOrbwalkTargetChange(IUnit* oldTarget, IUnit* newTarget)
	{
		for (event_id_t i = 0; i < newTargetHandlers.size(); i++)
		{
			if (newTargetHandlers[i] != nullptr)
			{
				newTargetHandlers[i](i, oldTarget, newTarget);
			}
		}
	}

	PLUGIN_EVENT(void) OnOrbwalkOrbwalkNonKillableMinion(IUnit* nonKillableMinion)
	{
		for (event_id_t i = 0; i < nonKillableMinionHandlers.size(); i++)
		{
			if (nonKillableMinionHandlers[i] != nullptr)
			{
				nonKillableMinionHandlers[i](i, nonKillableMinion);
			}
		}
	}

	PLUGIN_EVENT(IUnit *) OnOrbwalkFindTarget()
	{
		IUnit* target = nullptr;

		for (event_id_t i = 0; i < findTargetHandlers.size(); i++)
		{
			if (findTargetHandlers[i] != nullptr)
			{
				auto ret = findTargetHandlers[i](i);

				if (ret != nullptr && target == nullptr)
				{
					target = nullptr;
				}
			}
		}

		return target;
	}

	PLUGIN_EVENT(void) OnGameUpdate()
	{
		for (event_id_t i = 0; i < updateHandlers.size(); i++)
		{
			if (updateHandlers[i] != nullptr)
			{
				updateHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnGameEnd()
	{
		for (event_id_t i = 0; i < endHandlers.size(); i++)
		{
			if (endHandlers[i] != nullptr)
			{
				endHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(bool) OnGameWndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto ret = true;

		for (event_id_t i = 0; i < wndProcHandlers.size(); i++)
		{
			if (wndProcHandlers[i] != nullptr)
			{
				auto r = wndProcHandlers[i](i, wnd, message, wParam, lParam);

				if (!r && ret)
				{
					ret = false;
				}
			}
		}

		return ret;
	}

	PLUGIN_EVENT(void) OnJungleNotify(JungleNotifyData* args)
	{
		for (event_id_t i = 0; i < jungleNotifyHandlers.size(); i++)
		{
			if (jungleNotifyHandlers[i] != nullptr)
			{
				jungleNotifyHandlers[i](i, args);
			}
		}
	}

	PLUGIN_EVENT(void) OnDrawRender()
	{
		for (event_id_t i = 0; i < renderHandlers.size(); i++)
		{
			if (renderHandlers[i] != nullptr)
			{
				renderHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnDrawRenderBehindHud()
	{
		for (event_id_t i = 0; i < renderBehindHudEventHandlers.size(); i++)
		{
			if (renderBehindHudEventHandlers[i] != nullptr)
			{
				renderBehindHudEventHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnDrawRenderD3DPresent()
	{
		for (event_id_t i = 0; i < D3DPresentEventHandlers.size(); i++)
		{
			if (D3DPresentEventHandlers[i] != nullptr)
			{
				D3DPresentEventHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnDrawRenderD3DPreReset()
	{
		for (event_id_t i = 0; i < D3DPreResetEventHandlers.size(); i++)
		{
			if (D3DPreResetEventHandlers[i] != nullptr)
			{
				D3DPreResetEventHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnDrawRenderD3DPostReset()
	{
		for (event_id_t i = 0; i < D3DPostResetEventHandlers.size(); i++)
		{
			if (D3DPostResetEventHandlers[i] != nullptr)
			{
				D3DPostResetEventHandlers[i](i);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitCreate(IUnit* unit)
	{
		for (event_id_t i = 0; i < createHandlers.size(); i++)
		{
			if (createHandlers[i] != nullptr)
			{
				createHandlers[i](i, unit);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitDestroy(IUnit* unit)
	{
		for (event_id_t i = 0; i < destroyHandlers.size(); i++)
		{
			if (destroyHandlers[i] != nullptr)
			{
				destroyHandlers[i](i, unit);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitDeath(IUnit* unit)
	{
		for (event_id_t i = 0; i < deathHandlers.size(); i++)
		{
			if (deathHandlers[i] != nullptr)
			{
				deathHandlers[i](i, unit);
			}
		}
	}

	PLUGIN_EVENT(bool) OnUnitIssueOrder(IUnit* source, int orderId, Vec3* pos, IUnit* target)
	{
		auto process = true;

		for (event_id_t i = 0; i < issueOrderHandlers.size(); i++)
		{
			if (issueOrderHandlers[i] != nullptr)
			{
				auto ret = issueOrderHandlers[i](i, source, orderId, pos, target);

				if (!ret && process)
				{
					process = false;
				}
			}
		}

		return process;
	}

	PLUGIN_EVENT(bool) OnUnitPreCast(int slot, IUnit* target, Vec3* start, Vec3* end)
	{
		auto process = true;

		for (event_id_t i = 0; i < preCastHandlers.size(); i++)
		{
			if (preCastHandlers[i] != nullptr)
			{
				auto ret = preCastHandlers[i](i, slot, target, start, end);

				if (!ret && process)
				{
					process = false;
				}
			}
		}

		return process;
	}

	PLUGIN_EVENT(void) OnUnitUpdateChargedSpell(int slot, Vec3* position, bool* releaseCast, bool* triggerEvent)
	{
		for (event_id_t i = 0; i < updateChargedSpellHandlers.size(); i++)
		{
			if (updateChargedSpellHandlers[i] != nullptr)
			{
				updateChargedSpellHandlers[i](i, slot, position, releaseCast, triggerEvent);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitProcessSpellCast(CastedSpell const& spell)
	{
		for (event_id_t i = 0; i < processSpellCastHandlers.size(); i++)
		{
			if (processSpellCastHandlers[i] != nullptr)
			{
				processSpellCastHandlers[i](i, spell);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitDoCast(CastedSpell const& spell)
	{
		for (event_id_t i = 0; i < doCastHandlers.size(); i++)
		{
			if (doCastHandlers[i] != nullptr)
			{
				doCastHandlers[i](i, spell);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitProcessInterruptableSpellCast(InterruptibleSpell const& spell)
	{
		for (event_id_t i = 0; i < processInterruptibleSpellHandlers.size(); i++)
		{
			if (processInterruptibleSpellHandlers[i] != nullptr)
			{
				processInterruptibleSpellHandlers[i](i, spell);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitProcessGapCloserSpellCast(GapCloserSpell const& spell)
	{
		for (event_id_t i = 0; i < processGapCloserSpellHandlers.size(); i++)
		{
			if (processGapCloserSpellHandlers[i] != nullptr)
			{
				processGapCloserSpellHandlers[i](i, spell);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitBuffAdd(IUnit* source, void* buffData)
	{
		for (event_id_t i = 0; i < buffAddHandlers.size(); i++)
		{
			if (buffAddHandlers[i] != nullptr)
			{
				buffAddHandlers[i](i, source, buffData);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitBuffRemove(IUnit* source, void* buffData)
	{
		for (event_id_t i = 0; i < buffRemoveHandlers.size(); i++)
		{
			if (buffRemoveHandlers[i] != nullptr)
			{
				buffRemoveHandlers[i](i, source, buffData);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitLevelUp(IUnit* source, int newLevel)
	{
		for (event_id_t i = 0; i < levelUpHandlers.size(); i++)
		{
			if (levelUpHandlers[i] != nullptr)
			{
				levelUpHandlers[i](i, source, newLevel);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitDash(UnitDash* dashArgs)
	{
		for (event_id_t i = 0; i < dashHandlers.size(); i++)
		{
			if (dashHandlers[i] != nullptr)
			{
				dashHandlers[i](i, dashArgs);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitEnterVisibility(IUnit* unit)
	{
		for (event_id_t i = 0; i < enterVisibilityHandlers.size(); i++)
		{
			if (enterVisibilityHandlers[i] != nullptr)
			{
				enterVisibilityHandlers[i](i, unit);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitExitVisibility(IUnit* unit)
	{
		for (event_id_t i = 0; i < exitVisibilityHandlers.size(); i++)
		{
			if (exitVisibilityHandlers[i] != nullptr)
			{
				exitVisibilityHandlers[i](i, unit);
			}
		}
	}

	PLUGIN_EVENT(bool) OnUnitPlayAnimation(IUnit* source, std::string const animationId)
	{
		auto process = true;

		for (event_id_t i = 0; i < playAnimationHandlers.size(); i++)
		{
			if (playAnimationHandlers[i] != nullptr)
			{
				auto ret = playAnimationHandlers[i](i, source, animationId);

				if (!ret && process)
				{
					process = false;
				}
			}
		}

		return process;
	}

	PLUGIN_EVENT(void) OnUnitPauseAnimation(IUnit* source)
	{
		for (event_id_t i = 0; i < pauseAnimationHandlers.size(); i++)
		{
			if (pauseAnimationHandlers[i] != nullptr)
			{
				pauseAnimationHandlers[i](i, source);
			}
		}
	}

	PLUGIN_EVENT(void) OnUnitNewPath(IUnit* source, std::vector<Vec3> const& path)
	{
		for (event_id_t i = 0; i < newPathEventHandlers.size(); i++)
		{
			if (newPathEventHandlers[i] != nullptr)
			{
				newPathEventHandlers[i](i, source, path);
			}
		}
	}

	void RegisterEvents(IEventManager* eventManager)
	{
		//Orbwalker Events
		eventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
		eventManager->AddEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
		eventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
		eventManager->AddEventHandler(kEventOrbwalkTargetChange, OnOrbwalkAfterAttack);
		eventManager->AddEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkOrbwalkNonKillableMinion);
		eventManager->AddEventHandler(kEventOrbwalkFindTarget, OnOrbwalkFindTarget);

		//Game Events
		eventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
		eventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
		eventManager->AddEventHandler(kEventOnWndProc, OnGameWndProc);
		eventManager->AddEventHandler(kEventOnJungleNotification, OnJungleNotify);

		//Draw Events
		eventManager->AddEventHandler(kEventOnRender, OnDrawRender);
		eventManager->AddEventHandler(kEventOnRenderBehindHud, OnDrawRenderBehindHud);
		eventManager->AddEventHandler(kEventOnD3DPresent, OnDrawRenderD3DPresent);
		eventManager->AddEventHandler(kEventOnD3DPreReset, OnDrawRenderD3DPreReset);
		eventManager->AddEventHandler(kEventOnD3DPostReset, OnDrawRenderD3DPostReset);

		//Unit Events
		eventManager->AddEventHandler(kEventOnCreateObject, OnUnitCreate);
		eventManager->AddEventHandler(kEventOnDestroyObject, OnUnitDestroy);
		eventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
		eventManager->AddEventHandler(kEventOnIssueOrder, OnUnitIssueOrder);
		eventManager->AddEventHandler(kEventOnPreCast, OnUnitPreCast);
		eventManager->AddEventHandler(kEventOnUpdateChargedSpell, OnUnitUpdateChargedSpell);
		eventManager->AddEventHandler(kEventOnSpellCast, OnUnitProcessSpellCast);
		eventManager->AddEventHandler(kEventOnDoCast, OnUnitDoCast);
		eventManager->AddEventHandler(kEventOnInterruptible, OnUnitProcessInterruptableSpellCast);
		eventManager->AddEventHandler(kEventOnGapCloser, OnUnitProcessGapCloserSpellCast);
		eventManager->AddEventHandler(kEventOnBuffAdd, OnUnitBuffAdd);
		eventManager->AddEventHandler(kEventOnBuffRemove, OnUnitBuffRemove);
		eventManager->AddEventHandler(kEventOnLevelUp, OnUnitLevelUp);
		eventManager->AddEventHandler(kEventOnDash, OnUnitDash);
		eventManager->AddEventHandler(kEventOnEnterVisible, OnUnitEnterVisibility);
		eventManager->AddEventHandler(kEventOnExitVisible, OnUnitExitVisibility);
		eventManager->AddEventHandler(kEventOnPlayAnimation, OnUnitPlayAnimation);
		eventManager->AddEventHandler(kEventOnPauseAnimation, OnUnitPauseAnimation);
		eventManager->AddEventHandler(kEventOnNewPath, OnUnitNewPath);
	}

	void UnregisterEvents(IEventManager* eventManager)
	{
		//Orbwalker Events
		eventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
		eventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnOrbwalkAttack);
		eventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
		eventManager->RemoveEventHandler(kEventOrbwalkTargetChange, OnOrbwalkAfterAttack);
		eventManager->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkOrbwalkNonKillableMinion);
		eventManager->RemoveEventHandler(kEventOrbwalkFindTarget, OnOrbwalkFindTarget);

		//Game Events
		eventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
		eventManager->RemoveEventHandler(kEventOnGameEnd, OnGameEnd);
		eventManager->RemoveEventHandler(kEventOnWndProc, OnGameWndProc);
		eventManager->RemoveEventHandler(kEventOnJungleNotification, OnJungleNotify);

		//Draw Events
		eventManager->RemoveEventHandler(kEventOnRender, OnDrawRender);
		eventManager->RemoveEventHandler(kEventOnRenderBehindHud, OnDrawRenderBehindHud);
		eventManager->RemoveEventHandler(kEventOnD3DPresent, OnDrawRenderD3DPresent);
		eventManager->RemoveEventHandler(kEventOnD3DPreReset, OnDrawRenderD3DPreReset);
		eventManager->RemoveEventHandler(kEventOnD3DPostReset, OnDrawRenderD3DPostReset);

		//Unit Events
		eventManager->RemoveEventHandler(kEventOnCreateObject, OnUnitCreate);
		eventManager->RemoveEventHandler(kEventOnDestroyObject, OnUnitDestroy);
		eventManager->RemoveEventHandler(kEventOnUnitDeath, OnUnitDeath);
		eventManager->RemoveEventHandler(kEventOnIssueOrder, OnUnitIssueOrder);
		eventManager->RemoveEventHandler(kEventOnPreCast, OnUnitPreCast);
		eventManager->RemoveEventHandler(kEventOnUpdateChargedSpell, OnUnitUpdateChargedSpell);
		eventManager->RemoveEventHandler(kEventOnSpellCast, OnUnitProcessSpellCast);
		eventManager->RemoveEventHandler(kEventOnDoCast, OnUnitDoCast);
		eventManager->RemoveEventHandler(kEventOnInterruptible, OnUnitProcessInterruptableSpellCast);
		eventManager->RemoveEventHandler(kEventOnGapCloser, OnUnitProcessGapCloserSpellCast);
		eventManager->RemoveEventHandler(kEventOnBuffAdd, OnUnitBuffAdd);
		eventManager->RemoveEventHandler(kEventOnBuffRemove, OnUnitBuffRemove);
		eventManager->RemoveEventHandler(kEventOnLevelUp, OnUnitLevelUp);
		eventManager->RemoveEventHandler(kEventOnDash, OnUnitDash);
		eventManager->RemoveEventHandler(kEventOnEnterVisible, OnUnitEnterVisibility);
		eventManager->RemoveEventHandler(kEventOnExitVisible, OnUnitExitVisibility);
		eventManager->RemoveEventHandler(kEventOnPlayAnimation, OnUnitPlayAnimation);
		eventManager->RemoveEventHandler(kEventOnPauseAnimation, OnUnitPauseAnimation);
		eventManager->RemoveEventHandler(kEventOnNewPath, OnUnitNewPath);
	}
}
