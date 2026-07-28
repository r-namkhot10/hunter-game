#include <iostream>
#include <cmath>
#include <vector>

struct Vec2 {
    float x, y;

    Vec2(float x, float y) {
        this->x = x;
        this->y = y; 
    }

    Vec2 operator+(const Vec2& other) const {
        return { x + other.x, y + other.y };
    }

    Vec2 operator-(const Vec2& other) const {
        return { x - other.x, y - other.y };
    }

    Vec2 operator*(float k) const {
        return { x * k, y * k };
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalize() const {
        float len = length();
        if (len == 0.0f)
            return { 0.0f, 0.0f };
        return { x / len, y / len };
    }

    float distanceTo(const Vec2& other) const {
        return (*this - other).length();
    }
};

void moveToward(Vec2& mover, const Vec2& target, float speed) {
    Vec2 direction = (target - mover).normalize();
    mover = mover + direction * speed;
}

void printStatus(const Vec2& player, const std::vector<Vec2>& hunters, int turn) {
    std::cout << "===== Turn " << turn << " =====\n"
        "Player Position: (" << player.x << ", " << player.y << ")\n";
    for (int i = 0; i < hunters.size(); i++) {
        std::cout << "Hunter " << (i + 1) << " Position: (" << hunters[i].x << ", " << hunters[i].y << ")\n"
        "Distance: " << player.distanceTo(hunters[i]) << "\n";
    }
}

int main() {
    Vec2 playerPos(0.0f, 0.0f);

    std::vector<Vec2> hunters;
    hunters.push_back(Vec2(10.0f, 10.0f));
    hunters.push_back(Vec2(-10.0f, 10.0f));

    float hunterSpeed = 0.8f;
    int turn = 0;

    std::cout << "Welcome to the Hunter Game!\n"
         "Your goal is to avoid the hunters for as long as possible.\n"
         "The hunters will move towards you each turn.\n"
         "You can move in four directions: up, down, left, and right.\n"
         "The game ends when a hunter catches you.\n\n"
         "***How to Play***\n"
         "Controls: w = up, a = left, s = down, d = right, q = quit\n"
         "Player starts at (0, 0), Two hunters start at (10, 10) and (-10, 10)\n"
         "Good luck!\n\n";

    while (true) {
        turn++;

        if (turn % 10 == 0) {
            hunterSpeed += 0.5f;
            std::cout << "\n*** The hunters are getting faster! ***\n"
                "Hunter speed is now: " << hunterSpeed << "\n\n";
        }

        
        printStatus(playerPos, hunters, turn);
        

        char input;
        std::cin >> input;

        if (input == 'w') {
            playerPos.y += 1.0f;
        }

        else if (input == 'a') {
            playerPos.x -= 1.0f;
        }

        else if (input == 's') {
            playerPos.y -= 1.0f;
        }

        else if (input == 'd') {
            playerPos.x += 1.0f;
        }

        else if (input == 'q') {
            break;
        }
        
        for (int i = 0; i < hunters.size(); i++) {
            moveToward(hunters[i], playerPos, hunterSpeed);
        }

        bool caught = false;

        for (Vec2& hunterPos : hunters) {
            if (playerPos.distanceTo(hunterPos) < 1) {
                caught = true;
            }
        }

        if (caught) {
            std::cout << "\n*** GAME OVER ***\n"
                "You survived " << turn << " turns!\n\n"
                "*** Hunter caught you at ("
                << playerPos.x << ", " << playerPos.y << ") ***\n";
            break;
        }

        if (turn == 20) {
            std::cout << "\n*** YOU WIN! ***\n"
                "You survived 20 turns!\n\n";
            break;
        }
    }
}