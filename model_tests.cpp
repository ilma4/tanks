#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cassert>
#include <iostream>
#include "doctest.h"
#include "model/blocks.h"
#include "model/game_model.h"
#include "model/projectile.h"

using namespace Tanks;
using namespace Tanks::model;
const std::array<Tanks::model::Direction, 4> DIRECTIONS = {
    Tanks::model::Direction::UP, Tanks::model::Direction::DOWN,
    Tanks::model::Direction::LEFT, Tanks::model::Direction::RIGHT};

TEST_CASE("Game creation") {
    Tanks::model::GameModel model;
    model.loadLevel(1);
    auto &brick00 = model.getEntityByCoords(TILE_SIZE, TILE_SIZE);

    CHECK(brick00.getType() == EntityType::FLOOR);
}

TEST_CASE("Single move") {
    Tanks::model::GameModel model;
    model.loadLevel(1);
    Tanks::model::Entity *brick00 =
        &model.getEntityByCoords(TILE_SIZE, TILE_SIZE);

    auto &real_tank = model.spawnPlayableTank(TILE_SIZE, TILE_SIZE);
    CHECK(real_tank.getLeft() == TILE_SIZE);
    CHECK(real_tank.getTop() == TILE_SIZE);
    auto &tank = static_cast<Tanks::model::Entity &>(real_tank);
    CHECK(&tank == &real_tank);

    for (auto &row : real_tank.snapshotBackground()) {
        for (auto *entity : row) {
            CHECK(entity != nullptr);
        }
    }

    real_tank.move(Tanks::model::Direction::DOWN);
    Tanks::model::Entity &ptr2 = model.getEntityByCoords(TILE_SIZE, TILE_SIZE);
    model.nextTick();

    CHECK(brick00 == &model.getEntityByCoords(TILE_SIZE, TILE_SIZE));
}

TEST_CASE("multiple moves") {
    Tanks::model::GameModel model;
    model.loadLevel(1);
    auto &realTank = model.spawnPlayableTank(TILE_SIZE, TILE_SIZE);
    auto left = realTank.look(Tanks::model::Direction::LEFT);
    CHECK(left[0] == left.back());
    CHECK(left[0] == &model.getEntityByCoords(0, TILE_SIZE));

    auto right = realTank.look(Tanks::model::Direction::RIGHT);
    CHECK(right[0] == right.back());
    CHECK(right[0]->getType() == Tanks::model::EntityType::FLOOR);

    // [0,48) : Tank
    // [0,56) : Block
    const int MOVES = 9;
    for (int i = 0; i < MOVES; i++) {
        realTank.move(Tanks::model::Direction::DOWN);
    }

    CHECK(realTank.getTop() == TILE_SIZE + MOVES * realTank.getSpeed());

    model.nextTick();
    right = realTank.look(Tanks::model::Direction::RIGHT);
    CHECK(right.back()->getType() == Tanks::model::EntityType::FLOOR);
}

TEST_CASE("Block check") {
    Tanks::model::GameModel model;
    model.loadLevel(1);
    {
        auto &block = model.getEntityByCoords(0, 0);
        CHECK(block.isBulletPassable() == false);
        CHECK(block.isTankPassable() == false);
        CHECK(block.isDestroyable() == false);
    }
    {
        auto &block = model.getEntityByCoords(100, 100);
        CHECK(block.getType() == Tanks::model::EntityType::FLOOR);
        CHECK(block.isDestroyable() == false);
        CHECK(block.isTankPassable() == true);
        CHECK(block.isBulletPassable() == true);
    }
}

TEST_CASE("Look for grass") {
    Tanks::model::GameModel model;
    model.loadLevel(1);
    auto &tank = model.spawnPlayableTank(80, 80);

    for (auto dir : DIRECTIONS) {
        for (auto &col : tank.look(dir)) {
            CHECK(col != nullptr);
            CHECK(col->getType() == Tanks::model::EntityType::FLOOR);
        }
    }
}

TEST_CASE("Tank simple shoot") {
    using namespace Tanks::model;
    using namespace Tanks;

    GameModel model;
    model.loadLevel(1);
    auto &tank = model.spawnPlayableTank(Tanks::TILE_SIZE, Tanks::TILE_SIZE);
    tank.setDirection(Tanks::model::Direction::RIGHT);
    tank.shoot();
    auto &bullet = static_cast<Projectile &>(
        model.getEntityByCoords(Tanks::TILE_SIZE + Tanks::TANK_SIZE,
                                Tanks::TILE_SIZE + Tanks::TANK_SIZE / 2));

    CHECK(bullet.getType() == Tanks::model::EntityType::BULLET);
    CHECK(bullet.getTop() == Tanks::TILE_SIZE + Tanks::TANK_SIZE / 2);
    CHECK(bullet.getLeft() == Tanks::TILE_SIZE + Tanks::TANK_SIZE);
    CHECK(bullet.getDirection() == tank.getDirection());

    model.nextTick();
    CHECK(bullet.getTop() == Tanks::TILE_SIZE + Tanks::TANK_SIZE / 2);
    CHECK(bullet.getLeft() == TILE_SIZE + TANK_SIZE + bullet.getSpeed());
}
