//
// Created by Niccolo on 21/03/2021.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Game.h"
#include "ScoreManager.h"

void ScoreManager::init() {
    m_score_record.nickname = "";
    m_score_record.score = 0;

    m_distance_achiev = {3000, 5000};
    m_killed_achiev = {3, 5};
    m_conseckilled_achiev = {2,3};
}

void ScoreManager::update() {

    /*
     *  distanza
     */
    int distance = STATS->getInt(Stats::Distance);
    if(distance - m_last_distance > CONFIG->getWindowSize().x) {
        m_last_distance = distance;
        m_score_record.score += 1;
        STATS->addInt(Stats::Score, 1);
    }
    STATS->setInt(Stats::Score, m_score_record.score);
    if(distance >= m_distance_achiev.second){
        STATS->setInt(Achievements::Distance, distance/100*100);
        m_distance_achiev = {m_distance_achiev.second, m_distance_achiev.first + m_distance_achiev.second};
    }

    /*
     * uccisioni
     */
    int killed = STATS->getInt(Stats::Killed);
    if(killed >= m_killed_achiev.second){
        STATS->setInt(Achievements::Killed, killed);
        m_killed_achiev = {m_killed_achiev.second, m_killed_achiev.first + m_killed_achiev.second};
    }

    /*
     * uccisioni consecutive
     */
    int consecutive_killed = STATS->getInt(Stats::ConsecutiveKilled);
    if(consecutive_killed >= m_conseckilled_achiev.second){
        STATS->setInt(Achievements::ConsecutiveKilled, consecutive_killed);
        m_conseckilled_achiev = {m_conseckilled_achiev.second, m_conseckilled_achiev.first + m_conseckilled_achiev.second};
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

void ScoreManager::setName(const std::string & nickname) {
    m_score_record.nickname = nickname;
    m_score_record.added = true;
    m_records.emplace_back(m_score_record);
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
