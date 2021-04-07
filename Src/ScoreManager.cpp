//
// Created by Niccolo on 21/03/2021.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Game.h"
#include "ScoreManager.h"

void ScoreManager::init() {
    m_score_record.clear();

    m_score_bonus = 0;
    m_distance_achiev = {5000, 10000};
    m_clean_distance_achiev = {3000, 5000};
    m_killed_achiev = {3, 5};
    m_consecutive_killed_achiev = {2, 3};
}

void ScoreManager::update() {

    /*
     * distanza
     */
    m_score_record.time = STATS->getInt(Stats::Time);
    m_score_record.distance = STATS->getInt(Stats::Distance);
    /*
     * bonus distanza
     */
    if(m_score_record.distance >= m_distance_achiev.second) {
        m_distance_achiev = {m_distance_achiev.second, 2 * m_distance_achiev.second - m_distance_achiev.first };
        STATS->setInt(Achievements::Distance, m_distance_achiev.first);
        m_score_bonus += m_distance_achiev.first / 100;
    }
    /*
     * bonus distanza senza danni
     */
    if(STATS->getInt(Stats::CleanDistance) > m_score_record.clean_distance)
        m_score_record.clean_distance = STATS->getInt(Stats::CleanDistance);
    if(m_score_record.clean_distance >= m_clean_distance_achiev.second) {
        m_clean_distance_achiev = {m_clean_distance_achiev.second, m_clean_distance_achiev.second + m_clean_distance_achiev.first};
        STATS->setInt(Achievements::CleanDistance, m_score_record.clean_distance);
        m_score_bonus += m_clean_distance_achiev.first / 100;
    }

    /*
     * bonus uccisioni
     */
    m_score_record.killed = STATS->getInt(Stats::Killed);
    if(m_score_record.killed >= m_killed_achiev.second) {
        m_killed_achiev = {m_killed_achiev.second, 2 * m_killed_achiev.second - m_killed_achiev.first};
        STATS->setInt(Achievements::Killed, m_killed_achiev.first);
        m_score_bonus += m_killed_achiev.first * 10;
    }

    /*
     * bonus uccisioni consecutive
     */
    if(STATS->getInt(Stats::ConsecutiveKilled) > m_score_record.consec_killed)
        m_score_record.consec_killed = STATS->getInt(Stats::ConsecutiveKilled);
    if(m_score_record.consec_killed >= m_consecutive_killed_achiev.second){
        m_consecutive_killed_achiev = {m_consecutive_killed_achiev.second, m_consecutive_killed_achiev.first + m_consecutive_killed_achiev.second};
        STATS->setInt(Achievements::ConsecutiveKilled, m_consecutive_killed_achiev.first);
        m_score_bonus += m_consecutive_killed_achiev.second * 100;
    }

    m_score_record.score = m_score_record.distance / m_distance_unit + m_score_bonus;
    STATS->setInt(Stats::Score, m_score_record.score);
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
                  >> record.rank
                  >> record.nickname
                  >> record.score
                  >> record.distance
                  >> record.clean_distance
                  >> record.killed
                  >> record.consec_killed
                  >> record.time
                  )) {
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
    sort();
}

void ScoreManager::saveToFile() {
    std::ofstream outfile(m_fileName);
    if(!outfile.is_open())
        return;

    for(const auto& record : m_records) {
        outfile << (record.added ? "*": "-")
                << " "
                << record.rank
                << " "
                << record.nickname
                << " "
                << record.score
                << " "
                << record.distance
                << " "
                << record.clean_distance
                << " "
                << record.killed
                << " "
                << record.consec_killed
                << " "
                << record.time
                << std::endl;
    }
}

void ScoreManager::sort() {
    std::sort(m_records.begin(), m_records.end(),
              [](Record const &l, Record const &r) { return l.score > r.score; });
    int rank = 0;
    for(auto& record : m_records) {
        record.rank = ++rank;
        if(record.added)
            m_score_record.rank = rank;
    }
}
