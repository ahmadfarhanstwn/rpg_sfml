#ifndef TILE_H
#define TILE_H

enum TileTypes
{
    DEFAULT,
    DAMAGING,
    DOODAD
};

class Tile
{
private:

protected:
    sf::RectangleShape shape;
    bool collision;
    short type;

public:
    Tile();
    Tile(int x, int y, float gridSizeF, const sf::Texture& texture_sheet,
         const sf::IntRect& texture_rect, bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //Accessors
    const std::string getAsString() const;
    const sf::Vector2f& getPosition() const;
    const bool& getCollision() const;
    const sf::FloatRect getGlobalBounds() const;
    const short& getType() const;

    //Functions
    const bool intersects(const sf::FloatRect bounds) const;
    void update();
    void render(sf::RenderTarget& target);
};

#endif // TILE_H
