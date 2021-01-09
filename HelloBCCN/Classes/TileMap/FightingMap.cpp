#include "FightingMap.h"

FightingMap::FightingMap()
{
	tiledMap = CCTMXTiledMap::create("map/huLaoMap.tmx");
}

FightingMap::~FightingMap()
{
}

void FightingMap::updateEXT(float delta)
{
}

CCTMXTiledMap* FightingMap::getTMXTiledMap()
{
	return tiledMap;
}