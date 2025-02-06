#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int TILE_SIZE = 32;
const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 21;

// Pacman map (1 = wall, 0 = empty space, 2 = dot)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,2,1},
    {1,1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1,1},
    {0,0,0,0,1,2,1,2,2,2,2,2,2,2,1,2,1,0,0,0,0},
    {1,1,1,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,1,1},
    {0,0,0,0,1,2,1,2,2,2,2,2,2,2,1,2,1,0,0,0,0},
    {1,1,1,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

class Pacman {
public:
    Pacman() {
        shape.setRadius(TILE_SIZE / 3.0f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(TILE_SIZE, TILE_SIZE);
    }

    void move(sf::Vector2f direction) {
        shape.move(direction);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void setPosition(sf::Vector2f position) {
        shape.setPosition(position);
    }

private:
    sf::CircleShape shape;
};

class Ghost {
public:
    Ghost(sf::Color color, sf::Vector2f position) {
        shape.setSize(sf::Vector2f(TILE_SIZE-4, TILE_SIZE-4));
        shape.setFillColor(color);
        shape.setPosition(position);
    }

    void move(sf::Vector2f direction) {
        shape.move(direction);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void setPosition(sf::Vector2f position) {
        shape.setPosition(position);
    }

private:
    sf::RectangleShape shape;
};

bool isCollision(const sf::FloatRect& bounds, int x, int y) {
    return map[y][x] == 1;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Pacman Game");

    Pacman pacman;
    std::vector<Ghost> ghosts;
    ghosts.emplace_back(sf::Color::Red, sf::Vector2f(15 * TILE_SIZE, 4 * TILE_SIZE));
    ghosts.emplace_back(sf::Color::Cyan, sf::Vector2f(3 * TILE_SIZE, 4 * TILE_SIZE));
    ghosts.emplace_back(sf::Color::Green, sf::Vector2f(3 * TILE_SIZE, 10 * TILE_SIZE));

    ghosts.emplace_back(sf::Color::Yellow, sf::Vector2f(15 * TILE_SIZE, 14 * TILE_SIZE));
    ghosts.emplace_back(sf::Color::Magenta, sf::Vector2f(5 * TILE_SIZE, 15 * TILE_SIZE));




    sf::Clock clock;
    float speed = 100.0f;
    int score = 0;
    bool gameOver = false;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            // Handle player input
            sf::Vector2f direction(0.0f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                direction.y = -speed * deltaTime.asSeconds();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                direction.y = speed * deltaTime.asSeconds();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                direction.x = -speed * deltaTime.asSeconds();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                direction.x = speed * deltaTime.asSeconds();
            }

            // Check for collisions with walls
            sf::FloatRect nextBounds = pacman.getBounds();
            nextBounds.left += direction.x;
            nextBounds.top += direction.y;

            int leftTile = static_cast<int>(nextBounds.left / TILE_SIZE);
            int rightTile = static_cast<int>((nextBounds.left + nextBounds.width) / TILE_SIZE);
            int topTile = static_cast<int>(nextBounds.top / TILE_SIZE);
            int bottomTile = static_cast<int>((nextBounds.top + nextBounds.height) / TILE_SIZE);

            if (!isCollision(nextBounds, leftTile, topTile) &&
                !isCollision(nextBounds, rightTile, topTile) &&
                !isCollision(nextBounds, leftTile, bottomTile) &&
                !isCollision(nextBounds, rightTile, bottomTile)) {
                pacman.move(direction);
            }

            // Check for collected dots
            sf::Vector2f pacmanPos = pacman.getPosition();
            int pacmanX = static_cast<int>(pacmanPos.x / TILE_SIZE);
            int pacmanY = static_cast<int>(pacmanPos.y / TILE_SIZE);

            if (map[pacmanY][pacmanX] == 2) {
                map[pacmanY][pacmanX] = 0;
                score += 10;
            }

            // Move ghosts randomly
            int  tempspeed= 1;
            int dir = rand() % 4;
            for (auto& ghost : ghosts) {




                sf::Vector2f ghostDir(0.0f, 0.0f);
                switch (dir) {
                    std::cout<<"direction\n"<<dir;
                    case 0: ghostDir.x = -speed * deltaTime.asSeconds()* tempspeed; break;

                    case 1: ghostDir.x = speed * deltaTime.asSeconds()* tempspeed; break;
                    case 2: ghostDir.y = -speed * deltaTime.asSeconds()* tempspeed; break;
                    case 3: ghostDir.y = speed * deltaTime.asSeconds()* tempspeed; break;

                }

                sf::FloatRect ghostNextBounds = ghost.getBounds();
                ghostNextBounds.left += ghostDir.x;
                ghostNextBounds.top += ghostDir.y;

                int ghostLeftTile = static_cast<int>(ghostNextBounds.left / TILE_SIZE);
                int ghostRightTile = static_cast<int>((ghostNextBounds.left + ghostNextBounds.width) / TILE_SIZE);
                int ghostTopTile = static_cast<int>(ghostNextBounds.top / TILE_SIZE);
                int ghostBottomTile = static_cast<int>((ghostNextBounds.top + ghostNextBounds.height) / TILE_SIZE);

                if (!isCollision(ghostNextBounds, ghostLeftTile, ghostTopTile) &&
                    !isCollision(ghostNextBounds, ghostRightTile, ghostTopTile) &&
                    !isCollision(ghostNextBounds, ghostLeftTile, ghostBottomTile) &&
                    !isCollision(ghostNextBounds, ghostRightTile, ghostBottomTile)) {
                    tempspeed = 10;
                    ghost.move(ghostDir);
                }else{
                     tempspeed = dir * 10;
                     dir = rand() % 4;
                }
            }

            // Check for collisions with ghosts
            for (const auto& ghost : ghosts) {
                if (pacman.getBounds().intersects(ghost.getBounds())) {
                    gameOver = true;
                }
            }
        }

        // Render the game
        window.clear();
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == 1) {
                    sf::RectangleShape wall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    wall.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    wall.setFillColor(sf::Color::Blue);
                    window.draw(wall);
                } else if (map[y][x] == 2) {
                    sf::CircleShape dot(TILE_SIZE / 8.0f);
                    dot.setFillColor(sf::Color::White);
                    dot.setPosition(x * TILE_SIZE + TILE_SIZE / 2.0f - dot.getRadius(), y * TILE_SIZE + TILE_SIZE / 2.0f - dot.getRadius());
                    window.draw(dot);
                }
            }
        }
        pacman.draw(window);
        for (const auto& ghost : ghosts) {
            ghost.draw(window);
        }

        // Display score
        sf::Font font;
        if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setString("Score: " + std::to_string(score));
            scoreText.setCharacterSize(24);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);
            window.draw(scoreText);
        }

        // Display game over message
        if (gameOver) {
            sf::Font font;
            if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
                sf::Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setString("Game Over! Final Score: " + std::to_string(score));
                gameOverText.setCharacterSize(40);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 50);
                window.draw(gameOverText);
            }
        }

        window.display();
    }

    return 0;
}
