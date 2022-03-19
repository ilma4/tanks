#ifndef TANKS_TANK_H
#define TANKS_TANK_H

#include "game_map.h"
#include "movable_entity.h"

namespace Tanks::model {
class Tank : public MovableEntity {
public:
    explicit Tank(int left,
                  int top,
                  EntityType type_,
                  Direction dir,
                  GameMap &map_);

    [[nodiscard]] std::vector<const Entity *> look(Direction dir);

protected:
    void shoot();
};

class PlayableTank : public Tank {
public:
    PlayableTank(int left, int top, Direction dir, GameMap &map_);
    // TODO: ShootHandler or other solution for shooting

    using MovableEntity::move;
};
}  // namespace Tanks::model

#endif  // TANKS_TANK_H
