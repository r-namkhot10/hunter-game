# HUNTER

A console chase game written in C++. Evade hunters that tracks you with
real-time seek AI — survive 20 turns to win.

## Features
- **Seek AI** — hunters recalculates their direction toward the player
  every turn using vector math
- **Difficulty scaling** — the hunters get faster every 10 turns
- **Win/lose conditions** — survive 20 turns to win; if any hunter gets
  within distance 1, you're caught
- Turn-based movement on a 2D coordinate plane
- Two hunters spawn at opposite corners and pursue simultaneously

## How to Run
Requires a C++17 compiler.

**MSVC (Developer PowerShell):**
```
cl main.cpp /EHsc /std:c++17 /Fe:hunter.exe
.\hunter.exe
```

**g++:**
```
g++ -std=c++17 main.cpp -o hunter
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

Each turn shows your position, each hunter' position, and the distance
between you.

**Tip:** running blindly gets you caught — run *away* from the hunters' spawn points, not across their paths.

## Technical Highlights
- **Custom `Vec2` math struct** with operator overloading (`+`, `-`, `*`),
  `length()`, `normalize()`, and `distanceTo()`
- **Const-correct methods** — every read-only operation is marked `const`
- **Seek behavior** in one line:
  `hunterPos = hunterPos + (playerPos - hunterPos).normalize() * hunterSpeed;`
- **Multiple enemies via `std::vector<Vec2>`** — the hunter loop scales to
  any number of pursuers without changing the AI code
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