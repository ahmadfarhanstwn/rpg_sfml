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
    const float p2pX(const float perc, sf::VideoMode& vm);
    const float p2pY(const float perc, sf::VideoMode& vm);
    const unsigned calcCharSize(sf::VideoMode& vm, const unsigned modifier = 43);
    /** ======================= Buttons ======================= **/
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
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderTarget& target);
    };

    /** ======================= DropDownList ======================= **/
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
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);
    };

    /** ======================= TextureSelector ======================= **/
    class TextureSelector
    {
    private:
        bool active;

        bool hidden;
        gui::Buttons* hideButton;

        //Keytime
        float keytime;
        const float keytimeMax;

        float gridSize;
        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;

    public:
        TextureSelector(float x, float y, float width, float height, float grid_size,
                        const sf::Texture* texture_sheet, sf::Font& font, std::string text);
        ~TextureSelector();

        //Accessors
        const bool& getActive() const;
        const sf::IntRect& getTextureRect() const;
        const bool getKeytime();

        //Functions
        void updateKeytime(const float& dt);
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);
    };

    /** ======================= Progress Bar ======================= **/
    class ProgressBar
    {
    private:
        std::string barString;
        sf::Text text;
        float maxWidth;
        int maxValue;
        sf::RectangleShape back;
        sf::RectangleShape inner;

    protected:

    public:
        ProgressBar(float x, float y, float width, float height, int max_value,
                    sf::Color inner_color, unsigned character_size,
                    sf::VideoMode& vm, sf::Font* font = nullptr);
        ~ProgressBar();

        //Accessors

        //Modifiers

        //Functions
        void update(const int current_value);
        void render(sf::RenderTarget& target);
    };
}

#endif // BUTTONS_H
