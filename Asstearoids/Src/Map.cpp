#include "Map.h"
//#include "GameInstance.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern EntityManager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{

}

/// <summary>
/// Loads a map from a file
/// </summary>
/// <param name="path"></param>
/// <param name="sizeX"></param>
/// <param name="sizeY"></param>
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int  srcX, srcY;


	for(int y = 0; y < sizeY; y++)
	{
		for(int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}


}

/// <summary>
/// Adds tiles to the manager
/// </summary>
/// <param name="srcX"></param>
/// <param name="srcY"></param>
/// <param name="xpos"></param>
/// <param name="ypos"></param>
void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto &tile(manager.addentity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(GameInstance::groupMap);
}

