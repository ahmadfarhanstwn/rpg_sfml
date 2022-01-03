#ifndef TILE_H
#define TILE_H

enum TileTypes
{
    DEFAULT,
    DAMAGING,
    DOODAD,
    ENEMYSPAWNER
};

class Tile
{
private:

protected:
    sf::Sprite shape;
    bool collision;
    short type;

public:
    Tile();
    Tile(short type, int x, int y, float gridSizeF, const sf::Texture& texture_sheet,
         const sf::IntRect& texture_rect, bool collision = false);
    virtual ~Tile();

    //Accessors
    virtual const std::string getAsString() const;
    virtual const sf::Vector2f& getPosition() const;
    virtual const bool& getCollision() const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const short& getType() const;

    //Functions
    const bool intersects(const sf::FloatRect bounds) const;
    virtual void update();
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif // TILE_H
