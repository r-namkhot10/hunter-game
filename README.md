# HUNTER

A console chase game written in C++. Evade a hunter that tracks you with
real-time seek AI — survive 20 turns to win.

## Features
- **Seek AI** — the hunter recalculates its direction toward the player
  every turn using vector math
- **Difficulty scaling** — the hunter gets faster every 10 turns
- **Win/lose conditions** — survive 20 turns to win; if the hunter gets
  within distance 1, you're caught
- Turn-based movement on a 2D coordinate plane

## How to Run
Requires a C++17 compiler.

**Visual Studio:** open the project and press `Ctrl+F5`

**g++:**
```
g++ -std=c++17 hunter-game.cpp -o hunter
./hunter
```

## How to Play
Type one key and press Enter:

| Key | Action |
|-----|--------|
| `w` | move up |
| `a` | move left |
| `s` | move down |
| `d` | move right |
| `q` | quit |

Each turn shows your position, the hunter's position, and the distance
between you.

**Tip:** running blindly gets you caught — run *away* from the hunter's
spawn point, not across its path.

## Technical Highlights
- **Custom `Vec2` math struct** with operator overloading (`+`, `-`, `*`),
  `length()`, `normalize()`, and `distanceTo()`
- **Const-correct methods** — every read-only operation is marked `const`
- **Seek behavior** in one line:
  `hunterPos = hunterPos + (playerPos - hunterPos).normalize() * hunterSpeed;`
- **Code reuse (DRY)** — refactored `distanceTo()` to build on the existing
  `operator-` instead of duplicating the math:

```cpp
// Before
float distanceTo(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y).length();
}

// After — reuses operator-
float distanceTo(const Vec2& other) const {
    return (*this - other).length();
}
```

## About This Project
This is my first complete C++ project. I built it while learning C++ with
Claude (AI) as my mentor — I tried to solve every problem myself first,
and asked for hints when I got stuck. Creating something playable from my
own imagination was one of the most satisfying moments I've had learning
to code.