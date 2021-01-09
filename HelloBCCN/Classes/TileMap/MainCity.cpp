#include "MainCity.h"

MainCity::MainCity()
{
	tiledMap = CCTMXTiledMap::create("map/MainCity.tmx");
}

MainCity::~MainCity()
{
}

void MainCity::updateEXT(float delta)
{
}

CCTMXTiledMap* MainCity::getTMXTiledMap()
{
	return tiledMap;
}