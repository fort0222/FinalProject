#include "PitTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


PitTile::PitTile(const char* textureName) : Tile(TileTypePit, textureName, false)
{

}

PitTile::~PitTile()
{

}

const char* PitTile::getType()
{
   return TILE_PIT_TYPE;
}
