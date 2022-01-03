#include "EditorMode.h"
#include "stdafx.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data) :
    stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data)
{
    //ctor
}

EditorMode::~EditorMode()
{
    //dtor
}

const bool EditorMode::getKeytime()
{
    if (*this->editorStateData->keytime >= *this->editorStateData->keytimeMax)
    {
        *this->editorStateData->keytime = 0.f;
        return true;
    }
    return false;
}
