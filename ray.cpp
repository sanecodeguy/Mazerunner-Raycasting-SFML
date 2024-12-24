#include"ray.h"

shootray castray(const sf::Vector2f& position, float angle, const std::vector<sprite>& sprites, const Map& map) {
    constexpr float maxDistance = 4.0f;  
    constexpr float PI = 3.141592653589793f;
    constexpr int numRays = 2;  
    constexpr float FOV = 30.0f;  
    constexpr float tolerance = .2f;  

    shootray result;
    result.hit = false;  

    float sprite_height = 1.3f;
    float sprite_width = sprite_height;

    
    float startAngle = angle - (FOV / 2);
    float angleIncrement = FOV / (numRays - 1);

    
    for (int i = 0; i < numRays; ++i) {
        float currentAngle = startAngle + (i * angleIncrement);
        float radian = currentAngle * (PI / 180.0f);
        sf::Vector2f rayDir(cos(radian), sin(radian));
        sf::Vector2f rayPos = position;

        
        for (float distance = 0.0f; distance < maxDistance; distance += 0.5f) {
            sf::Vector2f currentRayPos = rayPos + rayDir * distance;

            
            if (map.getmapcell(static_cast<int>(currentRayPos.x), static_cast<int>(currentRayPos.y)) == 1 ||
                map.getmapcell(static_cast<int>(currentRayPos.x), static_cast<int>(currentRayPos.y)) == 2) {
                break;  
            }
        }

        
        for (const auto& sprite : sprites) {
            
            sf::Vector2f toSprite = sprite.position - rayPos;

            
            float projectionLength = toSprite.x * rayDir.x + toSprite.y * rayDir.y;

            
            if (projectionLength > 0 && projectionLength < maxDistance) {
                
                sf::Vector2f closestPoint = rayPos + rayDir * projectionLength;

                
                float left = sprite.position.x - sprite_width / 2;
                float right = sprite.position.x + sprite_width / 2;
                float top = sprite.position.y - sprite_height / 2;
                float bottom = sprite.position.y + sprite_height / 2;

                if (closestPoint.x >= left - tolerance && closestPoint.x <= right + tolerance &&
                    closestPoint.y >= top - tolerance && closestPoint.y <= bottom + tolerance) {
                    result.hit = true;
                    result.hitPos = sprite.position;  
                    return result;  
                }
            }
        }
    }

    result.hit = false;  
    return result;
}
