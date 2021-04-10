//
// Created by Niccolo on 10/04/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "Mock/MockGameConfig.h"
#include "Mock/MockSceneManager.h"

class ScoreManagerTest : public ::testing::Test {
private:
    Game * game;
public:
    ScoreManagerTest() {
        Game::deleteInstance();
        auto state = new GameStateMachine(State::Init);
        auto cfg   = new MockGameConfig();
        auto resm  = new ResourceManager();
        auto fact  = new Factory();
        auto scn   = new MockSceneManager();
        auto stats = new GameStats();
        auto score = new ScoreManager();
        game = Game::instance(state, cfg, resm, fact, scn, stats, score);
        cfg->init();
    }
};

/*
 * Record azzerato dopo init()
 */
TEST_F(ScoreManagerTest, Init) {
    SCORE->init();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.added, false);
    ASSERT_EQ(record.rank, 0);
    ASSERT_EQ(record.nickname, "");
    ASSERT_EQ(record.score, 0);
    ASSERT_EQ(record.distance, 0);
    ASSERT_EQ(record.clean_distance, 0);
    ASSERT_EQ(record.killed, 0);
    ASSERT_EQ(record.consec_killed, 0);
    ASSERT_EQ(record.time, 0);
}

/*
 * Distanza
 */
TEST_F(ScoreManagerTest, Distance) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 1500);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 1500);

    STATS->setInt(Stats::Distance, 5000);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 5000);
}

/*
 * Calcolo base punteggio
 */
TEST_F(ScoreManagerTest, Score) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 50);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.score, 0);
    ASSERT_EQ(record.distance, 50);

    STATS->setInt(Stats::Distance, 150);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.score, 1);
    ASSERT_EQ(record.distance, 150);
    ASSERT_EQ(STATS->getInt(Stats::Score), 1);
}

/*
 * Distanza bonus
 */
TEST_F(ScoreManagerTest, DistanceBonus) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 3000);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 3000);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 0);
    int score = 30;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 11111);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 11111);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 10000);
    score = 111 + 50;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 16134);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 16134);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 15000);
    score = 161 + 50 + 75;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 21789);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 21789);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 20000);
    score = 217 + 50 + 75 + 100;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);
}

/*
 * Distanza senza danni bonus
 */
TEST_F(ScoreManagerTest, CleanDistanceBonus) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 3210);
    STATS->setInt(Stats::CleanDistance, 1111);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 3210);
    ASSERT_EQ(record.clean_distance, 1111);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 0);
    ASSERT_EQ(STATS->getInt(Achievements::CleanDistance), 0);
    int score = 32;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 7450);
    STATS->setInt(Stats::CleanDistance, 5011);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 7450);
    ASSERT_EQ(record.clean_distance, 5011);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 0);
    ASSERT_EQ(STATS->getInt(Achievements::CleanDistance), 5000);
    score = 74 + 100;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 11450);
    STATS->setInt(Stats::CleanDistance, 1050);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 11450);
    ASSERT_EQ(record.clean_distance, 5011);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 10000);
    ASSERT_EQ(STATS->getInt(Achievements::CleanDistance), 5000);
    score = 114 + 50 + 100;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 19999);
    STATS->setInt(Stats::CleanDistance, 8150);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 19999);
    ASSERT_EQ(record.clean_distance, 8150);
    ASSERT_EQ(STATS->getInt(Achievements::Distance), 15000);
    ASSERT_EQ(STATS->getInt(Achievements::CleanDistance), 8000);
    score = 199 + 50 + 100 + 75 + 160;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);
}

/*
 * Uccisioni
 */
TEST_F(ScoreManagerTest, Killed) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 3333);
    STATS->setInt(Stats::Killed, 1);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 3333);
    ASSERT_EQ(record.killed, 1);
    int score = 33 + 10;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 4);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 4);
    score = 99 + 40;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);
}

/*
 * Uccisioni bonus
 */
TEST_F(ScoreManagerTest, ConsecutiveKilledBonus) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 4);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 4);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 0);
    int score = 99 + 40;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 7);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 7);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 5);
    score = 99 + 70 + 100;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 10);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 10);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 10);
    score = 99 + 100 + 100 + 200;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);
}

/*
 * Uccisioni consecutive bonus
 */
TEST_F(ScoreManagerTest, KilledBonus) {
    STATS->init();
    SCORE->init();

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 4);
    STATS->setInt(Stats::ConsecutiveKilled, 2);
    SCORE->update();
    ScoreManager::Record record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 4);
    ASSERT_EQ(record.consec_killed, 2);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 0);
    ASSERT_EQ(STATS->getInt(Achievements::ConsecutiveKilled), 0);
    int score = 99 + 40;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 5);
    STATS->setInt(Stats::ConsecutiveKilled, 3);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 5);
    ASSERT_EQ(record.consec_killed, 3);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 5);
    ASSERT_EQ(STATS->getInt(Achievements::ConsecutiveKilled), 3);
    score = 99 + 50 + 100 + 150;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);

    STATS->setInt(Stats::Distance, 9999);
    STATS->setInt(Stats::Killed, 8);
    STATS->setInt(Stats::ConsecutiveKilled, 6);
    SCORE->update();
    record = SCORE->getRecord();
    ASSERT_EQ(record.distance, 9999);
    ASSERT_EQ(record.killed, 8);
    ASSERT_EQ(record.consec_killed, 6);
    ASSERT_EQ(STATS->getInt(Achievements::Killed), 5);
    ASSERT_EQ(STATS->getInt(Achievements::ConsecutiveKilled), 5);
    score = 99 + 80 + 100 + 150 + 250;
    ASSERT_EQ(record.score, score);
    ASSERT_EQ(STATS->getInt(Stats::Score), score);
}

