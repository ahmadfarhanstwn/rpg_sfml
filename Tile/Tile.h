#ifndef TILE_H
#define TILE_H

enum TileTypes
{
    DEFAULT,
    DAMAGING
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
    Tile(float x, float y, float gridSizeF, const sf::Texture& texture_sheet,
         const sf::IntRect& texture_rect, bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //Accessors
    const std::string getAsString() const;

    //Functions
    void update();
    void render(sf::RenderTarget& target);
};

#endif // TILE_H
