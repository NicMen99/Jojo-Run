//
// Created by Niccolo on 28/03/2021.
//

#include "Entity.h"
#include "CollisionManager.h"

bool CollisionManager::collisionCheck(Entity *item1, Entity *item2, CollisionTag & tag1, CollisionTag & tag2) {
    /*
     * Se nessuna collisione in atto non fa niente
     */
    auto item1_rect = item1->getBounds();
    auto item2_rect = item2->getBounds();
    tag1 = CollisionTag::None;
    tag2 = CollisionTag::None;
    if (!item1->isEnabled() || !item2->isEnabled() || !item1_rect.intersects(item2_rect))
        return false;

    if(item1->getType() == EntityType::Hero && item2->getGroup() == EntityGroup::Platform)
        return checkHeroPlatform(item1, item2, tag1, tag2);

    if(item1->getGroup() == EntityGroup::Enemy && item2->getGroup() == EntityGroup::Platform)
        return checkEnemyPlatform(item1, item2, tag1, tag2);

    if(item1_rect.intersects(item2_rect)){
        tag1 = CollisionTag::Any;
        tag2 = CollisionTag::Any;
        return true;
    }
    return false;

}

bool CollisionManager::checkHeroPlatform(Entity * hero, Entity * platform, CollisionTag & hero_tag, CollisionTag & platform_tag) {
    /*
     * Se una collisione non in atto non fa niente
     */
    auto platform_rect = platform->getBounds();
    auto hero_rect = hero->getBounds();
    if (!hero->isEnabled() || !platform->isEnabled() || !hero_rect.intersects(platform_rect))
        return false;

    /*
     * Se una collisione precende già in atto non fa niente
     */
    auto hero_prev = hero->getPrevBounds();
    auto platform_prev = platform->getPrevBounds();
    if (hero_prev.intersects(platform_prev))
        return false;

    /*
     * Condizione 1 :
     *  Istante attuale : Top Hero sopra Top Piattaforma
     *  Istante precedente : Bottom Hero sopra Top Piattaforma
     *  Collisione
     */
    if (hero_rect.top < platform_rect.top && (hero_prev.top + hero_prev.height) <= platform_prev.top) {
        hero_tag = CollisionTag::Bottom;
        platform_tag = CollisionTag::Top;
        return true;
    }

    /*
     * Condizione 2 :
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sotto Bottom Piattaforma
     */
    if (hero_rect.top > platform_rect.top && hero_prev.top >= (platform_prev.top + platform_prev.height)) {
        hero_tag = CollisionTag::Top;
        platform_tag = CollisionTag::Bottom;
        return true;
    }

    return false;
}

bool CollisionManager::checkEnemyPlatform(Entity *enemy, Entity *platform, CollisionTag &enemy_tag, CollisionTag &platform_tag) {
    /*
     * Se una collisione non in atto non fa niente
     */
    auto platform_rect = platform->getBounds();
    auto enemy_rect = enemy->getBounds();
    if (!enemy->isEnabled() || !platform->isEnabled() || !enemy_rect.intersects(platform_rect))
        return false;

    /*
     * Se una collisione precende già in atto non fa niente
     */
    auto enemy_prev = enemy->getPrevBounds();
    auto platform_prev = platform->getPrevBounds();
    if (enemy_prev.intersects(platform_prev))
        return false;

    if (enemy_rect.top < platform_rect.top && (enemy_prev.top + enemy_prev.height) <= platform_prev.top) {
        enemy_tag = CollisionTag::Bottom;
        platform_tag = CollisionTag::Top;
        return true;
    }

    return false;
}

std::shared_ptr<sf::FloatRect> CollisionManager::intersectionRect(Entity *hero, Entity *platform) {
    auto new_rect = std::make_shared<sf::FloatRect> (0,0,0,0);
    new_rect->top = std::max(hero->getBounds().top, platform->getBounds().top);
    new_rect->left = std::max(hero->getBounds().left, platform->getBounds().left);
    new_rect->height= std::min(hero->getBounds().top + hero->getBounds().height, platform->getBounds().top + platform->getBounds().height) - new_rect->top;
    new_rect->width = std::min(hero->getBounds().left + hero->getBounds().width, platform->getBounds().left + platform->getBounds().width) - new_rect->left;
    return new_rect;
}

