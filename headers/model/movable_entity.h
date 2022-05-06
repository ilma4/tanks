#ifndef TANKS_MOVABLE_ENTITY_H
#define TANKS_MOVABLE_ENTITY_H

#include "model/foreground_entity.h"

namespace Tanks::model {

class MovableEntity : public ForegroundEntity {
public:
    friend MovableHandler;

    explicit MovableEntity(int left,
                           int right,
                           std::unique_ptr<MovableHandler> handler,
                           Direction direction);

    explicit MovableEntity(int left,
                           int top,
                           int id,
                           std::unique_ptr<MovableHandler> handler,
                           Direction direction);

    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] virtual int getSpeed() const = 0;

protected:
    void setDirection(Direction dir);
    void move(Direction dir, int speed);  // TODO rename speed 2

private:
    Direction direction_;
};
}  // namespace Tanks::model

#endif  // TANKS_MOVABLE_ENTITY_H
