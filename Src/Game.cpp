//
// Created by angiolo99 on 23/08/20.
//

#include "GameConfig.h"
#include "Game.h"
#include <cstring>
#include <fstream>

float Game::getCreationRate() const {
    return creationRate;
}

Game::~Game() {
    blocks.clear();
    enemies.clear();
    firewalls.clear();
    powerups.clear();
    knives.clear();
}

void Game::createObj() {
    if (powerupClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::Knife);
            knife->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            powerups.emplace_back(move(knife));
            isCreated = true;
            powerupClk.restart();
            countCreation++;
        }
        if (countCreation % 7 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> shield = factory.createPowerUp(PowerUpType::Shield);
            shield->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            powerups.emplace_back(move(shield));
            isCreated = true;
            powerupClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
            block->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            blocks.emplace_back(move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<FireWall> fireWall = factory.createFireWall(FireWallType::MovingWall);
            fireWall->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            firewalls.emplace_back(move(fireWall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (!isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
            block->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            blocks.emplace_back(move(block));
            std::unique_ptr<FireWall> firewall = factory.createFireWall(FireWallType::StillWall);
            firewall->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            firewalls.emplace_back(move(firewall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::throwKnife() {
    if (hero.getKnives() > 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) {
        hero.setKnives(hero.getKnives() - 1);
        std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::ThrownKnife);
        knife->setPosition(sf::Vector2f(hero.getHeroPos().x, hero.getHeroPos().y));
        knives.emplace_back(move(knife));
    }
}

void Game::createEnemy() {
    if (enemyClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 4 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::HamonEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            hamonEnemySound.play();
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 4 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::EmeraldEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            emeraldEnemySound.play();
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 4 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::FireEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            fireEnemySound.play();
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        /*
        if(!isCreated){
            std::unique_ptr<Enemy> enemy= factory.createEnemy(EnemyType::StillEnemy);
            enemy->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        */
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
    numLife.setString(std::to_string(hero.getHealth()));
    numLife.setPosition(1500, 3);
    numLife.setCharacterSize(40);
    numLife.setFillColor(sf::Color::White);

    knivesTxt.setFont(font);
    knivesTxt.setString("Knives");
    knivesTxt.setPosition(1400, 38);
    knivesTxt.setCharacterSize(35);
    knivesTxt.setFillColor(sf::Color::White);

    numKnives.setFont(font);
    numKnives.setString(std::to_string(hero.getKnives()));
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
        if (enemies[i]->getPosition().x + enemies[i]->getGlobalBounds().width < 0)
            enemies.erase(enemies.begin() + i);
    }
}

void Game::moveObject() {
    for (auto &b : blocks) {
        if (b->getIsMovingBlock()) {
            if (b->getPosition().y + b->getGlobalBounds().height >= map.getMapSize().y - ground ||
                b->getPosition().y <= 0)
                b->setBlockSpeedX(-b->getBlockSpeedX());
                b->move(-b->getBlockSpeedX(), 0);
        }
    }
    for (auto &p : powerups) {
        if (p->getIsMovingPu()) {
            if (p->getPosition().y + p->getGlobalBounds().height >= map.getMapSize().y - ground ||
                p->getPosition().y <= 0)
                p->setSpeedPux(-p->getSpeedPux());
                p->move(-p->getSpeedPux(), 0);
        }
    }

    for (auto &f : firewalls) {
        if (f->getIsMovingFW()) {
            if (f->getPosition().y + f->getGlobalBounds().height >= map.getMapSize().y - ground ||
                f->getPosition().y <= 0)
                f->setFireWallSpeedX(-f->getFWSpeedX());
                f->move(-f->getFWSpeedX(), 0);
        }
    }
    for (auto &k: knives) {
        k->setPosition(hero.getHeroPos());
        if (k->getIsMovingPu()) {
            if (k->getPosition().y + k->getGlobalBounds().height >= map.getMapSize().y - ground ||
                k->getPosition().y <= 0)
                k->setSpeedPux(+k->getSpeedPux());
                k->move(+k->getSpeedPux(), 0);
        }
    }
}

void Game::collision() {
    if (!isCollided) {
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i]->getGlobalBounds().intersects(hero.getHeroBounds())) {
                //Se ha lo scudo e interseca un blocco non muore
                if (isShieldOn) {
                    isShieldOn = false;
                    shieldOnSound.play();
                    controlPU.restart();
                    blocks.erase(blocks.begin()+i);
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
                    hero.gameOver();
                    collisionSound.play();
                    BlockCollision = true;
                    collisionClk.restart();
                }
            }
        }
        for (int j = 0; j < firewalls.size(); j++) {
            if (firewalls[j]->getGlobalBounds().intersects(hero.getHeroBounds())) {
                //Se ha lo scudo e interseca l'oggetto non muore
                if (isShieldOn) {
                    isShieldOn = false;
                    shieldOnSound.play();
                    controlPU.restart();
                    firewalls.erase(firewalls.begin()+j);
                }else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
                    hero.gameOver();
                    collisionSound.play();
                    FirewallCollision = true;
                    collisionClk.restart();
                }
            }
        }
        for (int e = 0; e < enemies.size(); e++) {
            if (enemies[e]->getGlobalBounds().intersects(hero.getHeroBounds())) {
                //Se ha lo scudo e interseca il nemico non muore
                if (isShieldOn) {
                    isShieldOn = false;
                    shieldOnSound.play();
                    controlPU.restart();
                    enemies.erase(enemies.begin()+e);
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
                    hero.gameOver();
                    collisionSound.play();
                    EnemyCollision = true;
                    collisionClk.restart();
                }
            }
        }
        for (int m = 0; m < powerups.size(); m++) {
            if (powerups[m]->getGlobalBounds().intersects(hero.getHeroBounds()) && strcmp(typeid(powerups[m]).name(), "Shield") == 0) {
                if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    ShieldPowerupCollision = true;
                    isCollided = true;
                    powerUpSound.play();
                    powerups.erase(powerups.begin() + m);
                    collisionClk.restart();
                }
            }
            else if (powerups[m]->getGlobalBounds().intersects(hero.getHeroBounds()) && strcmp(typeid(powerups[m]).name(), "Knife") == 0){
                if (controlPU.getElapsedTime().asSeconds() >= toll){
                    KnivesPowerupCollision = true;
                    isCollided = true;
                    powerups.erase(powerups.begin() + m);
                    collisionClk.restart();
                }
            }
        }
        for (int h = 0; h < powerups.size(); h++) {
            for (auto & enemy : enemies){
                if (powerups[h]->getGlobalBounds().intersects(enemy->getGlobalBounds()) && (strcmp(typeid(powerups[h]).name(), "ThrownKnife") == 0)) {
                    if (controlPU.getElapsedTime().asSeconds() >= toll) {
                        isCollided = true;
                        KnifeCollision = true;
                        powerups.erase(powerups.begin() + h);
                        int e = enemies.size();
                        enemies.erase(enemies.begin() + e);
                        collisionClk.restart();
                    }
                }
            }
        }
    }
}

void Game::moveHero() {
    hero.setHeroPos(hero.getHeroPos().x, hero.getHeroPos().y + g);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        hero.setHeroPos(hero.getHeroPos().x, hero.getHeroPos().y - jump);
        if (isShieldOn)
            hero.setHeroTexture(heroTextureS1);
        else
            hero.setHeroTexture(heroTexture2);
        heroTexture2.setSmooth(true);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (isShieldOn)
            hero.setHeroTexture(heroTextureS1);
        else
            hero.setHeroTexture(heroTexture1);
        heroTexture1.setSmooth(true);
    }
    if (hero.getHeroPos().y + hero.getHeroSize().y >= map.getMapSize().y - ground)
        hero.setHeroPos(hero.getHeroPos().x, map.getMapSize().y - (hero.getHeroSize().y + ground));
    if (hero.getHeroPos().y <= top )
        hero.setHeroPos(hero.getHeroPos().x, top);
}

