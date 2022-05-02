#ifndef TANKS_PLAYABLE_TANK_H
#define TANKS_PLAYABLE_TANK_H

#include <memory>
#include <queue>
#include "model/tank.h"

namespace Tanks::model {
class PlayableTank : public Tank {
public:
    explicit PlayableTank(int left_,
                          int top_,
                          Direction direction_,
                          std::unique_ptr<BasicHandler> handler_);

    explicit PlayableTank(int left, int top, Direction dir, GameModel &model);

    using MovableEntity::move;
    using MovableEntity::setDirection;
    using Tank::shoot;
};
}  // namespace Tanks::model
#endif  // TANKS_PLAYABLE_TANK_H
