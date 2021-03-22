//
// Created by Niccolo on 21/03/2021.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Score.h"

void Score::load() {

    m_records.clear();

    std::ifstream infile(m_fileName);
    if(!infile.is_open())
        return;

    std::string line;
    std::string tmp;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        Score::Record record;
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

void Score::add(const std::string & nickname, int score) {
    Record r;
    r.added = true;
    r.nickname = nickname;
    r.score = score;
    m_records.emplace_back(r);
}

void Score::save() {
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

std::vector<Score::Record> Score::get() {
    return m_records;
}

void Score::sort() {
    std::sort(m_records.begin(), m_records.end(),
              [](Record const &l, Record const &r) { return l.score > r.score; });
}
