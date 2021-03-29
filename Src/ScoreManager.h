//
// Created by Niccolo on 21/03/2021.
//

#ifndef JOJO_RUN_SCOREFILE_H
#define JOJO_RUN_SCOREFILE_H


#include <string>
#include <vector>

class ScoreManager {

    struct Record {
        bool        added;
        std::string nickname;
        int         score;
    };

    /* achievement management */
public:
    void init();
    void update();

    /* Record file management */
public:
    void loadFromFile();
    void addScoreRecord(const std::string & nickname, int score);
    void saveToFile();
    std::vector<Record> getScoreRecord();

private:
    void sort();

private:
    const std::string m_fileName = "ScoreManager.txt";
    std::vector<Record> m_records;
    Record m_score_record;
    int m_last_distance = 0;

private:
    bool m_killed_1 = false;
    bool m_killed_2 = false;
    bool m_killed_3 = false;

    bool m_distance_1 = false;
    bool m_distance_2 = false;
    bool m_distance_3 = false;

    bool m_combo_1 = false;
    bool m_combo_2 = false;
    bool m_combo_3 = false;
};


#endif //JOJO_RUN_SCOREFILE_H
