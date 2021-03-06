#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
    if (!this->maps.empty())
    {
        for (int x = 0; x < this->maps.size(); x++)
        {
            for (int y = 0; y < this->maps[x].size(); y++)
            {
                for (int z = 0; z < this->maps[x][y].size(); z++)
                {
                    for(size_t k = 0; k < this->maps[x][y][z].size(); k++)
                    {
                        delete this->maps[x][y][z][k];
                        this->maps[x][y][z][k] = nullptr;
                    }
                    this->maps[x][y][z].clear();
                }
                this->maps[x][y].clear();
            }
            this->maps[x].clear();
        }
        this->maps.clear();
    }
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file)
{
    this->gridSizeF = grid_size;
    this->gridSizeI = static_cast<int>(this->gridSizeF);
    this->maxSizeWorldGrid.x = width;
    this->maxSizeWorldGrid.y = height;
    this->maxSizeWorldF.x = static_cast<float>(width) * grid_size;
    this->maxSizeWorldF.y = static_cast<float>(height) * grid_size;
    this->layers = 1;
    this->textureFile = texture_file;
    if (!this->tileSheet.loadFromFile(texture_file))
    {
        std::cout << "ERROR::TILEMAP::COULDN'T LOAD TEXTURE SHEET, " << texture_file << "\n";
    }

    this->fromX = 0;
    this->fromY = 0;
    this->toX = 0;
    this->toY = 0;
    this->layer = 0;

    this->maps.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
    for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
    {
        for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
        {
            this->maps[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>> ());
            for (int z = 0; z < this->layers; z++)
            {
                this->maps[x][y].resize(this->layers, std::vector<Tile*>());
            }
        }
    }

    this->collisionBox.setSize(sf::Vector2f(grid_size, grid_size));
    this->collisionBox.setFillColor(sf::Color(0,0,255,50));
}

TileMap::TileMap(std::string file_name)
{
    this->fromX = 0;
    this->fromY = 0;
    this->toX = 0;
    this->toY = 0;
    this->layer = 0;

    this->loadFromFile(file_name);

    this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->collisionBox.setFillColor(sf::Color(0,0,255,50));
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

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
    if (x >= 0 && x < static_cast<int>(this->maps.size()))
    {
        if (y >= 0 && y < static_cast<int>(this->maps[x].size()))
        {
            if (layer >= 0 && layer < static_cast<int>(this->maps[x][y].size()))
            {
                return this->maps[x][y][layer].size();
            }
        }
    }
    return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
    return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
    return this->maxSizeWorldF;
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
    if (x >= 0 && x < this->maxSizeWorldGrid.x &&
        y >= 0 && y < this->maxSizeWorldGrid.y &&
        z >= 0 && z < this->layers)
    {
        return this->maps[x][y][z].empty();
    }

    return false;
}

