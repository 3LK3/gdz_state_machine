#include "helpers.h"
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

bool EngineHelper::runs_in_editor()
{
    return Engine::get_singleton()->is_editor_hint();
}

bool EngineHelper::runs_in_game()
{
    return !Engine::get_singleton()->is_editor_hint();
}