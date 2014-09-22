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
const std::string kAssetUIAttackButton          = kPathUI + "attack_button.png";
const std::string kAssetUIAttackButtonPressed   = kPathUI + "attack_button_pressed.png";
const std::string kAssetUICharacterCard         = kPathUI + "character_card.png";
const std::string kAssetUICharacterCardSelected = kPathUI + "character_card_selected.png";
const std::string kAssetUICommandPanel          = kPathUI + "command_panel.png";
const std::string kAssetUIGameTimerPanel        = kPathUI + "gametimer_panel.png";
const std::string kAssetUIMoveButton            = kPathUI + "move_button.png";
const std::string kAssetUIMoveButtonPressed     = kPathUI + "move_button_pressed.png";
const std::string kAssetUIPausedPanel           = kPathUI + "paused_panel.png";
const std::string kAssetUIRotateButton          = kPathUI + "rotate_button.png";
const std::string kAssetUIRotateButtonPressed   = kPathUI + "rotate_button_pressed.png";
const std::string kAssetUIBackgroundPanel       = kPathUI + "ui_background_panel.png";


/* Tiles */
const std::string kAssetArtTilesHexagon = kPathTiles + "tiles_hexagon.png";
const std::string kAssetArtTilesIsometric = kPathTiles + "tiles_isometric_48.png";
const std::string kAssetArtTilesHexIsometric = kPathTiles + "tiles_hexagon_isometric.png";

/* Fonts */
const std::string kAssetFontPsychoPoetry = kPathFont + "psychopoetry.ttf";
const std::string kAssetFontConsolas = kPathFont + "consola.ttf";
const std::string kAssetFontUbuntuMono = kPathFont + "UbuntuMono-Regular.ttf";

/* Maps */
const std::string kMapTest24x18HexIsometric = kPathMap + "test_24x18_hex_iso.map";
const std::string kMapTestHexIsometric = kPathMap + "test_hex_iso.map";

#endif
