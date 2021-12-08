#ifndef GUI_H
#define GUI_H

enum button_states
{
    BTN_IDLE,
    BTN_HOVERED,
    BTN_ACTIVE
};

namespace gui
{
    class Buttons
    {
    private:
        short unsigned btnState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

    public:
        Buttons(float x, float y, float width, float height, sf::Font* font, std::string text,
                unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
                sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
                short unsigned id = 0);
        virtual ~Buttons();

        //Accessors
        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        //Modifier
        void setText(const std::string text);
        void setId(const short unsigned id);

        //Function
        void update(const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);
    };

    class DropDownList
    {
    private:
        sf::Font& font;
        gui::Buttons* activeElement;
        std::vector<gui::Buttons*> list;
        bool showList;
        float keytime;
        float keytimeMax;

    public:
        DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index);
        ~DropDownList();

        //Accessors
        const bool getKeytime();
        const unsigned short& getActiveElementId() const;

        //Function
        void updateKeytime(const float& dt);
        void update(const sf::Vector2f& mousePos, const float& dt);
        void render(sf::RenderTarget& target);
    };
}

#endif // BUTTONS_H
