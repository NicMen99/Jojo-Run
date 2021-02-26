//
// Created by angiolo99 on 23/08/20.
//
#include <fstream>
#include <memory>
#include "GameConfig.h"
#include "Game.h"


Game::~Game() {
    blocks.clear();
    enemies.clear();
    firewalls.clear();
    powerups.clear();
    knives.clear();
    platforms.clear();
}

void Game::init() {
    m_window.create(sf::VideoMode(1600, 1000), "JoJo Run");
    //m_window.setFramerateLimit(60);
}

void Game::loop() {
    while(m_window.isOpen()){
        while (m_window.pollEvent(m_event)) {
            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }
        sf::Time elapsedTime = m_clock.restart();
        m_accumulator += elapsedTime;

        while (m_accumulator > m_framerate) {
            m_accumulator -= m_framerate;
            m_gameMachine->exec();
            m_gameMachine->update(m_framerate.asMilliseconds());
            sf::sleep(sf::milliseconds(10));
        }
        m_window.clear();
        m_gameMachine->render(m_window);
        m_window.display();
    }
}

float Game::getCreationRate() const {
    return creationRate;
}

void Game::createObj() {

    if (powerupClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::Knife);
            knife->setMPosition(sf::Vector2f(m_window.getSize().x + 20, randomPosY()));
            powerups.emplace_back(std::move(knife));
            isCreated = true;
            powerupClk.restart();
            countCreation++;
        }
        if (countCreation % 9 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> shield = factory.createPowerUp(PowerUpType::Shield);
            shield->setMPosition(sf::Vector2f(m_window.getSize().x + 20, randomPosY()));
            powerups.emplace_back(std::move(shield));
            isCreated = true;
            powerupClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
            block->setMPosition(sf::Vector2f(m_window.getSize().x + 50, randomPosY()));
            blocks.emplace_back(std::move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 3 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<FireWall> fireWall = factory.createFireWall(FireWallType::MovingWall);
            fireWall->setMPosition(sf::Vector2f(m_window.getSize().x + 50, randomPosY()));
            firewalls.emplace_back(std::move(fireWall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (!isCreated) {
            objectClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::throwKnife() {
    if (m_hero.getKnives() > 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) {
        m_hero.setKnives(m_hero.getKnives() - 1);
        std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::ThrownKnife);
        knife->setMPosition(sf::Vector2f(m_hero.getHeroPos().x, m_hero.getHeroPos().y));
        knives.emplace_back(std::move(knife));
    }
}

void Game::createEnemy() {
    if (enemyClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 11 == 0 && randomCreation() == 1) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::HamonEnemy);
            enemy->setMPosition(sf::Vector2f(150 + m_window.getSize().x, randomPosY()));
            hamonEnemySound.play();
            enemies.emplace_back(std::move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 13 == 0 && randomCreation() == 1) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::EmeraldEnemy);
            enemy->setMPosition(sf::Vector2f(150 + m_window.getSize().x, randomPosY()));
            emeraldEnemySound.play();
            enemies.emplace_back(std::move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 17 == 0 && randomCreation() == 1) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::FireEnemy);
            enemy->setMPosition(sf::Vector2f(150 + m_window.getSize().x, randomPosY()));
            fireEnemySound.play();
            enemies.emplace_back(std::move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::handleTxt() {
    scoreTxt.setFont(font);
    scoreTxt.setString("Score");
    scoreTxt.setPosition(10, 3);
    scoreTxt.setCharacterSize(40);
    scoreTxt.setFillColor(sf::Color::White);

    numScore.setFont(font);
    numScore.setString(std::to_string(score));
    numScore.setPosition(135, 3);
    numScore.setCharacterSize(40);
    numScore.setFillColor(sf::Color::White);

    lifeTxt.setFont(font);
    lifeTxt.setString("HP");
    lifeTxt.setPosition(1440, 3);
    lifeTxt.setCharacterSize(40);
    lifeTxt.setFillColor(sf::Color::White);

    numLife.setFont(font);
    numLife.setString(std::to_string(m_hero.getHealth()));
    numLife.setPosition(1500, 3);
    numLife.setCharacterSize(40);
    numLife.setFillColor(sf::Color::White);

    knivesTxt.setFont(font);
    knivesTxt.setString("Knives");
    knivesTxt.setPosition(1400, 38);
    knivesTxt.setCharacterSize(35);
    knivesTxt.setFillColor(sf::Color::White);

    numKnives.setFont(font);
    numKnives.setString(std::to_string(m_hero.getKnives()));
    numKnives.setPosition(1535, 38);
    numKnives.setCharacterSize(35);
    numKnives.setFillColor(sf::Color::White);

    bestScoreTxt.setFont(font);
    bestScoreTxt.setString("High Score: ");
    bestScoreTxt.setPosition(450, 800);
    bestScoreTxt.setCharacterSize(75);
    bestScoreTxt.setFillColor(sf::Color::White);

    scoreB.setFont(font);
    scoreB.setString("0");
    scoreB.setCharacterSize(100);
    scoreB.setFillColor(sf::Color::White);

    bestScoreNum.setFont(font);
    bestScoreNum.setString(std::to_string(bestScore));
    bestScoreNum.setPosition(1000, 850);
    bestScoreNum.setCharacterSize(100);
    bestScoreNum.setFillColor(sf::Color::White);

    bestScoreB.setFont(font);
    bestScoreB.setString("h");
    bestScoreB.setPosition(300, 600);
    bestScoreB.setCharacterSize(110);
    bestScoreB.setFillColor(sf::Color::Black);
}

void Game::deleteObject() {
    for (int i=0; i<blocks.size(); i++) {
        if (blocks[i]->getPosition().x + blocks[i]->getGlobalBounds().width < 0)
            blocks.erase(blocks.begin() + i);
    }

    for (int i=0; i<firewalls.size(); i++) {
        if (firewalls[i]->getPosition().x + firewalls[i]->getGlobalBounds().width < 0)
            firewalls.erase(firewalls.begin() + i);
    }

    for (int i=0; i<powerups.size(); i++) {
        if (powerups[i]->getPosition().x + powerups[i]->getGlobalBounds().width < 0)
            powerups.erase(powerups.begin() + i);
    }
    for (int i=0; i<knives.size(); i++) {
        if (knives[i]->getPosition().x + knives[i]->getGlobalBounds().width < 0)
            knives.erase(knives.begin() + i);
    }
}

void Game::deleteEnemy() {
    for (int i=0; i<enemies.size(); i++) {
        if (enemies[i]->getEnemyPosition().x + enemies[i]->getEnemyBounds().width < 0)
            enemies.erase(enemies.begin() + i);
    }
}

/*
void Game::moveObject() {
    for (auto &b : blocks) {
        if (b->getIsMovingBlock()) {
// Controllare y non sembra servire fino quando non si implementa il movimento vericale
// Comunque con l'introduzione della mappa va cambiato
//            if (b->getPosition().y + b->getGlobalBounds().height >= m_window.getSize().y - ground || b->getPosition().y <= 0)
                b->update();
        }
    }
    for (auto &p : powerups) {
        if (p->getIsMovingPu()) {

            if (p->getPosition().y + p->getGlobalBounds().height >= m_window.getSize().y - ground || p->getPosition().y <= 0)
                p->setSpeedPux(-p->getSpeedPux());
                p->move({-p->getSpeedPux(), 0});

            p->update();
        }
    }


    for (auto &f : firewalls) {
        if (f->getIsMovingFW()) {

            if (f->getPosition().y + f->getGlobalBounds().height >= m_window.getSize().y - ground || f->getPosition().y <= 0)
                f->setFireWallSpeedX(-f->getFWSpeedX());
                f->move(-f->getFWSpeedX(), 0);

            f->update();
        }
    }
    for (auto &k: knives) {
        if (k->getIsMovingPu()) {

             if (k->getPosition().y + k->getGlobalBounds().height >= m_window.getSize().y - ground || k->getPosition().y <= 0)
                k->setSpeedPux(+k->getSpeedPux());
                k->move(+k->getSpeedPux(), 0);

            k->update();
        }
    }
}
*/


void Game::collision() {
    if (!isCollided) {
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i]->getGlobalBounds().intersects(m_hero.getHeroBounds())) {
                m_hero.collisionevent();
                if (isShieldOn) {
                    controlPU.restart();
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    collisionClk.restart();
                }
                BlockCollision = true;
                isCollided = true;
                collidedblocks = i;
            }
        }
        for (int j = 0; j < firewalls.size(); j++) {
            if (firewalls[j]->getGlobalBounds().intersects(m_hero.getHeroBounds())) {
                m_hero.collisionevent();
                if (isShieldOn) {
                    controlPU.restart();
                }else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    collisionClk.restart();
                }
                FirewallCollision = true;
                isCollided = true;
                collidedfirewalls = j;
            }
        }
        for (int e = 0; e < enemies.size(); e++) {
            if (enemies[e]->getEnemyBounds().intersects(m_hero.getHeroBounds())) {
                m_hero.collisionevent();
                if (isShieldOn) {
                    controlPU.restart();
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    collisionClk.restart();
                }
                isCollided = true;
                EnemyCollision = true;
                collidedenemies = e;
            }
        }
        for (int m = 0; m < powerups.size(); m++) {
            if (powerups[m]->getGlobalBounds().intersects(m_hero.getHeroBounds()) && powerups[m]->getisShield()) {
                if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    ShieldPowerupCollision = true;
                    isCollided = true;
                    collidedpowerups = m;
                    collisionClk.restart();
                    shieldClk.restart();
                }
            }
            else if (powerups[m]->getGlobalBounds().intersects(m_hero.getHeroBounds()) && powerups[m]->getisKnife()){
                if (controlPU.getElapsedTime().asSeconds() >= toll){
                    KnivesPowerupCollision = true;
                    isCollided = true;
                    collidedknives = m;
                    collisionClk.restart();
                }
            }
        }
        for (int h = 0; h < knives.size(); h++) {
            for (int e = 0; e < enemies.size(); e++){
                if (knives[h]->getGlobalBounds().intersects(enemies[e]->getEnemyBounds()) && knives[h]->getisThrowable()) {
                    if (controlPU.getElapsedTime().asSeconds() >= toll) {
                        KnifeCollision = true;
                        isCollided = true;
                        collidedknives = h;
                        collidedenemies = e;
                        collisionClk.restart();
                    }
                }
            }
        }
    }
}

