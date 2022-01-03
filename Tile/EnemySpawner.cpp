#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int x, int y, float gridSizeF, const sf::Texture& texture_sheet, const sf::IntRect& texture_rect,
                           int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
                           : Tile(TileTypes::ENEMYSPAWNER, x, y, gridSizeF, texture_sheet, texture_rect, false)
{
    this->enemyType = enemy_type;
    this->enemyAmount = enemy_amount;
    this->enemyTimeToSpawn = enemy_time_to_spawn;
    this->enemyMaxDistance = enemy_max_distance;
}

EnemySpawner::~EnemySpawner()
{
    //dtor
}

//Functions
const std::string EnemySpawner::getAsString() const
{
    std::stringstream ss;

    ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top
    << this->enemyType << this->enemyAmount << this->enemyTimeToSpawn << this->enemyMaxDistance;

    return ss.str();
}

void EnemySpawner::spawn()
{

}

void EnemySpawner::clear()
{

}

void EnemySpawner::update()
{

}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", playerPosition);

        target.draw(this->shape, shader);
    }
    else
    {
        target.draw(this->shape);
    }
}
