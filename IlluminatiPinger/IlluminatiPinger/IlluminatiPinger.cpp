#include "PluginSDK.h"
#include <math.h>
#define M_PI 3.14159265358979323846

PluginSetup("IlluminatiPinger - Trees");

IMenu* Menu;
IMenuOption* Enabled;
IMenuOption* Exploit;
IMenuOption* Key;
IMenuOption* Points;
IMenuOption* Delay;
IMenuOption* Radius;
IMenuOption* Arrow;

int LastPing;
bool drawingArrow;
Vec3 arrowStart;

std::vector<std::string> badObjects = {"obj_BarracksDampener", "obj_HQ"};

static bool IsKeyDown(IMenuOption* menuOption)
{
	return GUtility->IsLeagueWindowFocused() && (GetAsyncKeyState(menuOption->GetInteger()) & 0x8000) != 0;
}

IUnit* GetUnitUnderCursor()
{
	auto d = 10000.f;
	IUnit* unit = nullptr;

	auto pos = GGame->CursorPosition();
	for (auto obj: GEntityList->GetAllUnits())
	{
		if (obj != nullptr && obj->IsValidObject() && std::find(badObjects.begin(), badObjects.end(), obj->GetClassIdentifier()) == badObjects.end())
		{
			auto d2 = (obj->GetPosition() - pos).Length();
			if (d2 < d)
			{
				unit = obj;
				d = d2;
			}
		}
	}

	return unit;
}

Vec3 Rotate(Vec3 point, Vec3 pivot, double angleDegree)
{
	auto angle = angleDegree * M_PI / 180.f;
	auto cosa = cos(angle);
	auto sina = sin(angle);
	auto dx = point.x - pivot.x;
	auto dy = point.z - pivot.z;
	auto x = cosa * dx - sina * dy + pivot.x;
	auto y = sina * dx + cosa * dy + pivot.z;
	auto rotated = Vec3(x, 0, y);
	return rotated;
}

void SendPing(Vec3 pos)
{
	GGame->SendPing(Exploit->Enabled() ? 1 : kPingNormal, pos);
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	auto tick = GetTickCount();

	if (!Enabled->Enabled() || tick - LastPing < Delay->GetInteger() * 1000.f)
	{
		return;
	}

	auto drawArrow = IsKeyDown(Arrow);

	if (arrowStart != Vec3(0, 0, 0))
	{
		if (drawArrow)
		{
			return;
		}

		auto end = GGame->CursorPosition();

		if ((end - arrowStart).Length() < 50)
		{
			arrowStart = Vec3(0, 0, 0);
			return;
		}

		auto d = (end - arrowStart).Length2D();
		auto p1 = arrowStart.Extend(end, d * .3333f);
		auto p2 = arrowStart.Extend(end, d * .6666f);
		auto p3 = Rotate(p2, end, 50);
		auto p4 = Rotate(p2, end, -50);
		auto v = std::vector<Vec3>();

		v.push_back(arrowStart);
		v.push_back(p1);
		v.push_back(p2);
		v.push_back(end);
		v.push_back(p3);
		v.push_back(p4);

		for (auto point : v)
		{
			SendPing(point);
		}

		arrowStart = Vec3(0, 0, 0);
		LastPing = tick;
		return;
	}

	if (drawArrow)
	{
		arrowStart = GGame->CursorPosition();
	}

	if (!IsKeyDown(Key))
	{
		return;
	}

	auto unit = GetUnitUnderCursor();

	if (unit == nullptr || !unit->IsValidObject())
	{
		return;
	}

	auto count = Points->GetInteger();
	auto point = unit->ServerPosition();
	auto constant = M_PI / 2.f - M_PI / count;
	auto radius = Radius->GetInteger();
	auto exploit = Exploit->Enabled();

	if ((point - GGame->CursorPosition()).Length() > 300)
	{
		point = GGame->CursorPosition();
		GGame->SendPing(exploit ? 1 : kPingNormal, point);
	}
	else
	{
		GGame->SendPing(exploit ? 1 : kPingNormal, unit);
	}

	std::vector<Vec3> v;
	for (auto i = 0; i < count; i++)
	{
		auto x = static_cast<float>(point.x + radius * cos(i * 2.f * M_PI / count + constant));
		auto y = static_cast<float>(point.z + radius * sin(i * 2.f * M_PI / count + constant));
		auto pos = Vec3(x, 0, y);
		SendPing(pos);
	}

	LastPing = tick;
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	Menu = GPluginSDK->AddMenu("Illuminati Pinger");
	Enabled = Menu->CheckBox("Enabled", true);
	Exploit = Menu->CheckBox("Exploit", false);
	Key = Menu->AddKey("Key", 'G');
	Points = Menu->AddInteger("Points", 2, 5, 3);
	Radius = Menu->AddInteger("Radius", 300, 600, 300);
	Arrow = Menu->AddKey("Arrow", 'H');
	Delay = Menu->AddInteger("Delay (s)", 1, 5, 3);

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
}

PLUGIN_API void OnUnload()
{
	Menu->Remove();
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
}