void Game::moveHero() {
    m_hero.setHeroPos(m_hero.getHeroPos().x, m_hero.getHeroPos().y + g);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_hero.setHeroPos(m_hero.getHeroPos().x, m_hero.getHeroPos().y - jump);
        if (isShieldOn)
            m_hero.setShieldOn();
        else
            m_hero.setJumpOn();
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (isShieldOn)
            m_hero.setShieldOn();
        else
            m_hero.setStanding();
    }
    if (m_hero.getHeroPos().y + m_hero.getHeroSize().y >= m_window.getSize().y - ground)
        m_hero.setHeroPos(m_hero.getHeroPos().x, m_window.getSize().y - (m_hero.getHeroSize().y + ground));
    if (m_hero.getHeroPos().y <= top )
        m_hero.setHeroPos(m_hero.getHeroPos().x, top);
}

/*
void Game::moveEnemy() {
    for (auto &e : enemies) {
        if (e->getIsMovingEnemy()) {

            if (e->getEnemyPosition().y + e->getEnemyBounds().height >= m_window.getSize().y - ground ||
                e->getEnemyPosition().y <= 0)
                e->setSpeed(-e->getSpeed());
                e->move(-e->getSpeed(), 0);

            e->update();
        }
    }
}
*/

int Game::randomPosY() {
    int res = ((std::rand() % int(getWindowSize().y - this->top - this->ground - 85)) + this->top );
    return res;
}

