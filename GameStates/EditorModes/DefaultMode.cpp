#include "DefaultMode.h"
#include "stdafx.h"

void DefaultEditorMode::initVariables()
{
    this->textureRect = sf::IntRect(0,0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));

    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->layer = 0;
    this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
{
    this->cursorText.setFont(*this->editorStateData->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y - 50.f);

    //Sidebar
    this->sidebar.setSize(sf::Vector2f(60.f, static_cast<float>(this->stateData->graphicsSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50,50,50,100));
    this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255,255,255,150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    //Init Texture Selector
    this->textureSelector = new gui::TextureSelector(20.f, 20.f, 640.f, 576.f,
                                                     this->stateData->gridSize ,this->tileMap->getTileSheet(),
                                                     *this->editorStateData->font, "X");
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data) :
    EditorMode(state_data, tile_map, editor_state_data)
{
    this->initVariables();
    this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
    delete this->textureSelector;
}

//Functions
void DefaultEditorMode::updateInput(const float& dt)
{
    // Add a tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
        {
            if (!this->textureSelector->getActive())
            {
                if (this->tileAddLock)
                {
                    if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
                    {
                        this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0,
                                               this->textureRect, this->collision, this->type);
                    }
                }
                else
                {
                    this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y,
                                           0, this->textureRect, this->collision, this->type);
                }
            }
            else
            {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    // Remove a tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
    {
        if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
            this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
    }
    //Collison
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("Toggle_Collision"))) && this->getKeytime())
    {
        this->collision = this->collision ? false : true;
    }
    //Decrease Type
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("Decrease_Type"))) && this->getKeytime())
    {
        if (this->type > 0)
            --this->type;
    }
    //Increase Type
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("Increase_Type"))) && this->getKeytime())
    {
        ++this->type;
    }
    //Tile Add Lock
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("Toggle_Lock_Add"))) && this->getKeytime())
    {
        this->tileAddLock = this->tileAddLock ? false : true;
    }
}

void DefaultEditorMode::updateGui(const float& dt)
{
    this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);

    if (!this->textureSelector->getActive())
    {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
                                       this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
    }
    this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y - 100.f);
    std::stringstream ss;
    ss << this->editorStateData->mousePosView->x << "  " << this->editorStateData->mousePosView->y <<
    "\n" << this->editorStateData->mousePosGrid->x << "  " << this->editorStateData->mousePosGrid->y <<
    "\n" << this->textureRect.left << "  " << this->textureRect.top <<
    "\nCollision : " << this->collision <<
    "\nType : " << this->type <<
    "\nTiles : " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) <<
    "\nLock Tiles : " << this->tileAddLock;

    this->cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{
    this->updateInput(dt);
    this->updateGui(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
    if (!this->textureSelector->getActive())
    {
        target.setView(*this->editorStateData->view);
        target.draw(this->selectorRect);
    }

    target.setView(this->stateData->window->getDefaultView());
    this->textureSelector->render(target);

    target.draw(this->sidebar);

    target.setView(*this->editorStateData->view);
    target.draw(this->cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
    this->renderGui(target);
}
