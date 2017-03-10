#pragma once
#include "PluginSDK.h"
#include "EventManager.h"
#include <algorithm>
#include <unordered_map>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <fstream>
#include <unordered_set>

#define M_PI 3.14159265358979323846

#pragma comment(lib, "urlmon")

class LPPUtils
{
public:
	static double AngleBetween(Vec3 a, Vec3 b, bool degrees = true)
	{
		return (acos((a.DotProduct(b)) / (a.Length() * b.Length()))) * (degrees ? (180.f / M_PI) : 1);
	}

	static void DelayAction(IPluginSDK* sdk, std::function<void()> action, unsigned long ticks)
	{
		auto startTick = GetTickCount();
		eventmanager::GameEventManager::RegisterUpdateEvent([=](event_id_t id) -> void
			{
				if ((GetTickCount() - startTick) > ticks)
				{
					action();
					eventmanager::GameEventManager::UnregisterUpdateEvent(id);
					return;
				}
			});
	}

	static void DelayActionGame(IPluginSDK* sdk, std::function<void()> action, float interval)
	{
		static auto game = sdk->GetGame();

		auto startTime = game->Time();
		eventmanager::GameEventManager::RegisterUpdateEvent([=](event_id_t id) -> void
			{
				if ((game->Time() - startTime) > interval)
				{
					action();
					eventmanager::GameEventManager::UnregisterUpdateEvent(id);
					return;
				}
			});
	}

	static Vec2 Extend(const Vec2& from, const Vec2& to, float distance)
	{
		return from + (distance * (to - from).VectorNormalize());
	}

	static Vec3 Extend(const Vec3& from, const Vec3& to, float distance)
	{
		return from + (distance * (to - from).VectorNormalize());
	}
};
