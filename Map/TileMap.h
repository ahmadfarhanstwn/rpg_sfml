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
    unsigned gridSizeU;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    unsigned layers;
    sf::Texture tileSheet;
    std::string textureFile; //the name of file for texture
    std::vector<std::vector<std::vector<Tile*>>> maps;

    sf::RectangleShape collisionBox;

    void clear();

    //Culling
    unsigned fromX;
    unsigned fromY;
    unsigned toX;
    unsigned toY;
    unsigned layer;

public:
    TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileSheet() const;


    //Functions
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    void updateCollision(Entity* entity);

    void update();
    void render(sf::RenderTarget& target, Entity* entity = nullptr);

    void addTile(const unsigned x, const unsigned y, const unsigned z, sf::IntRect& texture_rect, const bool collision, const short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

#endif // TILEMAP_H
