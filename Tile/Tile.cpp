#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
    this->collision = false;
    this->type = 0;
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture_sheet,
           const sf::IntRect& texture_rect, bool collision, short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::White);
//    this->shape.setOutlineThickness(1.f);
//    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(x,y);
    this->shape.setTexture(&texture_sheet);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{
    //dtor
}

//Accessors
const std::string Tile::getAsString() const
{
    std::stringstream ss;

    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

    return ss.str();
}

//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
