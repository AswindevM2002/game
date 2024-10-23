#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int grid[3][3] = {0};  // 0: Empty, 1: X, 2: O
int currentPlayer = 1; // Player 1 (X) starts

// Function to draw the grid
void drawGrid(sf::RenderWindow& window) {
    for (int i = 1; i < 3; i++) {
        sf::RectangleShape line(sf::Vector2f(300, 5));
        line.setFillColor(sf::Color::Black);
        
        // Horizontal lines
        line.setPosition(50, 100 * i + 50);
        window.draw(line);
        
        // Vertical lines
        line.setSize(sf::Vector2f(5, 300));
        line.setPosition(100 * i + 50, 50);
        window.draw(line);
    }
}

// Function to draw X and O on the grid
void drawMarks(sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(grid[i][j] == 1 ? "X" : "O");
                text.setCharacterSize(80);
                text.setFillColor(sf::Color::Black);
                text.setPosition(100 * j + 60, 100 * i + 50);
                window.draw(text);
            }
        }
    }
}

// Function to check for a win
int checkWin() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != 0)
            return grid[i][0];
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != 0)
            return grid[0][i];
    }
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != 0)
        return grid[0][0];
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != 0)
        return grid[0][2];
    
    return 0; // No winner yet
}

// Function to reset the game
void resetGame() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = 0;
        }
    }
    currentPlayer = 1; // Player 1 (X) starts again
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Tic-Tac-Toe");

    sf::Font font;
if (!font.loadFromFile("/usr/share/fonts/truetype/tlwg/TlwgTypo-Bold.ttf")) {
        cout << "Error loading font\n";
        return -1;
    }

    bool gameOver = false;
    int winner = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed && !gameOver) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    int row = (y - 50) / 100;
                    int col = (x - 50) / 100;

                    if (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == 0) {
                        grid[row][col] = currentPlayer;
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;

                        winner = checkWin();
                        if (winner != 0) {
                            gameOver = true;
                        }
                    }
                }
            }

            // Reset the game when space is pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                resetGame();
                gameOver = false;
            }
        }

        window.clear(sf::Color::White);
        
        drawGrid(window);
        drawMarks(window, font);

        if (gameOver) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::Red);
            text.setPosition(100, 350);
            text.setString("Player " + to_string(winner) + " wins! Press Space to reset.");
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
