#include "game.hpp"

static World world;
static bool hasGameStarted;
static int PlayerPoints;
static int ComputerPoints;

DEV(float fpsDelay; int frameCount;)

bool HasGameStarted() {
    return hasGameStarted;
}

void InitGame(SDL_Window* window) {
    InitRenderer(window);

    memset(&world, 0, sizeof(world));
    
    // Text Entities
    
    world.HeaderText.Texture = GetStaticTextTexture(GetFontAsset(FONT_TTF), "Press space to start");
    world.HeaderText.Size = HEADER_TEXT_RECT_SIZE;
    world.HeaderText.Position = glm::vec2(HEADER_TEXT_RECT_CENTER.x - (HEADER_TEXT_RECT_SIZE.x / 2.0f), HEADER_TEXT_RECT_CENTER.y - (HEADER_TEXT_RECT_SIZE.y / 2.0f));
    
    InitDynamicText(world.PlayerPoints, GetSpriteAsset(FONT_BITMAP_SPRITE));
    world.PlayerPoints.Position = PLAYER_POINTS_TEXT_POSITION;
    world.PlayerPoints.TextSize = POINTS_TEXT_SIZE;
    SetDynamicText(world.PlayerPoints, "%i", 0);
    
    InitDynamicText(world.ComputerPoints, GetSpriteAsset(FONT_BITMAP_SPRITE));
    world.ComputerPoints.Position = COMPUTER_POINTS_TEXT_POSITION;
    world.ComputerPoints.TextSize = POINTS_TEXT_SIZE;
    SetDynamicText(world.ComputerPoints, "%i", 0);
    
DEV(
    fpsDelay = 0.0f;
    frameCount = 0;
    InitDynamicText(world.Fps, GetSpriteAsset(FONT_BITMAP_SPRITE));
    world.Fps.Position = FPS_TEXT_POSITION;
    world.Fps.TextSize = FPS_TEXT_SIZE;
    SetDynamicText(world.Fps, "%i", 0);
)
    
    // Line Entities
    
    world.Borders[0].PositionA = world.Borders[3].PositionB = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_BOTTOM_LEFT_Y);
    world.Borders[0].PositionB = world.Borders[1].PositionA = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_TOP_RIGHT_Y);
    world.Borders[1].PositionB = world.Borders[2].PositionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_TOP_RIGHT_Y);
    world.Borders[2].PositionB = world.Borders[3].PositionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_BOTTOM_LEFT_Y);
    
    // Paddle Entities
    
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    world.Player.Texture = GetSpriteAsset(PADDLE_SPRITE);
    world.Player.Size = GetTextureSize(world.Player.Texture);
    world.Player.Position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (world.Player.Size.y / 2.0f));
    
    world.Computer.Texture = GetSpriteAsset(PADDLE_SPRITE);
    world.Computer.Size = GetTextureSize(world.Computer.Texture);
    world.Computer.Position = glm::vec2(BOUNDS_TOP_RIGHT_X - world.Computer.Size.x - 10, paddleY - (world.Computer.Size.y / 2.0f));
    
    // Ball Entity
    
    world.Ball.Texture = GetSpriteAsset(BALL_SPRITE);
    world.Ball.Size = GetTextureSize(world.Ball.Texture);
    world.Ball.Position = glm::vec2(SCREEN_WIDTH - world.Ball.Size.x, SCREEN_HEIGHT + world.Ball.Size.y) / 2.0f;
    
    // GameState
    
    hasGameStarted = false;
    PlayerPoints = ComputerPoints = 0;
}

void StartGame() {
    world.Ball.Velocity = glm::normalize(glm::vec2(-1, 1)) * BALL_SPEED;
    hasGameStarted = true;
}

void EndGame() {
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    
    world.Player.Position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (world.Player.Size.y / 2.0f));
    world.Player.Velocity = glm::vec2(0, 0);
    
    world.Computer.Position = glm::vec2(BOUNDS_TOP_RIGHT_X - world.Computer.Size.x - 10, paddleY - (world.Computer.Size.y / 2.0f));
    world.Computer.Velocity = glm::vec2(0, 0);
    
    world.Ball.Position = glm::vec2(SCREEN_WIDTH - world.Ball.Size.x, SCREEN_HEIGHT + world.Ball.Size.y) / 2.0f;
    world.Ball.Velocity = glm::vec2(0, 0);
    
    hasGameStarted = false;
}

void SetPlayerVelocity(Entity& Player, const Input& input) {
    if (input.Up) {
        Player.Velocity.y = -PLAYER_SPEED;
    }
    else if (input.Down) {
        Player.Velocity.y = PLAYER_SPEED;
    }
    else {
        Player.Velocity.y = 0.0;
    }
}

void SetComputerVelocity(Entity& Computer, Entity& Ball, float deltaTime) {
    float ballNextFrameY = Ball.Position.y + (Ball.Size.y / 2.0f) + (Ball.Velocity.y * deltaTime);
    float computerY = Computer.Position.y + (Computer.Size.y / 2.0f);
    
    if (glm::abs(ballNextFrameY - computerY) < COMPUTER_SPEED * deltaTime)
        Computer.Velocity = glm::vec2(0, 0);
    else if (ballNextFrameY > computerY)
        Computer.Velocity = glm::vec2(0, COMPUTER_SPEED);
    else
        Computer.Velocity = glm::vec2(0, -COMPUTER_SPEED);
}

int CheckEndGame() {
    float ballLeftX = world.Ball.Position.x;
    float ballRightX = ballLeftX + world.Ball.Size.x;
    
    if (ballLeftX < BOUNDS_BOTTOM_LEFT_X)
        return -1;
    if (ballRightX > BOUNDS_TOP_RIGHT_X)
        return 1;
    
    return 0;
}

void LogicTick(const Input& input, float deltaTime) {
    if (hasGameStarted) {
        SetPlayerVelocity(world.Player, input);
        SetComputerVelocity(world.Computer, world.Ball, deltaTime);
        
        if (int point = CheckEndGame()) {
            if (point > 0)
                SetDynamicText(world.PlayerPoints, "%i", ++PlayerPoints);
            else
                SetDynamicText(world.ComputerPoints, "%i", ++ComputerPoints);
            EndGame();
        }
    }
    else if (input.Space) {
        StartGame();
    }
    
DEV(
    fpsDelay += deltaTime;
    frameCount++;
    
    if (fpsDelay > FPS_TICK_DELAY) {
        float fps = (1.0f / fpsDelay) * frameCount;
        SetDynamicText(world.Fps, "%i", (int)fps);
        fpsDelay = 0.0f;
        frameCount = 0;
    }
)
}

void PhysicsTick(float deltaTime) {
    MoveEntities(world, deltaTime);
    ResolveCollision(world);
}

void RenderTick() {
    ClearFrame();
    
    RenderEntity(world.Player);
    RenderEntity(world.Computer);
    RenderEntity(world.Ball);
    
    for (int i = 0; i < 4; i++)
        RenderLine(world.Borders[i]);
    
    if (!hasGameStarted)
        RenderEntity(world.HeaderText);
    
    RenderDynamicText(world.PlayerPoints, POINTS_TEXT_COLOR);
    RenderDynamicText(world.ComputerPoints, POINTS_TEXT_COLOR);
    
    DEV(RenderDynamicText(world.Fps, FPS_TEXT_COLOR));
    
    RenderFrame();
}

void DestroyGame() {
    delete world.PlayerPoints.Selection;
    delete world.ComputerPoints.Selection;
    
    DEV(delete world.Fps.Selection);

    DestroyRenderer();
}
