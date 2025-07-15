#pragma once

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

namespace godot {
/*
 * State is a base class for all states in the state machine.
 * It provides virtual methods for handling updates, entering, exiting,
 * and handling input events.
 *
 * The state machine will call these methods at appropriate times.
 */
class State : public Node {
  GDCLASS(State, Node)

 protected:
  static void _bind_methods();

  GDVIRTUAL2(_enter_state, StringName, Dictionary);
  GDVIRTUAL0(_exit_state);
  GDVIRTUAL1(_handle_input, Ref<InputEvent>);
  GDVIRTUAL1(_physics_update, float);
  GDVIRTUAL1(_update, float);

 public:
  State();
  ~State();

  /*
   * Finishes the current state by emitting finished signal.
   */
  void finish(StringName next_state_name, Dictionary data);
};
}  // namespace godot
