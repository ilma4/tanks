#ifndef TANKS_HANDLER_H
#define TANKS_HANDLER_H

#include <climits>
#include "entity.h"
#include "model/entities_fwd.h"

namespace Tanks::model {
class GameModel;  // TODO GameModel fwd
class BasicHandler {
public:
    explicit BasicHandler(GameModel &model_, Entity &entity);

    BasicHandler(const BasicHandler &) = delete;
    BasicHandler(BasicHandler &&) = delete;
    BasicHandler &operator=(const BasicHandler &) = delete;
    BasicHandler &operator=(BasicHandler &&) = delete;

    virtual ~BasicHandler() = default;

protected:
    GameModel &model;
    Entity &entity;
};

class ForegroundHandler : public BasicHandler {
public:
    explicit ForegroundHandler(GameModel &model_, ForegroundEntity &entity);

    void setBackground();
    void restoreBackground();
};

class MovableHandler : public ForegroundHandler {
public:
    explicit MovableHandler(GameModel &model_, MovableEntity &entity);

    [[nodiscard]] std::vector<const Entity *> look(Direction direction);
    void move(Direction direction, int speed);

protected:
    template <typename T>
    std::vector<const Entity *> nearest(Direction direction, T cond) {
        int dist = INT_MAX;
        std::vector<const Entity *> res;
        for (const auto *obj : look(direction)) {
            if (cond(obj)) {
                if (entity.dist(*obj) <= dist) {
                    if (entity.dist(*obj) == dist) {
                        res = {obj};
                    } else {
                        res.push_back(obj);
                    }
                }
            }
        }
        return res;
    }
};

class TankHandler : public MovableHandler {
public:
    explicit TankHandler(GameModel &model_, Tank &entity);

    void shoot();
};

class ProjectileHandler : public MovableHandler {
public:
    explicit ProjectileHandler(GameModel &model, MovableEntity &entity);

    [[nodiscard]] bool isBreakOnNextTick();
    [[nodiscard]] bool isBreakOnCreation();

protected:
    void destroyByBullet(Entity &other);
};

}  // namespace Tanks::model
#endif  // TANKS_HANDLER_H
