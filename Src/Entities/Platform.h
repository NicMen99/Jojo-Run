//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_PLATFORM_H
#define JOJO_RUN_PLATFORM_H

#include "Entity.h"


class Platform : public Entity {
public:
    explicit Platform(std::string id);
    ~Platform() override;
    void init(EntityType type);

private:
    void event(GameEvent event, Entity *collider) override;
};


#endif //JOJO_RUN_PLATFORM_H
