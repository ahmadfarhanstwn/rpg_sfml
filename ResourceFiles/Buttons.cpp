#include "Buttons.h"

Buttons::Buttons(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
                 sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                 sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
                           this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
                           this->shape.getPosition().y + (this->shape.getGlobalBounds().height/2.f) - this->text.getGlobalBounds().height/2.f
                           );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->btnState = BTN_IDLE;
}

Buttons::~Buttons()
{
    //dtor
}

//Accessors
const bool Buttons::isPressed() const
{
    if(this->btnState == BTN_ACTIVE)
        return true;

    return false;
}

//Functions
void Buttons::update(const sf::Vector2f mousePos)
{
    //update the booleans for hover and pressed
    this->btnState = BTN_IDLE;
    //button hovered
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->btnState = BTN_HOVERED;
        //button pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->btnState = BTN_ACTIVE;
        }
    }

    switch(this->btnState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVERED:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }
}

void Buttons::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->text);
}
