//
// Created by Niccolo on 21/03/2021.
//

#ifndef JOJO_RUN_SCOREFILE_H
#define JOJO_RUN_SCOREFILE_H


#include <string>
#include <vector>

class ScoreManager {
public:
    struct Record {
        int         added;
        int         rank;
        std::string nickname;
        int         score;
        int         distance;
        int         clean_distance;
        int         killed;
        int         consec_killed;
        int         time;
        void clear() {
            added=false;
            rank=0;
            nickname="";
            score=0;
            distance=0;
            clean_distance=0;
            killed=0;
            consec_killed=0;
            time=0;
        }
    };

    /* achievement management */
    void init();
    void update();

    /* Record file management */
    void loadFromFile();
    void setName(const std::string & nickname);
    void saveToFile();
    std::vector<Record> getScoreRecords() { return m_records; }
    Record getScore() { return m_score_record; }

private:
    void sort();
    const std::string m_fileName = "ScoreManager.txt";
    std::vector<Record> m_records;
    Record m_score_record;

    static const int m_distance_unit = 100;
    int m_score_bonus = 0;
    std::pair<int, int> m_distance_achiev = {0, 0};
    std::pair<int, int> m_clean_distance_achiev = {0, 0};
    std::pair<int, int> m_killed_achiev = {0, 0};
    std::pair<int, int> m_consecutive_killed_achiev = {0, 0};
};


#endif //JOJO_RUN_SCOREFILE_H
