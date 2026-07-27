#include <iostream>
#include <cmath>

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

void printStatus(const Vec2& player, const Vec2& hunter, int turn) {
    std::cout << "===== Turn " << turn << " =====\n"
        "Player Position: (" << player.x << ", " << player.y << ")\n"
        "Hunter Position: (" << hunter.x << ", " << hunter.y << ")\n"
        "Distance: " << player.distanceTo(hunter) << "\n";
}


int main() {
    Vec2 playerPos(0.0f, 0.0f);
    Vec2 hunterPos(10.0f, 10.0f);
    float hunterSpeed = 0.8f;
    int turn = 0;

    std::cout << "Welcome to the Hunter Game!\n"
         "Your goal is to avoid the hunter for as long as possible.\n"
         "The hunter will move towards you each turn.\n"
         "You can move in four directions: up, down, left, and right.\n"
         "The game ends when the hunter catches you.\n\n"
         "***How to Play***\n"
         "Controls: w = up, a = left, s = down, d = right, q = quit\n"
         "Player starts at (0, 0), Hunter starts at (10, 10)\n"
         "Good luck!\n\n";

    while (true) {
        turn++;

        if (turn % 10 == 0) {
            hunterSpeed += 0.5f;
            std::cout << "\n*** The hunter is getting faster! ***\n"
                "Hunter speed is now: " << hunterSpeed << "\n\n";
        }

        printStatus(playerPos, hunterPos, turn);

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

        moveToward(hunterPos, playerPos, hunterSpeed);

        if (playerPos.distanceTo(hunterPos) < 1) {
            std::cout << "\n*** GAME OVER ***\n"
                "You survived " << turn << " turns!\n\n"
                "*** Hunter caught you at ("
                << playerPos.x << ", " << playerPos.y << ") ***\n";
            break;
        }

        else if (turn == 20) {
            std::cout << "\n*** YOU WIN! ***\n"
                "You survived 20 turns!\n\n";
            break;
        }
    }
}