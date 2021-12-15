#include "stdafx.h"
#include "GUI.h"

/** ============================= BUTTONS =====================================**/
gui::Buttons::Buttons(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
                 sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                 sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
                 sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
                short unsigned id)
{
    this->id = id;

    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outline_idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
                           this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
                           this->shape.getPosition().y
                           );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;

    this->btnState = BTN_IDLE;
}

gui::Buttons::~Buttons()
{
    //dtor
}

//Accessors
const bool gui::Buttons::isPressed() const
{
    if(this->btnState == BTN_ACTIVE)
        return true;

    return false;
}

const std::string gui::Buttons::getText() const
{
    return this->text.getString();
}

const short unsigned& gui::Buttons::getId() const
{
    return this->id;
}

//Modifier
void gui::Buttons::setText(const std::string text)
{
    this->text.setString(text);
}

void gui::Buttons::setId(const short unsigned id)
{
    this->id = id;
}

//Functions
void gui::Buttons::update(const sf::Vector2i& mousePosWindow)
{
    //update the booleans for hover and pressed
    this->btnState = BTN_IDLE;
    //button hovered
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
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
        this->shape.setOutlineColor(this->outlineIdleColor);
        break;
    case BTN_HOVERED:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        this->shape.setOutlineColor(sf::Color::Black);
        break;
    }
}

void gui::Buttons::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

/** ===============================  DropDownList ==================================== **/
gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font,
                                std::string list[], unsigned nrOfElements, unsigned default_index) :
    font(font), showList(false), keytimeMax(2.f), keytime(keytimeMax)
{
    this->activeElement = new gui::Buttons(x,y,width,height,
                                          &this->font,list[default_index], 12,
                                          sf::Color(255,255,255,150),sf::Color(255,255,255,200),sf::Color(20,20,20,50),
                                          sf::Color(70,70,70,200),sf::Color(150,150,150,200),sf::Color(20,20,20,200),
                                           sf::Color(255,255,255,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50));

    for (unsigned i = 0; i < nrOfElements; i++)
    {
        this->list.push_back(new gui::Buttons(x,y + ((i+1) * height),width,height,
                                          &this->font,list[i], 12,
                                          sf::Color(255,255,255,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200),
                                          sf::Color(70,70,70,200),sf::Color(150,150,150,200),sf::Color(20,20,20,200),
                                              sf::Color(255,255,255,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50),
                                              i));
    }
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for (size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}

//Accessors
const bool gui::DropDownList::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
    return this->activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
    {
        this->keytime += 10.f * dt;
    }
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    this->updateKeytime(dt);

    this->activeElement->update(mousePosWindow);

    if(this->activeElement->isPressed() && this->getKeytime())
    {
        this->showList = this->showList ? false : true;
    }

    if (this->showList)
    {
        for(auto &i : this->list)
        {
            i->update(mousePosWindow);

            if(i->isPressed() && this->getKeytime())
            {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
    this->activeElement->render(target);

    if (this->showList)
    {
        for(auto &i : this->list)
        {
            i->render(target);
        }
    }
}

/** ============================= TEXTURE SELECTOR =====================================**/
gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float grid_size,
                                      const sf::Texture* texture_sheet, sf::Font& font, std::string text)
                                      : keytimeMax(2.f), keytime(keytimeMax)
{
    this->gridSize = grid_size;
    this->active = false;
    this->hidden = false;

    this->bounds.setSize(sf::Vector2f(width,height));
    this->bounds.setPosition(x + 60,y);
    this->bounds.setFillColor(sf::Color(50,50,50,100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x + 60,y);

    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
        this->sheet.setTextureRect(sf::IntRect(0,0,static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
    }
    else if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0,0,static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
    }

    this->selector.setPosition(x + 60,y);
    this->selector.setSize(sf::Vector2f(grid_size, grid_size));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->textureRect.width = static_cast<int>(grid_size);
    this->textureRect.height = static_cast<int>(grid_size);

    this->hideButton = new gui::Buttons(x,y,50.f,50.f,
                                        &font,text, 20,
                                        sf::Color(255,255,255,200),sf::Color(255,255,255,255),sf::Color(255,255,255,200),
                                        sf::Color(200,0,0,200),sf::Color(255,0,0,255),sf::Color(20,20,20,0));;
}

gui::TextureSelector::~TextureSelector()
{
    delete this->hideButton;
}

//Accessors
const bool& gui::TextureSelector::getActive() const
{
    return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
    return this->textureRect;
}

const bool gui::TextureSelector::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
    {
        this->keytime += 10.f * dt;
    }
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    //Update Keytime
    this->updateKeytime(dt);
    //Update Hidden Button
    this->hideButton->update(mousePosWindow);

    //If close button pressed
    if (this->hideButton->isPressed() && this->getKeytime())
    {
        this->hidden = this->hidden ? false : true;
    }

    //Update Texture Selector
    if (!this->hidden)
    {
        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
            this->active = true;
        else
            this->active = false;

        if (this->active)
        {
            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

            this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                                       this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

            //Update texture rectangle
            this->textureRect.left = static_cast<int>(this->selector.getPosition().x) - this->bounds.getPosition().x;
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y) - this->bounds.getPosition().y;
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{

    if (!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->sheet);
        target.draw(this->selector);
    }

    this->hideButton->render(target);
}
