#pragma once
#include "PluginSDK.h"
class IUnit;

class Pix
{
public:
	static void Initialize(ISpell2* spell, IMenuOption* draw);
	static void __cdecl OnRender();
	static void Unload();
	static bool IsPixValid();
	static void UpdatePix();
	static IUnit* GetPix();
	static IUnit* GetTarget(boolean eReady);
	static IUnit* GetETarget(IUnit* target);
private:
	static IUnit* pix;
	static ISpell2* pixQ;
	static IMenuOption* draw;
	static void __cdecl OnGameUpdate();
	static IUnit* player;
};
