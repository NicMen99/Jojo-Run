//
// Created by Niccolo on 21/03/2021.
//

#ifndef JOJO_RUN_SCOREFILE_H
#define JOJO_RUN_SCOREFILE_H


#include <string>
#include <vector>

class ScoreManager {
private:

    struct Record {
        bool        added;
        std::string nickname;
        int         score;
        int         distance;
        int         clean_distance;
        int         killed;
        int         consec_killed;
        int         time;
        void clear() {
            added=false;
            nickname="";
            score=0;
            distance=0;
            clean_distance=0;
            killed=0;
            consec_killed=0;
            time=0;
        }
    };

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

    /* achievement management */
public:
    void init();
    void update();

    /* Record file management */
    void loadFromFile();
    void setName(const std::string & nickname);
    void saveToFile();
    std::vector<Record> getScoreRecord();
};


#endif //JOJO_RUN_SCOREFILE_H
