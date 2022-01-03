#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Tile.h"

class EnemySpawner : public Tile
{
private:
    int enemyType;
    int enemyAmount;
    int enemyTimeToSpawn;
    float enemyMaxDistance;

public:
    EnemySpawner(int x, int y, float gridSizeF, const sf::Texture& texture_sheet, const sf::IntRect& texture_rect,
                 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
    virtual ~EnemySpawner();

    //Functions
    const std::string getAsString() const;

    void spawn();
    void clear();

    void update();
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif // ENEMYSPAWNER_H
