#pragma once
#include <functional>
#include "PluginData.h"
#include "PluginSDK.h"

typedef unsigned int event_id_t;

namespace eventmanager
{
	class OrbwalkerEventManager
	{
	public:
		static event_id_t RegisterBeforeAttackEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterAttackEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func);
		static event_id_t RegisterAfterAttackEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func);
		static event_id_t RegisterNewTargetEvent(std::function<void(event_id_t, IUnit*, IUnit*)> func);
		static event_id_t RegisterNonKillableMinionEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterFindTargetEvent(std::function<IUnit *(event_id_t)> func);

		static void UnregisterBeforeAttackEvent(event_id_t id);
		static void UnregisterAttackEvent(event_id_t id);
		static void UnregisterAfterAttackEvent(event_id_t id);
		static void UnregisterNewTargetEvent(event_id_t id);
		static void UnregisterNonKillableMinionEvent(event_id_t id);
		static void UnregisterFindTargetEvent(event_id_t id);

	private:
		OrbwalkerEventManager()
		{
		}
	};

	class GameEventManager
	{
	public:
		static event_id_t RegisterUpdateEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterEndEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterWndProcEvent(std::function<bool(event_id_t, HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)> func);
		static event_id_t RegisterJungleNotifyEvent(std::function<void(event_id_t, JungleNotifyData*)> func);

		static void UnregisterUpdateEvent(event_id_t id);
		static void UnregisterEndEvent(event_id_t id);
		static void UnregisterWndProcEvent(event_id_t id);
		static void UnregisterJungleNotifyEvent(event_id_t id);

	private:
		GameEventManager()
		{
		}
	};

	class DrawEventManager
	{
	public:
		static event_id_t RegisterRenderEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterRenderBehindHudEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterD3DPresentEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterD3DPreResetEvent(std::function<void(event_id_t)> func);
		static event_id_t RegisterD3DPostResetEvent(std::function<void(event_id_t)> func);

		static void UnregisterRenderEvent(event_id_t id);
		static void UnregisterRenderBehindHudEvent(event_id_t id);
		static void UnregisterD3DPresentEvent(event_id_t id);
		static void UnregisterD3DPreResetEvent(event_id_t id);
		static void UnregisterD3DPostResetEvent(event_id_t id);

	private:
		DrawEventManager()
		{
		}
	};

	class UnitEventManager
	{
	public:
		static event_id_t RegisterCreateEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterDestroyEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterDeathEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterIssueOrderEvent(std::function<bool(event_id_t, IUnit*, int, Vec3*, IUnit*)> func);
		static event_id_t RegisterPreCastEvent(std::function<bool(event_id_t, int, IUnit*, Vec3*, Vec3*)> func);
		static event_id_t RegisterUpdateChargedSpellEvent(std::function<void(event_id_t, int, Vec3*, bool*, bool*)> func);
		static event_id_t RegisterProcessSpellCastEvent(std::function<void(event_id_t, CastedSpell const&)> func);
		static event_id_t RegisterDoCastEvent(std::function<void(event_id_t, CastedSpell const&)> func);
		static event_id_t RegisterProcessInterruptibleSpellEvent(std::function<void(event_id_t, InterruptibleSpell const&)> func);
		static event_id_t RegisterProcessGapCloserSpellEvent(std::function<void(event_id_t, GapCloserSpell const&)> func);
		static event_id_t RegisterBuffAddEvent(std::function<void(event_id_t, IUnit*, void*)> func);
		static event_id_t RegisterBuffRemoveEvent(std::function<void(event_id_t, IUnit*, void*)> func);
		static event_id_t RegisterLevelUpEvent(std::function<void(event_id_t, IUnit*, int)> func);
		static event_id_t RegisterDashEvent(std::function<void(event_id_t, UnitDash*)> func);
		static event_id_t RegisterEnterVisibilityEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterExitVisibilityEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterPlayAnimationEvent(std::function<bool(event_id_t, IUnit*, std::string const)> func);
		static event_id_t RegisterPauseAnimationEvent(std::function<void(event_id_t, IUnit*)> func);
		static event_id_t RegisterNewPathEvent(std::function<void(event_id_t, IUnit*, std::vector<Vec3> const&)> func);

		static void UnregisterCreateEvent(event_id_t id);
		static void UnregisterDestroyEvent(event_id_t id);
		static void UnregisterDeathEvent(event_id_t id);
		static void UnregisterIssueOrderEvent(event_id_t id);
		static void UnregisterPreCastEvent(event_id_t id);
		static void UnregisterUpdateChargedSpellEvent(event_id_t id);
		static void UnregisterProcessSpellCastEvent(event_id_t id);
		static void UnregisterDoCastEvent(event_id_t id);
		static void UnregisterProcessInterruptibleSpellEvent(event_id_t id);
		static void UnregisterProcessGapCloserSpellEvent(event_id_t id);
		static void UnregisterBuffAddEvent(event_id_t id);
		static void UnregisterBuffRemoveEvent(event_id_t id);
		static void UnregisterLevelUpEvent(event_id_t id);
		static void UnregisterDashEvent(event_id_t id);
		static void UnregisterEnterVisibilityEvent(event_id_t id);
		static void UnregisterExitVisibilityEvent(event_id_t id);
		static void UnregisterPlayAnimationEvent(event_id_t id);
		static void UnregisterPauseAnimationEvent(event_id_t id);
		static void UnregisterNewPathEvent(event_id_t id);

	private:
		UnitEventManager()
		{
		}
	};

	void RegisterEvents(IEventManager* eventManager);
	void UnregisterEvents(IEventManager* eventManager);
}
