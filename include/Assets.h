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
const std::string kPathUI         = kPathArt    + "ui/";

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

/* UI */
const std::string kAssetUIAttackButton           = kPathUI + "attackButton.png";
const std::string kAssetUIAttackButtonPressed    = kPathUI + "attackButtonPressed.png";
const std::string kAssetUICharacterPanel         = kPathUI + "characterPanel.png";
const std::string kAssetUICharacterPanelSelected = kPathUI + "characterPanelSelected.png";
const std::string kAssetUICommandPanel           = kPathUI + "commandPanel.png";
const std::string kAssetUIGameTimerPanel         = kPathUI + "gametimerPanel.png";
const std::string kAssetUIMoveButton             = kPathUI + "moveButton.png";
const std::string kAssetUIMoveButtonPressed      = kPathUI + "moveButtonPressed.png";
const std::string kAssetUIPausedPanel            = kPathUI + "pausedPanel.png";
const std::string kAssetUIRotateButton           = kPathUI + "rotateButton.png";
const std::string kAssetUIRotateButtonPressed    = kPathUI + "rotateButtonPressed.png";
const std::string kAssetUIBackgroundPanel        = kPathUI + "uiBackgroundPanel.png";


/* Tiles */
const std::string kAssetArtTiles = kPathTiles + "tiles_48.png";
const std::string kAssetArtTilesIsometric = kPathTiles + "tilesIsometric_48.png";

const std::string kAssetArtTilesHexagon = kPathTiles + "tilesHexagon.png";
const std::string kAssetArtTilesHexIsometric = kPathTiles + "tilesHexagonIsometric.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";
const std::string kAssetFontUbuntuMono = kPathFont + "UbuntuMono-Regular.ttf";

/* Maps */
const std::string kMapTest3D = kPathMap + "test_3d.xml";
const std::string kMapTest24x18 = kPathMap + "test_24x18.xml";
const std::string kMapTest24x18Iso = kPathMap + "test_24x18Iso.map";

const std::string kMapTest24x18HexIsometric = kPathMap + "test_24x18HexIso.map";
const std::string kMapTestHexIsometric = kPathMap + "testHexIso.map";

#endif
