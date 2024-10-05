#include "game.hpp"

namespace Game {

    static World _world;
    static bool _hasGameStarted;
    static int _playerPoints;
    static int _computerPoints;

    DEV(float _fpsDelay; int _frameCount;)

    bool HasGameStarted() {
        return _hasGameStarted;
    }

    void Init(SDL_Window* window) {
        Renderer::InitRenderer(window);

        Assets::DynamicFontAsset* dynamicFont = 
            Assets::CreateDynamicFontAsset(Renderer::GetSpriteAsset(Assets::FONT_BITMAP_SPRITE), Assets::FONT_META);

        memset(&_world, 0, sizeof(_world));

        // Text Entities

        _world.HeaderText.Texture = Renderer::GetStaticTextTexture(Assets::GetFontAsset(Assets::FONT_TTF), "Press space to start");
        _world.HeaderText.Size = Scene::HEADER_TEXT_RECT_SIZE;
        _world.HeaderText.Position = glm::vec2(Scene::HEADER_TEXT_RECT_CENTER.x - (Scene::HEADER_TEXT_RECT_SIZE.x / 2.0f), Scene::HEADER_TEXT_RECT_CENTER.y - (Scene::HEADER_TEXT_RECT_SIZE.y / 2.0f));

        _world.PlayerPoints.DynamicFont = dynamicFont;
        _world.PlayerPoints.Position = Scene::PLAYER_POINTS_TEXT_POSITION;
        _world.PlayerPoints.TextSize = Scene::POINTS_TEXT_SIZE;
        SetDynamicText(_world.PlayerPoints, "%i", 0);

        _world.ComputerPoints.DynamicFont = dynamicFont;
        _world.ComputerPoints.Position = Scene::COMPUTER_POINTS_TEXT_POSITION;
        _world.ComputerPoints.TextSize = Scene::POINTS_TEXT_SIZE;
        SetDynamicText(_world.ComputerPoints, "%i", 0);

        DEV(
            _fpsDelay = 0.0f;
            _frameCount = 0;
            _world.Fps.DynamicFont = dynamicFont;
            _world.Fps.Position = Scene::FPS_TEXT_POSITION;
            _world.Fps.TextSize = Scene::FPS_TEXT_SIZE;
            SetDynamicText(_world.Fps, "%i", 0);
        )

        // Line Entities

        _world.Borders[0].PositionA = _world.Borders[3].PositionB = glm::vec2(Scene::BOUNDS_BOTTOM_LEFT_X, Scene::BOUNDS_BOTTOM_LEFT_Y);
        _world.Borders[0].PositionB = _world.Borders[1].PositionA = glm::vec2(Scene::BOUNDS_BOTTOM_LEFT_X, Scene::BOUNDS_TOP_RIGHT_Y);
        _world.Borders[1].PositionB = _world.Borders[2].PositionA = glm::vec2(Scene::BOUNDS_TOP_RIGHT_X, Scene::BOUNDS_TOP_RIGHT_Y);
        _world.Borders[2].PositionB = _world.Borders[3].PositionA = glm::vec2(Scene::BOUNDS_TOP_RIGHT_X, Scene::BOUNDS_BOTTOM_LEFT_Y);

        // Paddle Entities

        float paddleY = (Scene::BOUNDS_TOP_RIGHT_Y + Scene::BOUNDS_BOTTOM_LEFT_Y) / 2.0f;
        _world.Player.Texture = Renderer::GetSpriteAsset(Assets::PADDLE_SPRITE);
        _world.Player.Size = Renderer::GetTextureSize(_world.Player.Texture);
        _world.Player.Position = glm::vec2(Scene::BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (_world.Player.Size.y / 2.0f));

        _world.Computer.Texture = Renderer::GetSpriteAsset(Assets::PADDLE_SPRITE);
        _world.Computer.Size = Renderer::GetTextureSize(_world.Computer.Texture);
        _world.Computer.Position = glm::vec2(Scene::BOUNDS_TOP_RIGHT_X - _world.Computer.Size.x - 10, paddleY - (_world.Computer.Size.y / 2.0f));

        // Ball Entity

        _world.Ball.Texture = Renderer::GetSpriteAsset(Assets::BALL_SPRITE);
        _world.Ball.Size = Renderer::GetTextureSize(_world.Ball.Texture);
        _world.Ball.Position = glm::vec2(Screen::WIDTH - _world.Ball.Size.x, Screen::HEIGHT + _world.Ball.Size.y) / 2.0f;

        // GameState

        _hasGameStarted = false;
        _playerPoints = _computerPoints = 0;
    }

