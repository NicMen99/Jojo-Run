//
// Created by Niccolo on 21/03/2021.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Game.h"
#include "GameStats.h"
#include "GameConfig.h"
#include "ScoreManager.h"

void ScoreManager::init() {
    m_score_record.nickname = "";
    m_score_record.score = 0;
    m_killed_1 = false;
    m_killed_2 = false;
    m_killed_3 = false;
    m_distance_1 = false;
    m_distance_2 = false;
    m_distance_3 = false;
    m_combo_1 = false;
    m_combo_2 = false;
    m_combo_3 = false;
}

void ScoreManager::update() {

    int dist = STATS.getInt("DISTANCE");
    if(dist - m_last_distance > CONFIG.getWindowSize().x) {
        m_last_distance = dist;
        m_score_record.score += 1;
    }
    STATS.setInt("SCORE", m_score_record.score);

    /*
     * Achievments distanza
     */

    if(STATS.getInt("DISTANCE") > 30000 && !m_distance_1){
        STATS.setInt("ACHIEVEMENT_D1", 1);
        m_distance_1 = true;
    }
    if(STATS.getInt("DISTANCE") > 75000 && !m_distance_2){
        STATS.setInt("ACHIEVEMENT_D2", 1);
        m_distance_1 = true;
    }
    if(STATS.getInt("DISTANCE") > 150000 && !m_distance_3){
        STATS.setInt("ACHIEVEMENT_D3", 1);
        m_distance_1 = true;
    }

    /*
     * Achievements uccisioni
     */

    if(STATS.getInt("KILLED") == 5 && !m_killed_1) {
        STATS.setInt("ACHIEVEMENT_K1", 1);
        m_killed_1 = true;
    }
    if(STATS.getInt("KILLED") == 15 && !m_killed_2) {
        STATS.setInt("ACHIEVEMENT_K2", 1);
        m_killed_2 = true;
    }
    if(STATS.getInt("KILLED") == 30 && !m_killed_3) {
        STATS.setInt("ACHIEVEMENT_K3", 1);
        m_killed_3 = true;
    }

    /*
     * Achievements uccisioni consecutive
     */

    if(STATS.getInt("COMBO") == 3 && !m_combo_1) {
        STATS.setInt("ACHIEVEMENT_C1", 1);
        m_combo_1 = true;
    }
    if(STATS.getInt("COMBO") == 7 && !m_combo_2) {
        STATS.setInt("ACHIEVEMENT_C2", 1);
        m_combo_2 = true;
    }
    if(STATS.getInt("COMBO") == 10 && !m_combo_3) {
        STATS.setInt("ACHIEVEMENT_C3", 1);
        m_combo_3 = true;
    }
}

void ScoreManager::loadFromFile() {

    m_records.clear();

    std::ifstream infile(m_fileName);
    if(!infile.is_open())
        return;

    std::string line;
    std::string tmp;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        ScoreManager::Record record;
        record.added = false;
        if (!(iss >> tmp //discard first field
                  >> record.nickname
                  >> record.score)) {
            continue;
        }
        m_records.emplace_back(record);
    }
    sort();
}

void ScoreManager::addScoreRecord(const std::string & nickname, int score) {
    Record r;
    r.added = true;
    r.nickname = nickname;
    r.score = score;
    m_records.emplace_back(r);
}

void ScoreManager::saveToFile() {
    sort();

    std::ofstream outfile(m_fileName);
    if(!outfile.is_open())
        return;

    for(const auto& record : m_records) {
        outfile << (record.added ? "*": "-")
                << " "
                << record.nickname
                << " "
                << record.score
                << std::endl;
    }
}

std::vector<ScoreManager::Record> ScoreManager::getScoreRecord() {
    return m_records;
}

void ScoreManager::sort() {
    std::sort(m_records.begin(), m_records.end(),
              [](Record const &l, Record const &r) { return l.score > r.score; });
}
