#include <string>

#ifndef TLB_ASSETS_H_
#define TLB_ASSETS_H_

/* Paths */
const std::string kPathRoot       = "";
const std::string kPathAssets     = kPathRoot   + "assets/";
const std::string kPathArt        = kPathAssets + "art/";
const std::string kPathFont       = kPathAssets + "font/";
const std::string kPathSprites = kPathArt + "sprites/";

/* Art */
const std::string kAssetArtDot = kPathArt + "dot.png";
const std::string kAssetArtDotCircle = kPathArt + "dot_circle.png";
const std::string kAssetArtGreenCircle = kPathArt + "green_circle.png";
const std::string kAssetArtWhiteCircle = kPathArt + "white_circle.png";
const std::string kAssetArtProbe = kPathSprites + "probe.png";
const std::string kAssetArtShip = kPathSprites + "ship.png";
const std::string kAssetArtRobot = kPathSprites + "robot.png";

const std::string kAssetArtHexagon = kPathArt + "hexagon.png";
const std::string kAssetArtHexagonOutline = kPathArt + "hexagon_outline.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";

#endif