    void StartGame() {
        _world.Ball.Velocity = glm::normalize(glm::vec2(-1, 1)) * BALL_SPEED;
        _hasGameStarted = true;
    }

    void EndGame() {
        float paddleY = (Scene::BOUNDS_TOP_RIGHT_Y + Scene::BOUNDS_BOTTOM_LEFT_Y) / 2.0f;

        _world.Player.Position = glm::vec2(Scene::BOUNDS_BOTTOM_LEFT_X + 10, paddleY - (_world.Player.Size.y / 2.0f));
        _world.Player.Velocity = glm::vec2(0, 0);

        _world.Computer.Position = glm::vec2(Scene::BOUNDS_TOP_RIGHT_X - _world.Computer.Size.x - 10, paddleY - (_world.Computer.Size.y / 2.0f));
        _world.Computer.Velocity = glm::vec2(0, 0);

        _world.Ball.Position = glm::vec2(Screen::WIDTH - _world.Ball.Size.x, Screen::HEIGHT + _world.Ball.Size.y) / 2.0f;
        _world.Ball.Velocity = glm::vec2(0, 0);

        _hasGameStarted = false;
    }

    void SetPlayerVelocity(Entity& player, const Input::InputKeys& input) {
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

        if (ballLeftX < Scene::BOUNDS_BOTTOM_LEFT_X)
            return -1;
        if (ballRightX > Scene::BOUNDS_TOP_RIGHT_X)
            return 1;

        return 0;
    }

    void LogicTick(const Input::InputKeys& input, float deltaTime) {
        if (_hasGameStarted) {
            SetPlayerVelocity(_world.Player, input);
            SetComputerVelocity(_world.Computer, _world.Ball, deltaTime);

            if (int point = CheckEndGame()) {
                if (point > 0)
                    SetDynamicText(_world.PlayerPoints, "%i", ++_playerPoints);
                else
                    SetDynamicText(_world.ComputerPoints, "%i", ++_computerPoints);
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
                float fps = _frameCount / _fpsDelay;
                SetDynamicText(_world.Fps, "%i", (int)fps);
                _fpsDelay = 0.0f;
                _frameCount = 0;
            }
        )
    }

    void PhysicsTick(float deltaTime) {
        Physics::MoveEntities(_world, deltaTime);
        Physics::ResolveCollisions(_world);
    }

    void RenderTick() {
        Renderer::ClearFrame();

        Renderer::RenderEntity(_world.Player);
        Renderer::RenderEntity(_world.Computer);
        Renderer::RenderEntity(_world.Ball);

        for (int i = 0; i < 4; i++)
            Renderer::RenderLine(_world.Borders[i]);

        if (!_hasGameStarted)
            Renderer::RenderEntity(_world.HeaderText);

        Renderer::RenderDynamicText(_world.PlayerPoints, Scene::POINTS_TEXT_COLOR);
        Renderer::RenderDynamicText(_world.ComputerPoints, Scene::POINTS_TEXT_COLOR);

        DEV(Renderer::RenderDynamicText(_world.Fps, Scene::FPS_TEXT_COLOR));

        Renderer::RenderFrame();
    }

    void Destroy() {
        delete _world.PlayerPoints.Selection;
        delete _world.ComputerPoints.Selection;

        DEV(delete[] _world.Fps.Selection);

        Renderer::DestroyRenderer();
    }
}
