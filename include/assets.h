#include <string>

#ifndef TLB_ASSETS_H_
#define TLB_ASSETS_H_

/* Paths */
const std::string kPathRoot       = "";
const std::string kPathAssets     = kPathRoot   + "assets/";
const std::string kPathArt        = kPathAssets + "art/";
const std::string kPathFont       = kPathAssets + "font/";
const std::string kPathSprites    = kPathArt    + "sprites/";
const std::string kPathTiles      = kPathArt    + "tiles/";
const std::string kPathMap        = kPathRoot   + "maps/";

/* Art */

/* Sprites */
const std::string kAssetSpriteZombie1 = kPathSprites + "zombie1.png";
const std::string kAssetSpriteZombie2 = kPathSprites + "zombie2.png";
const std::string kAssetSpriteZombie3 = kPathSprites + "zombie3.png";
const std::string kAssetSpriteZombie4 = kPathSprites + "zombie4.png";
const std::string kAssetSpriteZombie5 = kPathSprites + "zombie5.png";
const std::string kAssetSpriteZombie6 = kPathSprites + "zombie6.png";
const std::string kAssetSpriteXMLZombie = kPathSprites + "zombie.xml";

const std::string kAssetSpriteHuman1 = kPathSprites + "human1.png";
const std::string kAssetSpriteXMLHuman = kPathSprites + "human.xml";

/* Tiles */
const std::string kAssetArtTilesHexagon = kPathTiles + "tiles_hexagon.png";
const std::string kAssetArtTilesIsometric = kPathTiles + "tiles_isometric_48.png";
const std::string kAssetArtTilesHexIsometric = kPathTiles + "tiles_hexagon_isometric.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";

/* Maps */
const std::string kMapTestHexIsometric = kPathMap + "test_24x18_hex_iso.map";

#endif
