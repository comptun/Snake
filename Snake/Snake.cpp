#include <iostream>
#include <SFML/Graphics.hpp>

int scene[40][40];

sf::RenderWindow window(sf::VideoMode(800, 800), "Snake");

sf::RectangleShape FOOD_TILE(sf::Vector2f(19, 19));
sf::RectangleShape SNAKE_TILE(sf::Vector2f(19, 19));

struct Player {
    int x;
    int y;
    int size;
    int direction;
    int head;
    Player(int x, int y, int size, int direction, int head) {
        this->x = x;
        this->y = y;
        this->size = size;
        this->direction = direction;
        this->head = head;
    }
} snakeData(20, 20, 4, 4, 4);

void display() {
    window.clear();
    for (int i = 0; i < 40; ++i) {
        for (int a = 0; a < 40; ++a) {
            if (scene[i][a] >= 1) {
                SNAKE_TILE.setPosition(20 * a, 20 * i);
                window.draw(SNAKE_TILE);
            }
            if (scene[i][a] == -1) {
                FOOD_TILE.setPosition(20 * a, 20 * i);
                window.draw(FOOD_TILE);
            }
        }
    }
    window.display();
}

int main()
{
    sf::Clock tick;

    int foodY, foodX;

    window.setFramerateLimit(100);

    srand(time(NULL));

    FOOD_TILE.setFillColor(sf::Color(255, 0, 0));
    SNAKE_TILE.setFillColor(sf::Color(0, 255, 0));

    for (int i = 1; i <= snakeData.size; ++i) {
        scene[snakeData.y][snakeData.x + i] = i;
    }

    display();

    while (window.isOpen())
    {
        sf::Event e;

        int foundFood = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            snakeData.direction = 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            snakeData.direction = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            snakeData.direction = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            snakeData.direction = 3;
        }

        
        for (int i = 0; i < 40; ++i) {
            for (int a = 0; a < 40; ++a) {
                if (scene[i][a] == -1) {
                    ++foundFood;
                }
                if (scene[i][a] <= snakeData.head - snakeData.size && scene[i][a] != -1) {
                    scene[i][a] = 0;
                }
                if (scene[i][a] == snakeData.head && tick.getElapsedTime().asSeconds() > 0.1) {
                    ++snakeData.head;
                    switch (snakeData.direction) {
                    case 1:
                        i == 0 ? scene[39][a] = snakeData.head : scene[i - 1][a] = snakeData.head;
                        break;
                    case 2:
                        a == 39 ? scene[i][0] = snakeData.head : scene[i][a + 1] = snakeData.head;
                        break;
                    case 3:
                        i == 39 ? scene[0][a] = snakeData.head : scene[i + 1][a] = snakeData.head;
                        break;
                    case 4:
                        a == 0 ? scene[i][39] = snakeData.head : scene[i][a - 1] = snakeData.head;
                        break;
                    }
                    display();
                    tick.restart();
                }
            }
        }

        if (foundFood == 0) {
            ++snakeData.size;
            bool searching = true;
            while (searching) {
                foodY = rand() % 40, foodX = rand() % 40;
                if (scene[foodY][foodX] == 0) {
                    scene[foodY][foodX] = -1;
                    searching = false;
                }
            }
        }

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }
    }
}