/*
 * Score File
 */
TEST_F(ScoreManagerTest, ScoreFileInitTest) {
    SCORE->init();
    SCORE->saveToFile();
    SCORE->loadFromFile();
    ASSERT_EQ(SCORE->getScoreRecords().size(), 0);

    STATS->setInt(Stats::Distance, 3210);
    STATS->setInt(Stats::CleanDistance, 1111);
    STATS->setInt(Stats::Killed, 2);
    STATS->setInt(Stats::ConsecutiveKilled, 2);
    SCORE->update();
    STATS->setInt(Stats::Distance, 10101);
    STATS->setInt(Stats::CleanDistance, 5006);
    STATS->setInt(Stats::Killed, 4);
    STATS->setInt(Stats::ConsecutiveKilled, 8);
    STATS->setInt(Stats::Time, 33);
    SCORE->update();

    SCORE->setName("TESTER1");
    SCORE->saveToFile();
    SCORE->loadFromFile();
    std::vector<ScoreManager::Record> records = SCORE->getScoreRecords();
    ASSERT_EQ(records.size(), 1);
    ASSERT_EQ(records[0].added, false);
    ASSERT_EQ(records[0].rank, 1);
    ASSERT_EQ(records[0].nickname, "TESTER1");
    ASSERT_EQ(records[0].score, 441);
    ASSERT_EQ(records[0].distance, 10101);
    ASSERT_EQ(records[0].clean_distance, 5006);
    ASSERT_EQ(records[0].killed, 4);
    ASSERT_EQ(records[0].consec_killed, 8);
    ASSERT_EQ(records[0].time, 33);

    STATS->setInt(Stats::Distance, 3210);
    STATS->setInt(Stats::CleanDistance, 1111);
    STATS->setInt(Stats::Killed, 2);
    STATS->setInt(Stats::ConsecutiveKilled, 2);
    SCORE->update();
    STATS->setInt(Stats::Distance, 13101);
    STATS->setInt(Stats::CleanDistance, 7009);
    STATS->setInt(Stats::Killed, 5);
    STATS->setInt(Stats::ConsecutiveKilled, 10);
    STATS->setInt(Stats::Time, 63);
    SCORE->update();

    SCORE->setName("TESTER2");
    SCORE->saveToFile();
    SCORE->loadFromFile();
    records = SCORE->getScoreRecords();
    ASSERT_EQ(records.size(), 2);
    ASSERT_EQ(records[0].added, false);
    ASSERT_EQ(records[0].rank, 1);
    ASSERT_EQ(records[0].nickname, "TESTER2");
    ASSERT_EQ(records[0].score, 1231);
    ASSERT_EQ(records[0].distance, 13101);
    ASSERT_EQ(records[0].clean_distance, 7009);
    ASSERT_EQ(records[0].killed, 5);
    ASSERT_EQ(records[0].consec_killed, 10);
    ASSERT_EQ(records[0].time, 63);
    ASSERT_EQ(records[1].added, false);
    ASSERT_EQ(records[1].rank, 2);
    ASSERT_EQ(records[1].nickname, "TESTER1");
    ASSERT_EQ(records[1].score, 441);
    ASSERT_EQ(records[1].distance, 10101);
    ASSERT_EQ(records[1].clean_distance, 5006);
    ASSERT_EQ(records[1].killed, 4);
    ASSERT_EQ(records[1].consec_killed, 8);
    ASSERT_EQ(records[1].time, 33);

    STATS->setInt(Stats::Distance, 3210);
    STATS->setInt(Stats::CleanDistance, 1111);
    STATS->setInt(Stats::Killed, 2);
    STATS->setInt(Stats::ConsecutiveKilled, 2);
    SCORE->update();
    STATS->setInt(Stats::Distance, 12101);
    STATS->setInt(Stats::CleanDistance, 7009);
    STATS->setInt(Stats::Killed, 5);
    STATS->setInt(Stats::ConsecutiveKilled, 10);
    STATS->setInt(Stats::Time, 53);
    SCORE->update();

    SCORE->setName("TESTER1");
    SCORE->saveToFile();
    SCORE->loadFromFile();
    records = SCORE->getScoreRecords();
    ASSERT_EQ(records.size(), 3);
    ASSERT_EQ(records[0].added, false);
    ASSERT_EQ(records[0].rank, 1);
    ASSERT_EQ(records[0].nickname, "TESTER2");
    ASSERT_EQ(records[0].score, 1231);
    ASSERT_EQ(records[0].distance, 13101);
    ASSERT_EQ(records[0].clean_distance, 7009);
    ASSERT_EQ(records[0].killed, 5);
    ASSERT_EQ(records[0].consec_killed, 10);
    ASSERT_EQ(records[0].time, 63);
    ASSERT_EQ(records[1].added, false);
    ASSERT_EQ(records[1].rank, 2);
    ASSERT_EQ(records[1].nickname, "TESTER1");
    ASSERT_EQ(records[1].score, 1221);
    ASSERT_EQ(records[1].distance, 12101);
    ASSERT_EQ(records[1].clean_distance, 7009);
    ASSERT_EQ(records[1].killed, 5);
    ASSERT_EQ(records[1].consec_killed, 10);
    ASSERT_EQ(records[1].time, 53);
    ASSERT_EQ(records[2].added, false);
    ASSERT_EQ(records[2].rank, 3);
    ASSERT_EQ(records[2].nickname, "TESTER1");
    ASSERT_EQ(records[2].score, 441);
    ASSERT_EQ(records[2].distance, 10101);
    ASSERT_EQ(records[2].clean_distance, 5006);
    ASSERT_EQ(records[2].killed, 4);
    ASSERT_EQ(records[2].consec_killed, 8);
    ASSERT_EQ(records[2].time, 33);
}
