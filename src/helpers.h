#pragma once

namespace godot {

class EngineHelper {
 public:
  static bool runs_in_editor();
  static bool runs_in_game();
};

}  // namespace godot
