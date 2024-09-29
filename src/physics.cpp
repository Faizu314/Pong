#include "physics.hpp"

int sign(float v) {
    if (v > 0)
        return 1;
    if (v < 0)
        return -1;
    return 0;
}

void MoveEntities(World& world, float deltaTime) {
    world.Player.Position += world.Player.Velocity * deltaTime;
    world.Computer.Position += world.Computer.Velocity * deltaTime;
    world.Ball.Position += world.Ball.Velocity * deltaTime;
}

void ResolvePaddleWithWallCollision(Entity& paddle) {
    float paddleMaxY = BOUNDS_BOTTOM_LEFT_Y - paddle.Size.y;
    float paddleMinY = BOUNDS_TOP_RIGHT_Y;
    
    if (paddle.Position.y > paddleMaxY)
        paddle.Position.y = paddleMaxY;
    else if (paddle.Position.y < paddleMinY)
        paddle.Position.y = paddleMinY;
}

void ResolveBallWithWallCollision(Entity& Ball) {
    float ballMaxY = BOUNDS_BOTTOM_LEFT_Y - Ball.Size.y;
    float ballMinY = BOUNDS_TOP_RIGHT_Y;
    
    if (Ball.Position.y > ballMaxY)
        Ball.Position.y = ballMaxY;
    else if (Ball.Position.y < ballMinY)
        Ball.Position.y = ballMinY;
    else
        return;
    
    Ball.Velocity.y = -Ball.Velocity.y;
}

void ResolveBallWithPaddleCollision(Entity& Ball, Entity& paddle) {
    bool isColliding =
        (Ball.Position.x < paddle.Position.x + paddle.Size.x)  &&
        (Ball.Position.x + Ball.Size.x > paddle.Position.x)    &&
        (Ball.Position.y < paddle.Position.y + paddle.Size.y)  &&
        (Ball.Position.y + Ball.Size.y > paddle.Position.y);
    
    if (!isColliding)
        return;
    
    float xDisp, yDisp;
    if (Ball.Velocity.x < 0.0f)
        xDisp = Ball.Position.x - (paddle.Position.x + paddle.Size.x);
    else
        xDisp = Ball.Position.x + Ball.Size.x - paddle.Position.x;
    if (Ball.Velocity.y - paddle.Velocity.y < 0.0f)
        yDisp = paddle.Position.y + paddle.Size.y - Ball.Position.y;
    else
        yDisp = paddle.Position.y - (Ball.Position.y + Ball.Size.y);
    
    if (std::abs(xDisp) < std::abs(yDisp)) {
        Ball.Position.x -= xDisp;
        Ball.Velocity.x *= -1;
    }
    else {
        Ball.Position.y += yDisp;
        Ball.Velocity.y *= sign(Ball.Velocity.y) * sign(yDisp);
    }
    
    glm::vec2 paddleMid(paddle.Position.x + (paddle.Size.x / 2.0), paddle.Position.y + (paddle.Size.y / 2.0));
    glm::vec2 ballMid(Ball.Position.x + (Ball.Size.x / 2.0), Ball.Position.y + (Ball.Size.y / 2.0));
    glm::vec2 paddleVelNorm = paddle.Velocity;
    if (paddleVelNorm.y != 0)
        paddleVelNorm.y = paddleVelNorm.y > 0.0 ? 1.0 : -1.0;
    
    Ball.Velocity = glm::normalize(Ball.Velocity) * REFLECTION_WEIGHT;
    Ball.Velocity += glm::normalize(ballMid - paddleMid) * PADDLE_DEFLECTION_WEIGHT;
    Ball.Velocity += paddleVelNorm * PADDLE_VELOCITY_WEIGHT;
    Ball.Velocity /= REFLECTION_WEIGHT + PADDLE_DEFLECTION_WEIGHT + PADDLE_VELOCITY_WEIGHT;
    Ball.Velocity = glm::normalize(Ball.Velocity) * BALL_SPEED;
}

void ResolveCollision(World& world) {
    ResolvePaddleWithWallCollision(world.Player);
    ResolvePaddleWithWallCollision(world.Computer);
    ResolveBallWithWallCollision(world.Ball);
    ResolveBallWithPaddleCollision(world.Ball, world.Player);
    ResolveBallWithPaddleCollision(world.Ball, world.Computer);
}
