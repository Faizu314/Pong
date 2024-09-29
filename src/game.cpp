#include "game.hpp"

static World _world;
static bool _hasGameStarted;
static int _playerPoints;
static int _computerPoints;

DEV(float _fpsDelay; int _frameCount;)

bool HasGameStarted() {
    return _hasGameStarted;
}

void InitGame(SDL_Window* window) {
    InitRenderer(window);

    memset(&_world, 0, sizeof(_world));
    
    // Text Entities
    
    _world.HeaderText.Texture = GetStaticTextTexture(GetFontAsset(FONT_TTF), "Press space to start");
    _world.HeaderText.Size = HEADER_TEXT_RECT_SIZE;
    _world.HeaderText.Position = glm::vec2(HEADER_TEXT_RECT_CENTER.x - (HEADER_TEXT_RECT_SIZE.x / 2.0f), HEADER_TEXT_RECT_CENTER.y - (HEADER_TEXT_RECT_SIZE.y / 2.0f));
    
    InitDynamicText(_world._playerPoints, GetSpriteAsset(FONT_BITMAP_SPRITE));
    _world._playerPoints.Position = PLAYER_POINTS_TEXT_POSITION;
    _world._playerPoints.TextSize = POINTS_TEXT_SIZE;
    SetDynamicText(_world._playerPoints, "%i", 0);
    
    InitDynamicText(_world._computerPoints, GetSpriteAsset(FONT_BITMAP_SPRITE));
    _world._computerPoints.Position = COMPUTER_POINTS_TEXT_POSITION;
    _world._computerPoints.TextSize = POINTS_TEXT_SIZE;
    SetDynamicText(_world._computerPoints, "%i", 0);
    
DEV(
    _fpsDelay = 0.0f;
    _frameCount = 0;
    InitDynamicText(_world.Fps, GetSpriteAsset(FONT_BITMAP_SPRITE));
    _world.Fps.Position = FPS_TEXT_POSITION;
    _world.Fps.TextSize = FPS_TEXT_SIZE;
    SetDynamicText(_world.Fps, "%i", 0);
)
    
    // Line Entities
    
    _world.Borders[0].PositionA = _world.Borders[3].PositionB = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_BOTTOM_LEFT_Y);
    _world.Borders[0].PositionB = _world.Borders[1].PositionA = glm::vec2(BOUNDS_BOTTOM_LEFT_X, BOUNDS_TOP_RIGHT_Y);
    _world.Borders[1].PositionB = _world.Borders[2].PositionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_TOP_RIGHT_Y);
    _world.Borders[2].PositionB = _world.Borders[3].PositionA = glm::vec2(BOUNDS_TOP_RIGHT_X, BOUNDS_BOTTOM_LEFT_Y);
    
    // Paddle Entities
    
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    _world.Player.Texture = GetSpriteAsset(PADDLE_SPRITE);
    _world.Player.Size = GetTextureSize(_world.Player.Texture);
    _world.Player.Position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (_world.Player.Size.y / 2.0f));
    
    _world.Computer.Texture = GetSpriteAsset(PADDLE_SPRITE);
    _world.Computer.Size = GetTextureSize(_world.Computer.Texture);
    _world.Computer.Position = glm::vec2(BOUNDS_TOP_RIGHT_X - _world.Computer.Size.x - 10, paddleY - (_world.Computer.Size.y / 2.0f));
    
    // Ball Entity
    
    _world.Ball.Texture = GetSpriteAsset(BALL_SPRITE);
    _world.Ball.Size = GetTextureSize(_world.Ball.Texture);
    _world.Ball.Position = glm::vec2(SCREEN_WIDTH - _world.Ball.Size.x, SCREEN_HEIGHT + _world.Ball.Size.y) / 2.0f;
    
    // GameState
    
    _hasGameStarted = false;
    _playerPoints = _computerPoints = 0;
}

void StartGame() {
    _world.Ball.Velocity = glm::normalize(glm::vec2(-1, 1)) * BALL_SPEED;
    _hasGameStarted = true;
}

