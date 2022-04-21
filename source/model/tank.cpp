#include "model/tank.h"
#include <cassert>
#include <queue>
#include "model/playable-tank.h"

namespace Tanks::model {
Tank::Tank(int left, int top, EntityType type_, Direction dir, GameMap &map_)
    : MovableEntity(left, top, TANK_SIZE, TANK_SIZE, type_, dir, map_) {
}

PlayableTank::PlayableTank(int left,
                           int top,
                           Direction dir,
                           GameMap &map_,
                           GameModel &model_)
    : Tank(left, top, EntityType::PLAYABLE_TANK, dir, map_),
      actionHandler(*this, model_) {
}

// hiding is a feature
void PlayableTank::move(Direction dir) {
    actionHandler.move(dir);
}

std::vector<const Entity *> Tank::look(Direction dir) {
    if (dir == Direction::DOWN) {
        if (getTop() + getHeight() == map.getHeight() - 1) {
            return {};
        }

        std::vector<const Entity *> res(getWidth());
        for (int col = getLeft(); col < getLeft() + getWidth(); col++) {
            res[col - getLeft()] =
                &map.getEntityByCoords(col, getTop() + getHeight());
        }
        return res;
    } else if (dir == Direction::UP) {
        if (getTop() == 0) {
            return {};
        }

        std::vector<const Entity *> res(getWidth());
        for (int col = getLeft(); col < getLeft() + getWidth(); col++) {
            res[col - getLeft()] = &map.getEntityByCoords(col, getTop() - 1);
        }
        return res;
    } else if (dir == Direction::RIGHT) {
        if (getLeft() + getWidth() == map.getWidth() - 1) {
            return {};
        }
        std::vector<const Entity *> res(getHeight());
        for (int row = getTop(); row < getTop() + getHeight(); row++) {
            res[row - getTop()] =
                &map.getEntityByCoords(getLeft() + getWidth(), row);
        }
        return res;
    } else {
        assert(dir == Direction::LEFT);
        std::vector<const Entity *> res(getHeight());
        if (getLeft() == 0) {
            return {};
        }
        for (int row = getTop(); row < getTop() + getHeight(); row++) {
            res[row - getTop()] = &map.getEntityByCoords(getLeft() - 1, row);
        }
        return res;
    }
}

void Tank::shoot() {
    // TODO
}
}  // namespace Tanks::model
