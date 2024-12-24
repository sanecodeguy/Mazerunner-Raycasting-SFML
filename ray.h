#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <limits>
#include "map.h"
#include"sprite.h"
// constexpr float PI = 3.141592653589793f;
constexpr float MAX_RAYCASTING_STEPS = 60;
#include <cmath>
#include <limits>

struct shootray {
    bool hit = false;
    sf::Vector2f hitPos;
};
