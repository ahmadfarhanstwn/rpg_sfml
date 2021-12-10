#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
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

TileMap::TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file)
{
    this->gridSizeF = grid_size;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->textureFile = texture_file;
    if (!this->tileSheet.loadFromFile(texture_file))
    {
        std::cout << "ERROR::TILEMAP::COULDN'T LOAD TEXTURE SHEET, " << texture_file << "\n";
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
    this->clear();
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
    return &this->tileSheet;
}

//Functions
void TileMap::saveToFile(const std::string file_name)
{
    /* Saves the entire tilemap to texture file
    Format:
        Basic:
        Size x y
        gridSize
        layers
        textureFile

    All tiles:
    gridPos x y, Texture rect x y, collision, type
     */

     std::ofstream out_file;

     out_file.open(file_name);

     if (out_file.is_open())
     {
         out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
         << this->gridSizeU << "\n"
         << this->layers << "\n"
         << this->textureFile << "\n";

         for (size_t x = 0; x < this->maxSize.x; x++)
        {
            for (size_t y = 0; y < this->maxSize.y; y++)
            {
                for (size_t z = 0; z < this->layers; z++)
                {
                    if (maps[x][y][z])
                        out_file << this->maps[x][y][z]->getAsString() << " ";
                }
            }
        }
     }
     else
     {
         std::cout << "ERROR::TileMap::saveToFile:: COULDN'T LOAD THE FILE NAME : " << file_name << "\n";
     }

     out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
    std::ifstream in_file;

     in_file.open(file_name);

     if (in_file.is_open())
     {
        sf::Vector2u size;
        unsigned gridSizeU = 0;
        unsigned layers = 0;

        //Basics
        in_file >> size.x >> size.y >> gridSizeU >> layers;

        //Tiles
        for (size_t x = 0; x < this->maxSize.x; x++)
        {
            for (size_t y = 0; y < this->maxSize.y; y++)
            {
                for (size_t z = 0; z < this->layers; z++)
                {
                    if (maps[x][y][z])
                        out_file << this->maps[x][y][z]->getAsString() << " ";
                }
            }
        }
     }
     else
     {
         std::cout << "ERROR::TileMap::saveToFile:: COULDN'T LOAD THE FILE NAME : " << file_name << "\n";
     }

     in_file.close();
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
