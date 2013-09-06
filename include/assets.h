#include <string>

#ifndef TLB_ASSETS_H_
#define TLB_ASSETS_H_

/* Paths */
const std::string kPathRoot       = "";
const std::string kPathAssets     = kPathRoot   + "assets/";
const std::string kPathArt        = kPathAssets + "art/";
const std::string kPathFont       = kPathAssets + "font/";
const std::string kPathSprites = kPathArt + "sprites/";
const std::string kPathMap        = kPathRoot   + "maps/";

/* Art */
const std::string kAssetArtDot = kPathArt + "dot.png";
const std::string kAssetArtDotCircle = kPathArt + "dot_circle.png";
const std::string kAssetArtGreenCircle = kPathArt + "green_circle.png";
const std::string kAssetArtWhiteCircle = kPathArt + "white_circle.png";
const std::string kAssetArtProbe = kPathSprites + "probe.png";
const std::string kAssetArtShip = kPathSprites + "ship.png";
const std::string kAssetArtRobot = kPathSprites + "robot.png";
const std::string kAssetArtTiles = kPathSprites + "tiles.png";

const std::string kAssetArtHexagon = kPathArt + "hexagon.png";
const std::string kAssetArtHexagonOutline = kPathArt + "hexagon_outline.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";

/* Maps */
const std::string kMapTest20x12 = kPathMap + "test_20x12.map";
const std::string kMapTest80x45 = kPathMap + "test_80x45.map";

#endif
