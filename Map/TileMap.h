#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"
#include "EnemySpawner.h"

class Tile;
class Entity;
class EnemySpawner;

class TileMap
{
private:
    float gridSizeF;
    int gridSizeI;
    sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    int layers;
    sf::Texture tileSheet;
    std::string textureFile; //the name of file for texture
    std::vector<std::vector<std::vector<std::vector<Tile*>>>> maps;
    std::stack<Tile*> deferredRenderStack;

    sf::RectangleShape collisionBox;

    void clear();

    //Culling
    int fromX;
    int fromY;
    int toX;
    int toY;
    int layer;

public:
    TileMap(float grid_size, int width, int height, std::string texture_file);
    TileMap(std::string file_name);
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileSheet() const;
    const int getLayerSize(const int x, const int y, const int layer) const;
    const sf::Vector2i& getMaxSizeGrid() const;
    const sf::Vector2f& getMaxSizeF() const;
    const bool tileEmpty(const int x, const int y, const int z) const;
    const bool getType(const int x, const int y, const int z, const int type) const;

    //Functions
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    void update(Entity* entity, const float& dt);

    void addTile(const int x, const int y, const int z, sf::IntRect& texture_rect, const bool collision, const short type);
    void removeTile(const int x, const int y, const int z, const int type = -1);

    void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
    void render(sf::RenderTarget& target, sf::Vector2i gridPosition, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f(), const bool show_collision = false);
};

#endif // TILEMAP_H