const bool TileMap::getType(const int x, const int y, const int z, const int type) const
{
    return this->maps[x][y][z].back()->getType() == type;
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
    gridPos.x, gridPos.y, layers, TextureRect.x, TextureRect.y, collision, type
     */

     std::ofstream out_file;

     out_file.open(file_name);

     if (out_file.is_open())
     {
         out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
         << this->gridSizeI << "\n"
         << this->layers << "\n"
         << this->textureFile << "\n";

         for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
        {
            for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
            {
                for (int z = 0; z < this->layers; z++)
                {
                    if (!maps[x][y][z].empty())
                    {
                        for (size_t k = 0; k < this->maps[x][y][z].size(); k++)
                        {
                            out_file << x << " " << y << " " << z << " " << this->maps[x][y][z][k]->getAsString() << " ";
                        }
                    }
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
        int gridSize = 0;
        int layers = 0;
        std::string textureFiles = "";
        int x = 0;
        int y = 0;
        int z = 0;
        int trX = 0;
        int trY = 0;
        bool collision = false;
        short type = 0;

        //Basics
        in_file >> size.x >> size.y >> gridSize >> layers >> textureFiles;

        //Tiles
        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeI = gridSize;
        this->maxSizeWorldGrid.x = size.x;
        this->maxSizeWorldGrid.y = size.y;
        this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
        this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
        this->layers = layers;
        this->textureFile = textureFiles;

        this->clear();

        this->maps.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
        for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
        {
            for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
            {
                this->maps[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>> ());
                for (int z = 0; z < this->layers; z++)
                {
                    this->maps[x][y].resize(this->layers, std::vector<Tile*>());
                }
            }
        }

        if (!this->tileSheet.loadFromFile(textureFiles))
        {
            std::cout << "ERROR::TILEMAP::COULDN'T LOAD TEXTURE SHEET, " << textureFiles << "\n";
        }

        while(in_file >> x >> y >> z >> type)
        {
            if (type == TileTypes::ENEMYSPAWNER)
            {
                //  Enemy Type,  Amount, TimeToSpawn, MaxDistance
                int enemy_type, enemy_am, enemy_tts, enemy_mD;

                in_file >> trX >> trY >>
                enemy_type >> enemy_am >> enemy_tts >> enemy_mD;

                this->maps[x][y][z].push_back(new EnemySpawner(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
                                 enemy_type, enemy_am, enemy_tts, enemy_mD));
            }
            else
            {
                in_file >> trX >> trY >> collision;

                this->maps[x][y][z].push_back(new Tile(type, x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collision));
            }
        }
     }
     else
     {
         std::cout << "ERROR::TileMap::LoadFromFile:: COULDN'T LOAD THE FILE NAME : " << file_name << "\n";
     }

     in_file.close();
}

void TileMap::update(Entity* entity, const float& dt)
{
    //WORLD BOUNDS
    if(entity->getPosition().x < 0.f)
    {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
    }
    else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
    {
        entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }
    if(entity->getPosition().y < 0.f)
    {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    }
    else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
    {
        entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }

    //TILES
    this->layer = 0;

    this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
    if(this->fromX < 0)
    {
        this->fromX = 0;
    }
    else if (this->fromX > this->maxSizeWorldGrid.x)
    {
        this->fromX = this->maxSizeWorldGrid.x;
    }

    this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
    if(this->toX < 0)
    {
        this->toX = 0;
    }
    else if (this->toX > this->maxSizeWorldGrid.x)
    {
        this->toX = this->maxSizeWorldGrid.x;
    }

    this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
    if(this->fromY < 0)
    {
        this->fromY = 0;
    }
    else if (this->fromY > this->maxSizeWorldGrid.y)
    {
        this->fromY = this->maxSizeWorldGrid.y;
    }

    this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
    if(this->toY < 0)
    {
        this->toY = 0;
    }
    else if (this->toY > this->maxSizeWorldGrid.y)
    {
        this->toY = this->maxSizeWorldGrid.y;
    }

    //COLLISION
    for (int x = this->fromX; x < this->toX; x++)
    {
        for (int y = this->fromY; y < this->toY; y++)
        {
            for(size_t k = 0; k < this->maps[x][y][this->layer].size(); k++)
            {
                this->maps[x][y][this->layer][k]->update();

                sf::FloatRect playerBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = this->maps[x][y][this->layer][k]->getGlobalBounds();
                sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

                if (this->maps[x][y][this->layer][k]->intersects(nextPositionBounds)
                    && this->maps[x][y][this->layer][k]->getCollision())
                {
                    //Bottom Collision
                    if (playerBounds.top < wallBounds.top
                        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                        && playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                    {
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                    }
                    //Top Collision
                    else if (playerBounds.top > wallBounds.top
                        && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                        && playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                    {
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                    }
                    //Right Collision
                    if (playerBounds.left < wallBounds.left
                        && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                        && playerBounds.top < wallBounds.top + wallBounds.height
                        && playerBounds.top + playerBounds.height > wallBounds.top
                             )
                    {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                    }
                    //Left Collision
                    else if (playerBounds.left > wallBounds.left
                             && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                             && playerBounds.top < wallBounds.top + wallBounds.height
                             && playerBounds.top + playerBounds.height > wallBounds.top
                             )
                    {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                    }
                }
            }
        }
    }
}

void TileMap::addTile(const int x, const int y, const int z, sf::IntRect& texture_rect, const bool collision, const short type)
{
    /* Take three parameters and add a tile to the position if available */
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
        y < this->maxSizeWorldGrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        /* OK TO ADD TILE */
        this->maps[x][y][z].push_back(new Tile(type, x, y, this->gridSizeF, this->tileSheet, texture_rect, collision));
    }
}

void TileMap::removeTile(const int x, const int y, const int z, const int type)
{
    /* Take three parameters and remove a tile from the position if available */
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
        y < this->maxSizeWorldGrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        /* Check if the maps in that position is not null */
        if (!this->maps[x][y][z].empty())
        {
            if (type >= 0)
            {
                if (this->maps[x][y][z].back()->getType() == type)
                {
                    delete this->maps[x][y][z][this->maps[x][y][z].size()-1];
                    this->maps[x][y][z].pop_back();
                }
            }
            else
            {
                // Ok to remove
                delete this->maps[x][y][z][this->maps[x][y][z].size()-1];
                this->maps[x][y][z].pop_back();
            }
        }
    }
}

void TileMap::render(sf::RenderTarget& target, sf::Vector2i gridPosition, sf::Shader* shader, const sf::Vector2f playerPosition, const bool show_collision)
{
    this->layer = 0;

    this->fromX = gridPosition.x - 12;
    if(this->fromX < 0)
    {
        this->fromX = 0;
    }
    else if (this->fromX > this->maxSizeWorldGrid.x)
    {
        this->fromX = this->maxSizeWorldGrid.x;
    }

    this->toX = gridPosition.x + 13;
    if(this->toX < 0)
    {
        this->toX = 0;
    }
    else if (this->toX > this->maxSizeWorldGrid.x)
    {
        this->toX = this->maxSizeWorldGrid.x;
    }

    this->fromY = gridPosition.y - 8;
    if(this->fromY < 0)
    {
        this->fromY = 0;
    }
    else if (this->fromY > this->maxSizeWorldGrid.y)
    {
        this->fromY = this->maxSizeWorldGrid.y;
    }

    this->toY = gridPosition.y + 10;
    if(this->toY < 0)
    {
        this->toY = 0;
    }
    else if (this->toY > this->maxSizeWorldGrid.y)
    {
        this->toY = this->maxSizeWorldGrid.y;
    }

    for(int x = this->fromX; x < this->toX; x++)
    {
        for(int y = this->fromY; y < this->toY; y++)
        {
            for (size_t k = 0; k < this->maps[x][y][this->layer].size(); k++)
            {
                if (this->maps[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
                {
                    this->deferredRenderStack.push(this->maps[x][y][this->layer][k]);
                }
                else
                {
                    if (shader)
                        this->maps[x][y][this->layer][k]->render(target,shader, playerPosition);
                    else
                        this->maps[x][y][this->layer][k]->render(target);
                }
                if (show_collision)
                {
                    if (this->maps[x][y][this->layer][k]->getCollision())
                    {
                        this->collisionBox.setPosition(this->maps[x][y][this->layer][k]->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
                if (this->maps[x][y][this->layer][k]->getCollision() == TileTypes::ENEMYSPAWNER)
                {
                    this->collisionBox.setPosition(this->maps[x][y][this->layer][k]->getPosition());
                    target.draw(this->collisionBox);
                }
            }
        }
    }
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
    while(!this->deferredRenderStack.empty())
    {
        if (shader)
            this->deferredRenderStack.top()->render(target,shader, playerPosition);
        else
            this->deferredRenderStack.top()->render(target);
        this->deferredRenderStack.pop();
    }
}