int Game::randomCreation() {
    return (rand() % 3);
}

Game::Game():
    factory(),
    speed(sf::Vector2f(1.1,1.1)), oldSpeed(speed), blockX(100), isCreated(false), isCollided(false), BlockCollision(false), EnemyCollision(false),
    FirewallCollision(false), KnifeCollision(false), KnivesPowerupCollision(false), ShieldPowerupCollision(false), countCreation(1), creationRate(2.5f),
    /*oldCreationRate(creationRate),*/ objectClk(), powerupClk(),shieldClk(), scoreClk(), controlPU(), collisionClk(),enemyClk(), isShieldOn(false),
    n(1), score(0), txtCount(0),bestScore(0) {

    m_gameMachine = new GameStateMachine(this, State::Init);

    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(m_window.getSize().y - (top + blockX));
}

const sf::Vector2f &Game::getSpeed() const {
    return speed;
}

int Game::getMaxY() const {
    return maxY;
}

void Game::notify() {
    for (auto i = std::begin(observers); i != std::end(observers); i++)
        (*i)->update();
}

void Game::unsubscribe(Observer *o) {
    observers.remove(o);
}

void Game::subscribe(Observer *o) {
    observers.push_back(o);
}

unsigned int Game::getScore() const {
    return score;
}

int Game::getHealth() const {
    return m_hero.getHealth();
}

