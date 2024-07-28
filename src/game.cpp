#include "game.hpp"

bool hasGameStarted;
int playerPoints;
int computerPoints;

DEV(float fpsDelay; int frameCount;)

bool HasGameStarted() {
    return hasGameStarted;
}

void InitWorld(World& world) {
    memset(&world, 0, sizeof(world));
    
    // Text Entities
    
    world.headerText.texture = GetStaticTextTexture(GetFontAsset(FONT_TTF), "Press space to start");
    world.headerText.size = HEADER_TEXT_RECT_SIZE;
    world.headerText.position = glm::vec2(HEADER_TEXT_RECT_CENTER.x - (HEADER_TEXT_RECT_SIZE.x / 2.0f), HEADER_TEXT_RECT_CENTER.y - (HEADER_TEXT_RECT_SIZE.y / 2.0f));
    
    InitDynamicText(world.playerPoints);
    world.playerPoints.position = PLAYER_POINTS_TEXT_POSITION;
    world.playerPoints.textSize = POINTS_TEXT_SIZE;
    SetDynamicText(world.playerPoints, "%i", 0);
    
    InitDynamicText(world.computerPoints);
    world.computerPoints.position = COMPUTER_POINTS_TEXT_POSITION;
    world.computerPoints.textSize = POINTS_TEXT_SIZE;
    SetDynamicText(world.computerPoints, "%i", 0);
    
DEV(
    fpsDelay = 0.0f;
    frameCount = 0;
    InitDynamicText(world.fps);
    world.fps.position = FPS_TEXT_POSITION;
    world.fps.textSize = FPS_TEXT_SIZE;
    SetDynamicText(world.fps, "%i", 0);
)
    
    // Line Entities
    
    world.borders[0].positionA = world.borders[3].positionB = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_BOTTOM_LEFT_Y);
    world.borders[0].positionB = world.borders[1].positionA = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_TOP_RIGHT_Y);
    world.borders[1].positionB = world.borders[2].positionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_TOP_RIGHT_Y);
    world.borders[2].positionB = world.borders[3].positionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_BOTTOM_LEFT_Y);
    
    // Paddle Entities
    
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    world.player.texture = GetSpriteAsset(PADDLE_SPRITE);
    world.player.size = GetTextureSize(world.player.texture);
    world.player.position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (world.player.size.y / 2.0f));
    
    world.computer.texture = GetSpriteAsset(PADDLE_SPRITE);
    world.computer.size = GetTextureSize(world.computer.texture);
    world.computer.position = glm::vec2(BOUNDS_TOP_RIGHT_X - world.computer.size.x - 10, paddleY - (world.computer.size.y / 2.0f));
    
    // Ball Entity
    
    world.ball.texture = GetSpriteAsset(BALL_SPRITE);
    world.ball.size = GetTextureSize(world.ball.texture);
    world.ball.position = glm::vec2(SCREEN_WIDTH - world.ball.size.x, SCREEN_HEIGHT + world.ball.size.y) / 2.0f;
    
    // GameState
    
    hasGameStarted = false;
    playerPoints = computerPoints = 0;
}

void StartGame(World& world) {
    world.ball.velocity = glm::normalize(glm::vec2(-1, 1)) * BALL_SPEED;
    hasGameStarted = true;
}

void EndGame(World& world) {
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    
    world.player.position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (world.player.size.y / 2.0f));
    world.player.velocity = glm::vec2(0, 0);
    
    world.computer.position = glm::vec2(BOUNDS_TOP_RIGHT_X - world.computer.size.x - 10, paddleY - (world.computer.size.y / 2.0f));
    world.computer.velocity = glm::vec2(0, 0);
    
    world.ball.position = glm::vec2(SCREEN_WIDTH - world.ball.size.x, SCREEN_HEIGHT + world.ball.size.y) / 2.0f;
    world.ball.velocity = glm::vec2(0, 0);
    
    hasGameStarted = false;
}

void SetPlayerVelocity(Entity& player, const Input& input) {
    if (input.up) {
        player.velocity.y = -PLAYER_SPEED;
    }
    else if (input.down) {
        player.velocity.y = PLAYER_SPEED;
    }
    else {
        player.velocity.y = 0.0;
    }
}

void SetComputerVelocity(Entity& computer, Entity& ball, float deltaTime) {
    float ballNextFrameY = ball.position.y + (ball.size.y / 2.0f) + (ball.velocity.y * deltaTime);
    float computerY = computer.position.y + (computer.size.y / 2.0f);
    
    if (glm::abs(ballNextFrameY - computerY) < COMPUTER_SPEED * deltaTime)
        computer.velocity = glm::vec2(0, 0);
    else if (ballNextFrameY > computerY)
        computer.velocity = glm::vec2(0, COMPUTER_SPEED);
    else
        computer.velocity = glm::vec2(0, -COMPUTER_SPEED);
}

int CheckEndGame(World& world) {
    float ballLeftX = world.ball.position.x;
    float ballRightX = ballLeftX + world.ball.size.x;
    
    if (ballLeftX < BOUNDS_BOTTOM_LEFT_X)
        return -1;
    if (ballRightX > BOUNDS_TOP_RIGHT_X)
        return 1;
    
    return 0;
}

void LogicTick(World& world, const Input& input, float deltaTime) {
    if (hasGameStarted) {
        SetPlayerVelocity(world.player, input);
        SetComputerVelocity(world.computer, world.ball, deltaTime);
        
        if (int point = CheckEndGame(world)) {
            if (point > 0)
                SetDynamicText(world.playerPoints, "%i", ++playerPoints);
            else
                SetDynamicText(world.computerPoints, "%i", ++computerPoints);
            EndGame(world);
        }
    }
    else if (input.space) {
        StartGame(world);
    }
    
    DEV(
    fpsDelay += deltaTime;
    frameCount++;
    
    if (fpsDelay > FPS_TICK_DELAY) {
        float fps = (1.0f / fpsDelay) * frameCount;
        SetDynamicText(world.fps, "%i", (int)fps);
        fpsDelay = 0.0f;
        frameCount = 0;
    }
    )
}

void PhysicsTick(World& world, float deltaTime) {
    MoveEntities(world, deltaTime);
    ResolveCollision(world);
}

void RenderTick(World& world) {
    ClearFrame();
    
    RenderEntity(world.player);
    RenderEntity(world.computer);
    RenderEntity(world.ball);
    
    for (int i = 0; i < 4; i++)
        RenderLine(world.borders[i]);
    
    if (!hasGameStarted)
        RenderEntity(world.headerText);
    
    RenderDynamicText(world.playerPoints, POINTS_TEXT_COLOR);
    RenderDynamicText(world.computerPoints, POINTS_TEXT_COLOR);
    
    DEV(RenderDynamicText(world.fps, FPS_TEXT_COLOR);)
    
    RenderFrame();
}

void DestroyWorld(World& world) {
    delete world.playerPoints.selection;
    delete world.computerPoints.selection;
    
    DEV(delete world.fps.selection;)
}
