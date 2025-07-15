#pragma once

#include <godot_cpp/classes/node.hpp>

#include "state.h"

namespace godot {

class StateMachine : public Node {
  GDCLASS(StateMachine, Node)

 public:
  StateMachine();
  ~StateMachine();

  void _process(double delta) override;
  void _physics_process(double delta) override;
  //void _ready() override;
  void _unhandled_input(const Ref<InputEvent> &input_event) override;

  void run();

  State *get_initial_state() const;
  void set_initial_state(State *state);

  /*bool should_auto_run() const;
  void set_auto_run(bool auto_run = false);*/

  State *get_current_state() const;
  void set_current_state(State *state);

 protected:
  static void _bind_methods();

 private:
  State *_current_state = NULL;
  State *_initial_state = NULL;
  Dictionary _states;

  bool _auto_run = false;

  void transition_to_next_state(StringName next_state_name, Dictionary data);
};

}  // namespace godot
