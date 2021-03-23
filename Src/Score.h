//
// Created by Niccolo on 21/03/2021.
//

#ifndef JOJO_RUN_SCOREFILE_H
#define JOJO_RUN_SCOREFILE_H


#include <string>
#include <vector>

class Score {

    struct Record {
        bool        added;
        std::string nickname;
        int         score;
    };

public:
    void load();
    void add(const std::string & nickname, int score);
    void save();
    std::vector<Score::Record> get();

private:
    void sort();

private:
    const std::string m_fileName = "Score.txt";
    std::vector<Score::Record> m_records;
};


#endif //JOJO_RUN_SCOREFILE_H
