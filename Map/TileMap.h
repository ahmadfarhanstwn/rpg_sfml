#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

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
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileSheet() const;
    const int getLayerSize(const int x, const int y, const int layer) const;

    //Functions
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    void updateCollision(Entity* entity, const float& dt);

    void addTile(const int x, const int y, const int z, sf::IntRect& texture_rect, const bool collision, const short type);
    void removeTile(const int x, const int y, const int z);

    void update();
    void renderDeferred(sf::RenderTarget& target);
    void render(sf::RenderTarget& target, sf::Vector2i gridPosition, const bool show_collision = false);
};

#endif // TILEMAP_H
