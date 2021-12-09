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
    sf::Texture tileSheet;
    std::vector<std::vector<std::vector<Tile*>>> maps;

public:
    TileMap(float grid_size, unsigned width, unsigned height);
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileSheet() const;


    //Functions
    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z, sf::IntRect& texture_rect);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

#endif // TILEMAP_H
