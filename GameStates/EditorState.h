#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Buttons.h"

class EditorState : public State
{
private:
    void initVariables();
    void initBackgrounds();
    void initKeyBinds();
    void initFonts();
    void initButtons();

    sf::Font font;

    std::map<std::string, Buttons*> buttons;

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);

    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // EDITORSTATE_H
