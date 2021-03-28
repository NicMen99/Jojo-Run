//
// Created by Niccolo on 28/03/2021.
//

#include "Entity.h"
#include "CollisionManager.h"

bool CollisionManager::collisionCheck(Entity *item1, Entity *item2) {
    /*
     * Se nessuna collisione in atto non fa niente
     */
    auto item1_rect = item1->getBounds();
    auto item2_rect = item2->getBounds();
    if (!item1->isEnabled() || !item2->isEnabled() || !item1_rect.intersects(item2_rect))
        return false;

    if(item1->getType() == GameObjectType::Hero && item2->getType() == GameObjectType::Platform)
        return checkHeroPlatform(item1, item2);

    return  item1_rect.intersects(item2_rect);
}

bool CollisionManager::checkHeroPlatform(Entity *hero, Entity *platform) {
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
    if (hero_rect.top < platform_rect.top && (hero_prev.top + hero_prev.height) <= platform_prev.top)
        return true;

    /*
     * Condizione 2 :
     * Istante attuale : Top Hero sotto Top Piattaforma
     * Istante precedente : Top Hero sotto Bottom Piattaforma
     */
    if (hero_rect.top > platform_rect.top && hero_prev.top >= (platform_prev.top + platform_prev.height))
        return true;

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
