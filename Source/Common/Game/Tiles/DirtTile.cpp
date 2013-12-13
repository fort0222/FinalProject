#include "DirtTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


DirtTile::DirtTile(const char* textureName) : Tile(TileTypeDirt, textureName, true)
{

}

DirtTile::~DirtTile()
{

}

const char* DirtTile::getType()
{
   return TILE_DIRT_TYPE;
}

float DirtTile::getTileSpeed()
{
    return 0.75f;
}
