#include "LavaTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


LavaTile::LavaTile(const char* textureName) : Tile(TileTypeLava, textureName, false)
{

}

LavaTile::~LavaTile()
{

}

const char* LavaTile::getType()
{
   return TILE_LAVA_TYPE;
}
