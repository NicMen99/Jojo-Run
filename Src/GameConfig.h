//
// Created by Niccolo on 05/10/2020.
//

#ifndef JOJO_RUN_GAMECONFIG_H
#define JOJO_RUN_GAMECONFIG_H

#include <string>
#include <map>

class GameConfig {
    GameConfig()=default;
    virtual ~GameConfig()=default;
    static GameConfig * _instance;
public:
    static GameConfig * instance();

    void init(const std::string & base_dir);
    std::string getAssetPath(const std::string & name);

private:
    // int loadConfigFile(std::string s);
    std::string asset_base_dir;
    std::map<std::string, std::string> asset_map;
};

#define GC GameConfig::instance()

#endif //JOJO_RUN_GAMECONFIG_H