void Game::moveEnemy() {
    for (auto &e : enemies) {
        if (e->getIsMovingEnemy()) {
            if (e->getPosition().y + e->getGlobalBounds().height >= map.getMapSize().y - ground ||
                e->getPosition().y <= 0)
                e->setSpeed(-e->getSpeed());
                e->move(-e->getSpeed(), 0);
        }
    }
}

int Game::randomPosY() {
    return (rand() % map.getMapSize().y);
}

int Game::randomCreation() {
    return (rand() % 3);
}

Game::Game(): map("JoJoRun", sf::Vector2u(1600, 1000)), hero(), layer1(), layer2(), layer3(), layer4(), factory(),
            speed(sf::Vector2f(1.1,1.1)), oldSpeed(speed), blockX(100), isCreated(false), isCollided(false), BlockCollision(false), EnemyCollision(false),
            FirewallCollision(false), KnifeCollision(false), KnivesPowerupCollision(false), ShieldPowerupCollision(false), countCreation(1), creationRate(2.5f),
            /*oldCreationRate(creationRate),*/ objectClk(), powerupClk(),shieldClk(), scoreClk(), controlPU(), collisionClk(),enemyClk(), isShieldOn(false),
            n(1), score(0), txtCount(0),bestScore(0) {

    //setting dei layers del background
    layer1Texture.loadFromFile(GC->getAssetPath("Background1"));
    layer1Texture.setRepeated(true);
    layer1.setTexture(layer1Texture);
    layer1.setScale(7.4, 7.4);
    layer1.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer2Texture.loadFromFile(GC->getAssetPath("BG"));
    layer2Texture.setRepeated(true);
    layer2.setTexture(layer2Texture);
    layer2.setScale(7.4, 7.4);
    layer2.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer3Texture.loadFromFile(GC->getAssetPath("Foreground"));
    layer3Texture.setRepeated(true);
    layer3.setScale(7.4, 7.4);
    layer3.setTexture(layer3Texture);
    layer3.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer4Texture.loadFromFile(GC->getAssetPath("Middle"));
    layer4Texture.setRepeated(true);
    layer4.setTexture(layer4Texture);
    layer4.setScale(7.4, 7.4);
    layer4.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));

    //setting texture e sprite
    heroTexture1.loadFromFile(GC->getAssetPath("playerTexture"));
    heroTexture2.loadFromFile(GC->getAssetPath("playerTextureUp"));
    hero.setTexture(heroTexture1);
    heroTextureS1.loadFromFile(GC->getAssetPath("shieldPowerUpTexture"));

    gameOverTexture.loadFromFile(GC->getAssetPath("GameOverScreen"));
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(225,100);
    gameOver.setScale(0.8,0.8);

    //setting music
    gameMusic.openFromFile(GC->getAssetPath("soundTrack"));
    gameMusic.setLoop(true);
    gameMusic.setVolume(10.f);
    gameMusic.play();

    gameOverBuffer.loadFromFile(GC->getAssetPath("gameOverSound"));
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(21.f);

    collisionBuffer.loadFromFile(GC->getAssetPath("collisionSound"));
    collisionSound.setBuffer(collisionBuffer);
    collisionSound.setVolume(22.f);

    powerUpBuffer.loadFromFile(GC->getAssetPath("shieldSound"));
    powerUpSound.setBuffer(powerUpBuffer);
    powerUpSound.setVolume(20.f);

    shieldOnBuffer.loadFromFile(GC->getAssetPath("shieldOn"));
    shieldOnSound.setBuffer(shieldOnBuffer);
    shieldOnSound.setVolume(20.f);

    fireEnemyBuffer.loadFromFile(GC->getAssetPath("fireEnemyShout"));
    fireEnemySound.setBuffer(fireEnemyBuffer);
    fireEnemySound.setVolume(21.f);

    emeraldEnemyBuffer.loadFromFile(GC->getAssetPath("emeraldEnemyShout"));
    emeraldEnemySound.setBuffer(emeraldEnemyBuffer);
    emeraldEnemySound.setVolume(21.f);

    hamonEnemyBuffer.loadFromFile(GC->getAssetPath("hamonEnemyShout"));
    hamonEnemySound.setBuffer(hamonEnemyBuffer);
    hamonEnemySound.setVolume(21.f);

    // Loading Font
    font.loadFromFile(GC->getAssetPath("arcadeclassic"));


    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(map.getMapSize().y - (top + blockX));
}

