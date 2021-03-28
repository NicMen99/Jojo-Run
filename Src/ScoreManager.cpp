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
}

void ScoreManager::update() {

    int dist = STATS.getInt("DISTANCE");
    if(dist - m_last_distance > CONFIG.getWindowSize().x) {
        m_last_distance = dist;
        m_score_record.score += 1;
    }

    if (dist > CONFIG.getWindowSize().x * 13) {
        m_score_record.score += 10;
    }

    STATS.setInt("SCORE", m_score_record.score);
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