void Game::setScore(unsigned int s) {
    Game::score = s;
    notify();
}

void Game::setHealth(int hp) {
    Game::m_hero.setHealth(hp);
    notify();
}

bool Game::getIsShieldOn() const {
    return isShieldOn;
}

bool Game::getIsCollided() const{
    return isCollided;
}

bool Game::getIsBlockCollision() const{
    return BlockCollision;
}

bool Game::getIsEnemyCollision() const{
    return EnemyCollision;
}

bool Game::getIsFirewallCollision() const{
    return FirewallCollision;
}

bool Game::getIsShieldCollision() const{
    return ShieldPowerupCollision;
}

bool Game::getIsKnifeCollision() const{
    return KnivesPowerupCollision;
}

bool Game::getIsKnifeThrownCollision() const{
    return KnifeCollision;
}

void Game::setBlockCollision(bool blockCollision) {
    BlockCollision = blockCollision;
}

void Game::setEnemyCollision(bool enemyCollision) {
    EnemyCollision = enemyCollision;
}

void Game::setFirewallCollision(bool firewallCollision) {
    FirewallCollision = firewallCollision;
}

void Game::setKnifeCollision(bool knifeCollision) {
    KnifeCollision = knifeCollision;
}

void Game::setShieldPowerupCollision(bool shieldPowerupCollision) {
    ShieldPowerupCollision = shieldPowerupCollision;
}

void Game::setKnivesPowerupCollision(bool knivesPowerupCollision) {
    KnivesPowerupCollision = knivesPowerupCollision;
}

void Game::setIsShieldOn(bool isShieldOn) {
    Game::isShieldOn = isShieldOn;
}

void Game::setIsCollided(bool isCollided) {
    Game::isCollided = isCollided;
}

void Game::createPlatform() {
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<Platform> platform = factory.createPlatform(GroundType::Large);
            platforms.emplace_back(std::move(platform));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
    }
}

void Game::movePlatform(int32_t delta_time) {
    for (auto &p : platforms){
        p->update(delta_time);
    }
}

void Game::deletePlatform() {
    for (int i=0; i<platforms.size(); i++) {
        if (platforms[i]->getMPosition().x + platforms[i]->getMBounds().width < 0)
            platforms.erase(platforms.begin() + i);
    }
}