void EndGame() {
    float paddleY = (BOUNDS_TOP_RIGHT_Y + BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
    
    _world.Player.Position = glm::vec2(BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (_world.Player.Size.y / 2.0f));
    _world.Player.Velocity = glm::vec2(0, 0);
    
    _world.Computer.Position = glm::vec2(BOUNDS_TOP_RIGHT_X - _world.Computer.Size.x - 10, paddleY - (_world.Computer.Size.y / 2.0f));
    _world.Computer.Velocity = glm::vec2(0, 0);
    
    _world.Ball.Position = glm::vec2(SCREEN_WIDTH - _world.Ball.Size.x, SCREEN_HEIGHT + _world.Ball.Size.y) / 2.0f;
    _world.Ball.Velocity = glm::vec2(0, 0);
    
    _hasGameStarted = false;
}

void SetPlayerVelocity(Entity& player, const Input& input) {
    if (input.Up) {
        player.Velocity.y = -PLAYER_SPEED;
    }
    else if (input.Down) {
        player.Velocity.y = PLAYER_SPEED;
    }
    else {
        player.Velocity.y = 0.0;
    }
}

void SetComputerVelocity(Entity& computer, Entity& ball, float deltaTime) {
    float ballNextFrameY = ball.Position.y + (ball.Size.y / 2.0f) + (ball.Velocity.y * deltaTime);
    float computerY = computer.Position.y + (computer.Size.y / 2.0f);
    
    if (glm::abs(ballNextFrameY - computerY) < COMPUTER_SPEED * deltaTime)
        computer.Velocity = glm::vec2(0, 0);
    else if (ballNextFrameY > computerY)
        computer.Velocity = glm::vec2(0, COMPUTER_SPEED);
    else
        computer.Velocity = glm::vec2(0, -COMPUTER_SPEED);
}

int CheckEndGame() {
    float ballLeftX = _world.Ball.Position.x;
    float ballRightX = ballLeftX + _world.Ball.Size.x;
    
    if (ballLeftX < BOUNDS_BOTTOM_LEFT_X)
        return -1;
    if (ballRightX > BOUNDS_TOP_RIGHT_X)
        return 1;
    
    return 0;
}

void LogicTick(const Input& input, float deltaTime) {
    if (_hasGameStarted) {
        SetPlayerVelocity(_world.Player, input);
        SetComputerVelocity(_world.Computer, _world.Ball, deltaTime);
        
        if (int point = CheckEndGame()) {
            if (point > 0)
                SetDynamicText(_world._playerPoints, "%i", ++_playerPoints);
            else
                SetDynamicText(_world._computerPoints, "%i", ++_computerPoints);
            EndGame();
        }
    }
    else if (input.Space) {
        StartGame();
    }
    
DEV(
    _fpsDelay += deltaTime;
    _frameCount++;
    
    if (_fpsDelay > FPS_TICK_DELAY) {
        float fps = (1.0f / _fpsDelay) * _frameCount;
        SetDynamicText(_world.Fps, "%i", (int)fps);
        _fpsDelay = 0.0f;
        _frameCount = 0;
    }
)
}

void PhysicsTick(float deltaTime) {
    MoveEntities(_world, deltaTime);
    ResolveCollision(_world);
}

void RenderTick() {
    ClearFrame();
    
    RenderEntity(_world.Player);
    RenderEntity(_world.Computer);
    RenderEntity(_world.Ball);
    
    for (int i = 0; i < 4; i++)
        RenderLine(_world.Borders[i]);
    
    if (!_hasGameStarted)
        RenderEntity(_world.HeaderText);
    
    RenderDynamicText(_world._playerPoints, POINTS_TEXT_COLOR);
    RenderDynamicText(_world._computerPoints, POINTS_TEXT_COLOR);
    
    DEV(RenderDynamicText(_world.Fps, FPS_TEXT_COLOR));
    
    RenderFrame();
}

void DestroyGame() {
    delete _world._playerPoints.Selection;
    delete _world._computerPoints.Selection;
    
    DEV(delete _world.Fps.Selection);

    DestroyRenderer();
}
