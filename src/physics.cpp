#include "physics.hpp"

int sign(float v) {
    if (v > 0)
        return 1;
    if (v < 0)
        return -1;
    return 0;
}

void MoveEntities(World& world, float deltaTime) {
    world.player.position += world.player.velocity * deltaTime;
    world.computer.position += world.computer.velocity * deltaTime;
    world.ball.position += world.ball.velocity * deltaTime;
}

void ResolvePaddleWithWallCollision(Entity& paddle) {
    float paddleMaxY = BOUNDS_BOTTOM_LEFT_Y - paddle.size.y;
    float paddleMinY = BOUNDS_TOP_RIGHT_Y;
    
    if (paddle.position.y > paddleMaxY)
        paddle.position.y = paddleMaxY;
    else if (paddle.position.y < paddleMinY)
        paddle.position.y = paddleMinY;
}

void ResolveBallWithWallCollision(Entity& ball) {
    float ballMaxY = BOUNDS_BOTTOM_LEFT_Y - ball.size.y;
    float ballMinY = BOUNDS_TOP_RIGHT_Y;
    
    if (ball.position.y > ballMaxY)
        ball.position.y = ballMaxY;
    else if (ball.position.y < ballMinY)
        ball.position.y = ballMinY;
    else
        return;
    
    ball.velocity.y = -ball.velocity.y;
}

void ResolveBallWithPaddleCollision(Entity& ball, Entity& paddle) {
    bool isColliding =
        (ball.position.x < paddle.position.x + paddle.size.x)  &&
        (ball.position.x + ball.size.x > paddle.position.x)    &&
        (ball.position.y < paddle.position.y + paddle.size.y)  &&
        (ball.position.y + ball.size.y > paddle.position.y);
    
    if (!isColliding)
        return;
    
    float xDisp, yDisp;
    if (ball.velocity.x < 0.0f)
        xDisp = ball.position.x - (paddle.position.x + paddle.size.x);
    else
        xDisp = ball.position.x + ball.size.x - paddle.position.x;
    if (ball.velocity.y - paddle.velocity.y < 0.0f)
        yDisp = paddle.position.y + paddle.size.y - ball.position.y;
    else
        yDisp = paddle.position.y - (ball.position.y + ball.size.y);
    
    if (std::abs(xDisp) < std::abs(yDisp)) {
        ball.position.x -= xDisp;
        ball.velocity.x *= -1;
    }
    else {
        ball.position.y += yDisp;
        ball.velocity.y *= sign(ball.velocity.y) * sign(yDisp);
    }
    
    glm::vec2 paddleMid(paddle.position.x + (paddle.size.x / 2.0), paddle.position.y + (paddle.size.y / 2.0));
    glm::vec2 ballMid(ball.position.x + (ball.size.x / 2.0), ball.position.y + (ball.size.y / 2.0));
    glm::vec2 paddleVelNorm = paddle.velocity;
    if (paddleVelNorm.y != 0)
        paddleVelNorm.y = paddleVelNorm.y > 0.0 ? 1.0 : -1.0;
    
    ball.velocity = glm::normalize(ball.velocity) * REFLECTION_WEIGHT;
    ball.velocity += glm::normalize(ballMid - paddleMid) * PADDLE_DEFLECTION_WEIGHT;
    ball.velocity += paddleVelNorm * PADDLE_VELOCITY_WEIGHT;
    ball.velocity /= REFLECTION_WEIGHT + PADDLE_DEFLECTION_WEIGHT + PADDLE_VELOCITY_WEIGHT;
    ball.velocity = glm::normalize(ball.velocity) * BALL_SPEED;
}

void ResolveCollision(World& world) {
    ResolvePaddleWithWallCollision(world.player);
    ResolvePaddleWithWallCollision(world.computer);
    ResolveBallWithWallCollision(world.ball);
    ResolveBallWithPaddleCollision(world.ball, world.player);
    ResolveBallWithPaddleCollision(world.ball, world.computer);
}
