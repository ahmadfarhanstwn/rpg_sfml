#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height)
{
    this->gridSizeF = grid_size;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;

    this->maps.resize(this->maxSize.x);
    for (size_t x = 0; x < this->maxSize.x; x++)
    {
        this->maps.push_back(std::vector<std::vector<Tile*>>());
        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->maps[x].resize(this->maxSize.y);
            this->maps[x].push_back(std::vector<Tile*> ());
            for (size_t z = 0; z < this->layers; z++)
            {
                this->maps[x][y].resize(this->layers);
                this->maps[x][y].push_back(nullptr);
            }
        }
    }
}

TileMap::~TileMap()
{
    for (size_t x = 0; x < this->maxSize.x; x++)
    {
        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                delete this->maps[x][y][z];
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
    for (auto &x : this->maps)
    {
        for(auto &y : x)
        {
            for(auto *z : y)
            {
                if (z)
                    z->render(target);
            }
        }
    }
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
    /* Take three parameters and add a tile to the position if available */
    if (x < this->maxSize.x && x >= 0 &&
        y < this->maxSize.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        /* Check if the maps in that position is null */
        if (!this->maps[x][y][z])
        {
            // Ok to add
            this->maps[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF);
        }
    }
}

void TileMap::removeTile()
{

}
