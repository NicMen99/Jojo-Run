//
// Created by Niccolo on 10/04/2021.
//

#ifndef JOJO_RUN_TESTGAMECONFIG_H
#define JOJO_RUN_TESTGAMECONFIG_H

#include "Game.h"

class TestGameConfig : public GameConfig {
public:
    void init() override;
    void clear();
    void setSceneSpeed(sf::Vector2f speed);
    void setMapResource(const std::string & name, const std::string & asset_path);
    void setTextureResource(const std::string & name, const std::string & asset_path);
    void setFontResource(const std::string & name, const std::string & asset_path);
    void setSoundResource(const std::string & name, const std::string & asset_path);
};
#endif //JOJO_RUN_TESTGAMECONFIG_H
