#include <string>

#ifndef TLB_ASSETS_H_
#define TLB_ASSETS_H_

/* Paths */
const std::string kPathRoot       = "";
const std::string kPathAssets     = kPathRoot   + "assets/";
const std::string kPathArt        = kPathAssets + "art/";
const std::string kPathFont       = kPathAssets + "font/";
const std::string kPathSprites = kPathArt + "sprites/";
const std::string kPathTiles = kPathArt + "tiles/";
const std::string kPathMap        = kPathRoot   + "maps/";

/* Art */
const std::string kAssetArtDot = kPathArt + "dot.png";
const std::string kAssetArtDotCircle = kPathArt + "dot_circle.png";
const std::string kAssetArtGreenCircle = kPathArt + "green_circle.png";
const std::string kAssetArtWhiteCircle = kPathArt + "white_circle.png";
const std::string kAssetArtProbe = kPathSprites + "probe.png";
const std::string kAssetArtShip = kPathSprites + "ship.png";
const std::string kAssetArtRobot = kPathSprites + "robot.png";

const std::string kAssetArtHexagon = kPathSprites + "hexagon.png";
const std::string kAssetArtHexagonOutline = kPathSprites + "hexagon_outline.png";

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
const std::string kAssetArtTiles80 = kPathTiles + "tiles_80.png";
const std::string kAssetArtTiles48 = kPathTiles + "tiles_48.png";
const std::string kAssetArtTiles32 = kPathTiles + "tiles_32.png";
const std::string kAssetArtTilesHexagon = kPathTiles + "hexagon_tiles.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";

/* Maps */
const std::string kMapTest20x12 = kPathMap + "test_20x12.map";
const std::string kMapTest24x18 = kPathMap + "test_24x18.map";
const std::string kMapTest28x24 = kPathMap + "test_28x24.map";
const std::string kMapTest32x24 = kPathMap + "test_32x24.map";
const std::string kMapTest80x45 = kPathMap + "test_80x45.map";
const std::string kMapTest28x24Structure = kPathMap + "test_28x24_structure.map";

const std::string kMapTest24x18Blank = kPathMap + "test_24x18_blank.map";

#endif
