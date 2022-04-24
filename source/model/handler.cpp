#include "model/handler.h"
#include <model/game_model.h>
#include <cassert>
#include "model/projectile.h"

namespace Tanks::model {
BasicHandler::BasicHandler(GameModel &model_, Entity &entity_)
    : model(model_), entity(entity_) {
    assert(model.handlers.count(&entity) == 0);
    model.handlers[&entity] = this;
}

void BasicHandler::move([[maybe_unused]] Direction direction) {
    assert(false);
}

void BasicHandler::shoot() {
    assert(false);
}

std::vector<const Entity *> BasicHandler::look(Direction direction) {
    assert(false);
}

std::vector<const Entity *> MovableHandler::look(Direction direction) {
    auto &real_entity = static_cast<MovableEntity &>(entity);
    // retuns square [left, right) x [down, top)
    int left = -1;
    int top = -1;
    int right = -1;
    int down = 0;
    switch (direction) {
        case (Direction::UP):
            left = entity.getLeft();
            right = left + entity.getWidth();
            down = entity.getTop() - 1;
            top = down - real_entity.getSpeed();
            break;
        case (Direction::DOWN):
            left = entity.getLeft();
            right = left + entity.getWidth();
            top = entity.getTop() + entity.getHeight();
            down = top + real_entity.getSpeed();
            break;
        case (Direction::LEFT):
            right = entity.getLeft();
            left = right - real_entity.getSpeed();
            top = entity.getTop() - 1;
            down = top + entity.getHeight();
            break;
        case (Direction::RIGHT):
            left = entity.getLeft() + entity.getWidth();
            right = left + real_entity.getSpeed();
            top = entity.getTop() - 1;
            down = top + entity.getHeight();
            break;
    }

    std::vector<const Entity *> res;
    for (int row = down; row > top; row--) {
        for (int col = left; col < right; col++) {
            res.push_back(&model.getEntityByCoords(col, row));
        }
    }

    return res;
}

void ForegroundHandler::restoreBackground() {
    auto &real_entity = static_cast<ForegroundEntity &>(entity);

    for (int y = 0; y < entity.getHeight(); y++) {
        for (int x = 0; x < entity.getWidth(); x++) {
            model.map.insert(
                const_cast<Entity &>(*real_entity.background[y][x]));
            real_entity.background[y][x] = nullptr;
        }
    }
}

void ForegroundHandler::setBackground() {
    auto &real_entity = static_cast<ForegroundEntity &>(entity);

    int y0 = entity.getTop();
    int x0 = entity.getLeft();
    for (int y = entity.getTop(); y < entity.getTop() + entity.getHeight();
         y++) {
        for (int x = entity.getLeft(); x < entity.getLeft() + entity.getWidth();
             x++) {
            real_entity.background[y - y0][x - x0] =
                &model.getEntityByCoords(x, y);
        }
    }
    model.map.insert(entity);
}

ForegroundHandler::ForegroundHandler(GameModel &model_,
                                     ForegroundEntity &entity)
    : BasicHandler(model_, entity) {
}

MovableHandler::MovableHandler(GameModel &model_, MovableEntity &entity)
    : ForegroundHandler(model_, entity) {
}

void MovableHandler::move(Direction direction) {
    // TODO lock model
    auto &real_entity = static_cast<MovableEntity &>(entity);

    real_entity.setDirection(direction);
    real_entity.restoreBackground();
    for (int i = 0; i < real_entity.getSpeed(); i++) {
        switch (direction) {
            case Direction::UP:
                real_entity.setTop(entity.getTop() - 1);
                break;
            case Direction::LEFT:
                real_entity.setLeft(entity.getLeft() - 1);
                break;
            case Direction::DOWN:
                real_entity.setTop(entity.getTop() + 1);
                break;
            case Direction::RIGHT:
                real_entity.setLeft(entity.getLeft() + 1);
                break;
        }
    }
    real_entity.setBackground();
}

void TankHandler::shoot() {
    auto &real_entity = static_cast<Tank &>(entity);

    const std::unordered_map<Direction, int> DCOL = {
        {Tanks::model::Direction::UP, entity.getWidth() / 2},
        {Tanks::model::Direction::DOWN, entity.getWidth() / 2},
        {Tanks::model::Direction::RIGHT, entity.getWidth()},
        {Tanks::model::Direction::LEFT, -1}};

    const std::unordered_map<Direction, int> DROW = {
        {Tanks::model::Direction::UP, -1},
        {Tanks::model::Direction::DOWN, entity.getHeight()},
        {Tanks::model::Direction::RIGHT, entity.getHeight() / 2},
        {Tanks::model::Direction::LEFT, entity.getHeight() / 2}};

    model.addEntity(std::make_unique<Projectile>(
        entity.getLeft() + DCOL.at(real_entity.getDirection()),
        entity.getTop() + DROW.at(real_entity.getDirection()),
        real_entity.getDirection(), model));
}

TankHandler::TankHandler(GameModel &model_, Tank &entity)
    : MovableHandler(model_, entity) {
}
}  // namespace Tanks::model