void Game::update() {
    map.update();
    layer1.move(-speed.x, 0);
    layer2.move(-speed.x*1.2, 0);
    layer3.move(-speed.x*1.4, 0);
    layer4.move(-speed.x*1.6, 0);

    if (hero.getIsDead() && txtCount == 0) {
        file.open("Score.txt", std::ios::out | std::ios::app);
        file << std::endl;
        file << "Score: " << score;
        file.close();
        txtCount++;

        gameMusic.stop();
        collisionSound.stop();
        shieldOnSound.stop();
        powerUpSound.stop();
        hamonEnemySound.stop();
        emeraldEnemySound.stop();
        fireEnemySound.stop();
        gameOverSound.play();

        bestScoreFileRead.open("BestScore.txt");
        bestScoreFileRead >> bestScore;
        bestScoreFileRead.close();

        bestScoreFileWrite.open("BestScore.txt");
        if (score > bestScore) {
            bestScore = score;
        }
        bestScoreFileWrite.clear();
        bestScoreFileWrite << bestScore;
        bestScoreFileWrite.close();
    }
    createObj();
    createEnemy();
    moveObject();
    moveHero();
    moveEnemy();
    deleteObject();
    deleteEnemy();
    handleTxt();

    setScore(score);
    setHealth(hero.getHealth());

    if (!hero.getIsDead()) {
        collision();
    }
    if (isCollided ) {
        if (collisionClk.getElapsedTime().asSeconds() >= 0.8f) {
            if(FirewallCollision && hero.getHealth() > 15){
                hero.setHealth(hero.getHealth() - 15);
                notify();
                FirewallCollision =false;
            }
            if(BlockCollision && hero.getHealth() > 70){
                hero.setHealth(hero.getHealth() - 70);
                notify();
                BlockCollision = false;
            }
            if(EnemyCollision && getHealth() > 90){
                hero.setHealth(hero.getHealth() - 90);
                notify();
                EnemyCollision = false;
            }
            if(ShieldPowerupCollision){
                isShieldOn = true;
                notify();
                ShieldPowerupCollision = false;
            }
            if(KnifeCollision){
                //se l'eroe colpisce un nemico col coltello lanciato, la sua vita aumenta leggermente
                hero.setHealth(hero.getHealth() + 20);
                notify();
                KnifeCollision = false;
            }
            if(KnivesPowerupCollision){
                hero.setKnives(hero.getKnives() + 4);
                notify();
                KnivesPowerupCollision = false;
            }
        }
        isCollided = false;
    }

    if(isShieldOn && shieldClk.getElapsedTime().asSeconds() >= 20.f) {
        isShieldOn = false;
    }

    if (scoreClk.getElapsedTime().asSeconds() >= 1.f && !hero.getIsDead()) {
        score ++;
        scoreClk.restart();
        notify();
    }
}

