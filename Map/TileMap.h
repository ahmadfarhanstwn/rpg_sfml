#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile*>>> maps;

public:
    TileMap(float grid_size, unsigned width, unsigned height);
    virtual ~TileMap();

    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z);
    void removeTile();
};

#endif // TILEMAP_H
