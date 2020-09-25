//
// Created by angiolo99 on 23/08/20.
//

#include "Game.h"
#include <cstring>
#include <fstream>

bool Game::getIsCollided() const {
    return isCollided;
}

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
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::Knife);
            knife->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            powerups.emplace_back(move(knife));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<PowerUp> shield = factory.createPowerUp(PowerUpType::Knife);
            shield->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            powerups.emplace_back(move(shield));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            blocks.emplace_back(move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<FireWall> fireWall = factory.createFireWall(FireWallType::MovingWall);
            fireWall->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            firewalls.emplace_back(move(fireWall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (!isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            blocks.emplace_back(move(block));
            std::unique_ptr<FireWall> firewall = factory.createFireWall(FireWallType::StillWall);
            firewall->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            firewalls.emplace_back(move(firewall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::createEnemy() {
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 4 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::HamonEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::EmeraldEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 6 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::FireEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if(!isCreated){
            std::unique_ptr<Enemy> enemy= factory.createEnemy(EnemyType::StillEnemy);
            enemy->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::handleTxt() {
    scoreTxt.setFont(font);
    scoreTxt.setString("Score: ");
    scoreTxt.setPosition(10, 3);
    scoreTxt.setCharacterSize(25);
    scoreTxt.setFillColor(sf::Color::Black);

    lifeTxt.setFont(font);
    lifeTxt.setString(std::to_string(hero.getHealth()));
    lifeTxt.setPosition(1550, 11);
    lifeTxt.setCharacterSize(40);
    lifeTxt.setFillColor(sf::Color::Black);

    numScore.setFont(font);
    numScore.setString(std::to_string(score));
    numScore.setPosition(100, 3);
    numScore.setCharacterSize(25);
    numScore.setFillColor(sf::Color::Black);

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
            b->move(-speed.x, b->getBlockSpeedX());
        } else
            b->move(-speed.x, 0);
    }
    for (auto &p : powerups) {
        if (p->getIsMovingPu()) {
            if (p->getPosition().y + p->getGlobalBounds().height >= map.getMapSize().y - ground ||
                p->getPosition().y <= 0)
                p->setSpeedPux(-p->getSpeedPux());
            p->move(-speed.x, p->getSpeedPux());
        } else
            p->move(-speed.x, 0);
    }

    for (auto &f : firewalls) {
        if (f->getIsMovingFW()) {
            if (f->getPosition().y + f->getGlobalBounds().height >= map.getMapSize().y - ground ||
                f->getPosition().y <= 0)
                f->setFireWallSpeedX(-f->getFWSpeedX());
            f->move(-speed.x, f->getFWSpeedX());
        } else
            f->move(-speed.x, 0);
    }
    for (auto &k: knives) {
        if (k->getIsMovingPu()) {
            if (k->getPosition().y + k->getGlobalBounds().height >= map.getMapSize().y - ground ||
                k->getPosition().y <= 0)
                k->setSpeedPux(+k->getSpeedPux());
            k->move(+speed.x, k->getSpeedPux());
        } else
            k->move(-speed.x, 0);
    }
}

void Game::collision() {
    if (!isCollided) {
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i]->getGlobalBounds().intersects(hero.getHeroBounds())) {
                //Se ha lo scudo e interseca un blocco non muore
                if (isShieldOn) {
                    isShieldOn = false;
                    controlPU.restart();
                    blocks.erase(blocks.begin()+i);
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
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
                    controlPU.restart();
                    firewalls.erase(firewalls.begin()+j);
                }else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
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
                    controlPU.restart();
                    enemies.erase(enemies.begin()+e);
                } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                    isCollided = true;
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
                    powerups.erase(powerups.begin() + m);
                    collisionClk.restart();
                }
            }else if (powerups[m]->getGlobalBounds().intersects(hero.getHeroBounds()) && strcmp(typeid(powerups[m]).name(), "Knife") == 0){
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
                        powerups.erase(powerups.begin()+h);
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
            e->move(-speed.x, e->getSpeed());
        } else
            e->move(-speed.x, 0);
    }
}

int Game::randomPosY() {
    return (rand() % 3);
}

int Game::randomCreation() {
    return (rand() % 3);
}

int Game::randomPU() {
    return (rand() % 2);
}

Game::Game(): map("JoJoRun", sf::Vector2u(1600, 1000)), hero(), layer1(), layer2(), layer3(), layer4(), factory(),
            speed(sf::Vector2f(0.9,0.8)), oldSpeed(speed), blockX(100), isCreated(false), isCollided(false), BlockCollision(false), EnemyCollision(false),
            FirewallCollision(false), KnifeCollision(false), KnivesPowerupCollision(false), ShieldPowerupCollision(false), countCreation(1), creationRate(1.8f),
            oldCreationRate(creationRate), objectClk(), controlPU(), scoreClk(), speedClk(), doubleClk(), collisionClk(), shieldClk(), isShieldOn(false),
            n(1), score(0), txtCount(0),bestScore(0) {

    //setting dei layers del background
    layer1Texture.loadFromFile("Map/Background1.png");
    layer1Texture.setRepeated(true);
    layer1.setTexture(layer1Texture);
    layer1.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer2Texture.loadFromFile("Map/BG.png");
    layer2Texture.setRepeated(true);
    layer2.setTexture(layer2Texture);
    layer2.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer3Texture.loadFromFile("Map/Foregroung.png");
    layer3Texture.setRepeated(true);
    layer3.setTexture(layer3Texture);
    layer3.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    layer4Texture.loadFromFile("Map/middle.png");
    layer4Texture.setRepeated(true);
    layer4.setTexture(layer4Texture);
    layer4.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));

    //setting texture e sprite
    heroTexture1.loadFromFile("Textures/playerTexture.png");
    heroTexture2.loadFromFile("Textures/playerTextureUp.png");
    hero.setTexture(heroTexture1);
    heroTextureS1.loadFromFile("Textures/shieldPowerUpTexture.png");

    gameOverTexture.loadFromFile("Textures/GameOverScreen.png");
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(225,100);
    gameOver.setScale(0.8,0.8);

    //setting music
    gameMusic.openFromFile("Music/soundtrack.wav");
    gameMusic.setLoop(true);
    gameMusic.setVolume(10.f);
    gameMusic.play();

    gameOverBuffer.loadFromFile("Music/gameOverSound.wav");
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(21.f);

    collisionBuffer.loadFromFile("Music/collisionSound.wav");
    collisionSound.setBuffer(collisionBuffer);
    collisionSound.setVolume(22.f);

    powerUpBuffer.loadFromFile("Music/shieldSound.wav");
    powerUpSound.setBuffer(powerUpBuffer);
    powerUpSound.setVolume(20.f);

    shieldOnBuffer.loadFromFile("Music/shieldOn.wav");
    shieldOnSound.setBuffer(shieldOnBuffer);
    shieldOnSound.setVolume(20.f);

    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(map.getMapSize().y - (top + blockX));
}

void Game::update() {
    map.update();
    layer1.move(-speed.x, 0);
    layer2.move(-speed.x*0.9, 0);
    layer3.move(-speed.x*0.8, 0);
    layer4.move(-speed.x*0.7, 0);

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
    moveObject();
    moveHero();
    deleteObject();
    handleTxt();

    //TODO da implementare ma pesno basti dichiarare un oggetto game nei parametri di hero
    //per poi chiamare di continuo il metodo notify
}

const sf::Vector2f &Game::getSpeed() const {
    return speed;
}

int Game::getMaxY() const {
    return maxY;
}

void Game::render() {
    map.clear();
    map.draw(layer4);
    map.draw(layer3);
    map.draw(layer2);
    map.draw(layer1);

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
        for (auto &fire: firewalls)
            map.draw(*fire);
        for (auto &movFire: firewalls)
            map.draw(*movFire);
        map.draw(scoreTxt);
        map.draw(numScore);
        map.draw(lifeTxt);
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





