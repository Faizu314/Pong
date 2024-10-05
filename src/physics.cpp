#include "physics.hpp"

namespace Game::Physics {

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

    static void ResolvePaddleWithWallCollision(Entity& paddle) {
        float paddleMaxY = Scene::BOUNDS_BOTTOM_LEFT_Y - paddle.Size.y;
        float paddleMinY = Scene::BOUNDS_TOP_RIGHT_Y;

        if (paddle.Position.y > paddleMaxY)
            paddle.Position.y = paddleMaxY;
        else if (paddle.Position.y < paddleMinY)
            paddle.Position.y = paddleMinY;
    }

    static void ResolveBallWithWallCollision(Entity& ball) {
        float ballMaxY = Scene::BOUNDS_BOTTOM_LEFT_Y - ball.Size.y;
        float ballMinY = Scene::BOUNDS_TOP_RIGHT_Y;

        if (ball.Position.y > ballMaxY)
            ball.Position.y = ballMaxY;
        else if (ball.Position.y < ballMinY)
            ball.Position.y = ballMinY;
        else
            return;

        ball.Velocity.y = -ball.Velocity.y;
    }

    static void ResolveBallWithPaddleCollision(Entity& ball, Entity& paddle) {
        bool isColliding =
            (ball.Position.x < paddle.Position.x + paddle.Size.x) &&
            (ball.Position.x + ball.Size.x > paddle.Position.x) &&
            (ball.Position.y < paddle.Position.y + paddle.Size.y) &&
            (ball.Position.y + ball.Size.y > paddle.Position.y);

        if (!isColliding)
            return;
        
        float ballSpeed = glm::length(ball.Velocity);

        float xDisp, yDisp;
        if (ball.Velocity.x < 0.0f)
            xDisp = ball.Position.x - (paddle.Position.x + paddle.Size.x);
        else
            xDisp = ball.Position.x + ball.Size.x - paddle.Position.x;
        if (ball.Velocity.y - paddle.Velocity.y < 0.0f)
            yDisp = paddle.Position.y + paddle.Size.y - ball.Position.y;
        else
            yDisp = paddle.Position.y - (ball.Position.y + ball.Size.y);

        if (std::abs(xDisp) < std::abs(yDisp)) {
            ball.Position.x -= xDisp;
            ball.Velocity.x *= -1;
        }
        else {
            ball.Position.y += yDisp;
            ball.Velocity.y *= sign(ball.Velocity.y) * sign(yDisp);
        }

        glm::vec2 paddleMid(paddle.Position.x + (paddle.Size.x / 2.0), paddle.Position.y + (paddle.Size.y / 2.0));
        glm::vec2 ballMid(ball.Position.x + (ball.Size.x / 2.0), ball.Position.y + (ball.Size.y / 2.0));
        glm::vec2 paddleVelNorm = paddle.Velocity;
        if (paddleVelNorm.y != 0)
            paddleVelNorm.y = paddleVelNorm.y > 0.0 ? 1.0 : -1.0;

        ball.Velocity = glm::normalize(ball.Velocity) * REFLECTION_WEIGHT;
        ball.Velocity += glm::normalize(ballMid - paddleMid) * PADDLE_DEFLECTION_WEIGHT;
        ball.Velocity += paddleVelNorm * PADDLE_VELOCITY_WEIGHT;
        ball.Velocity /= REFLECTION_WEIGHT + PADDLE_DEFLECTION_WEIGHT + PADDLE_VELOCITY_WEIGHT;
        ball.Velocity = glm::normalize(ball.Velocity) * ballSpeed * BALL_VELOCITY_DECAY;
    }

    void ResolveCollisions(World& world) {
        ResolvePaddleWithWallCollision(world.Player);
        ResolvePaddleWithWallCollision(world.Computer);
        ResolveBallWithWallCollision(world.Ball);
        ResolveBallWithPaddleCollision(world.Ball, world.Player);
        ResolveBallWithPaddleCollision(world.Ball, world.Computer);
    }
}
