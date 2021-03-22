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
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        Score::Record record;
        if (!(iss >> record.nickname
                  >> record.score )) {
            break;
        }
        m_records.emplace_back(record);
    }
    sort();
}

void Score::add(const Score::Record &r) {
    m_records.emplace_back(r);
}

void Score::save() {
    sort();

    std::ofstream outfile(m_fileName);
    if(!outfile.is_open())
        return;

    for(auto record : m_records) {
        outfile << record.nickname
                << " "
                << record.score
                << std::endl;
    }
}

void Score::sort() {
    std::sort(m_records.begin(), m_records.end(),
              [](Record const &l, Record const &r) { return l.score > r.score; });
}


