#include "utils/assets.h"

std::vector<std::string> Assets::shipTextures(
        {"assets/graphics/xwing.png",
         "assets/graphics/falcon.png",
         "assets/graphics/ghost.png"});
std::vector<std::string> Assets::shipNames(
        {"X-wing", "Falcon", "Ghost"});

std::vector<std::string> Assets::keyTextures(
        {"assets/graphics/updown_key.png",
         "assets/graphics/leftright_key.png",
         "assets/graphics/space_key.png",
         "assets/graphics/enter_key.png",
         "assets/graphics/esc_key.png"});
std::vector<std::string> Assets::keyNames(
        {"Up / Down", "Left / Right",
        "Fire", "Select / Pause", "Quit"});

std::string Assets::saveScorePath = "assets/save/score";
std::string Assets::explosionPath = "assets/graphics/explosion.png";
std::string Assets::bgPath = "assets/graphics/bg.png";
std::string Assets::fontPath = "assets/fonts/font.ttf";
std::string Assets::menuTieLargePath = "assets/graphics/menu_tie_0.png";
std::string Assets::menuTieSmallPath = "assets/graphics/menu_tie_1.png";
std::string Assets::macdumiProfilePath = "assets/graphics/macdumi.png";
std::string Assets::adProfilePath = "assets/graphics/ad.png";

std::string Assets::combatMusicPath = "assets/sounds/combat.ogg";
std::string Assets::menuMusicPath = "assets/sounds/menu.ogg";
std::string Assets::gameOverMusicPath = "assets/sounds/gameover.ogg";