const sf::Vector2f &Game::getSpeed() const {
    return speed;
}

int Game::getMaxY() const {
    return maxY;
}

void Game::render() {
    map.clear();
    map.draw(layer2);
    map.draw(layer1);
    map.draw(layer4);
    map.draw(layer3);

    if (!hero.getIsDead()) {
        hero.renderHero(*map.getRenderMap());
        for (auto &block : blocks)
            map.draw(*block);
        for (auto &movBlock : blocks)
            map.draw(*movBlock);
        for (auto &power : powerups)
            map.draw(*power);
        for (auto &enem : enemies)
            map.draw(*enem);
        for (auto &movEnem : enemies)
            map.draw(*movEnem);
        for (auto &fire: firewalls)
            map.draw(*fire);
        for (auto &movFire: firewalls)
            map.draw(*movFire);
        for (auto &knife : knives)
            map.draw(*knife);
        map.draw(scoreTxt);
        map.draw(numScore);
        map.draw(lifeTxt);
        map.draw(numLife);
        map.draw(knivesTxt);
        map.draw(numKnives);
    }
    else {
        scoreTxt.setCharacterSize(80);
        numScore.setCharacterSize(80);
        scoreTxt.setPosition(600, 400);
        numScore.setPosition(900, 400);
        scoreB.setPosition(500, 390);

        map.draw(scoreTxt);
        map.draw(numScore);
        map.draw(gameOver);
        map.draw(scoreB);
        map.draw(bestScoreTxt);
        map.draw(bestScoreB);
        map.draw(bestScoreNum);
    }
    map.display();
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
    return hero.getHealth();
}

void Game::setScore(unsigned int s) {
    Game::score = s;
    notify();
}

void Game::setHealth(int hp) {
    Game::hero.setHealth(hp);
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



