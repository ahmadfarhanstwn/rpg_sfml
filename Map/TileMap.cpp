#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height)
{
    this->gridSizeF = grid_size;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    if (!this->tileSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
    {
        std::cout << "ERROR::TILEMAP::COULDN'T LOAD TEXTURE SHEET, 'grass1.png'" << "\n";
    }

    this->maps.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < this->maxSize.x; x++)
    {
        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->maps[x].resize(this->maxSize.y, std::vector<Tile*> ());
            for (size_t z = 0; z < this->layers; z++)
            {
                this->maps[x][y].resize(this->layers, nullptr);
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
//    delete this->textureSheet;
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
    return &this->tileSheet;
}

//Functions
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

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, sf::IntRect& texture_rect)
{
    /* Take three parameters and add a tile to the position if available */
    if (x < this->maxSize.x && x >= 0 &&
        y < this->maxSize.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        /* Check if the maps in that position is not null */
        if (!this->maps[x][y][z])
        {
            // Ok to add
            this->maps[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    /* Take three parameters and remove a tile from the position if available */
    if (x < this->maxSize.x && x >= 0 &&
        y < this->maxSize.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        /* Check if the maps in that position is not null */
        if (this->maps[x][y][z])
        {
            // Ok to remove
            delete this->maps[x][y][z];
            this->maps[x][y][z] = nullptr;
        }
    }
}
