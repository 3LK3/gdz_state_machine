#include "state_machine.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "helpers.h"

using namespace godot;

StateMachine::StateMachine() { _states = Dictionary(); }

StateMachine::~StateMachine() {}

void StateMachine::_bind_methods() {
  ClassDB::bind_method(D_METHOD("run"), &StateMachine::run);

  ClassDB::bind_method(D_METHOD("transition_to_next_state"),
                       &StateMachine::transition_to_next_state);

  ClassDB::bind_method(D_METHOD("get_current_state"),
                       &StateMachine::get_current_state);
  ClassDB::bind_method(D_METHOD("set_current_state", "state"),
                       &StateMachine::set_current_state);

  ClassDB::bind_method(D_METHOD("get_initial_state"),
                       &StateMachine::get_initial_state);
  ClassDB::bind_method(D_METHOD("set_initial_state", "state"),
                       &StateMachine::set_initial_state);

  // ClassDB::bind_method(D_METHOD("should_auto_run"),
  //                      &StateMachine::should_auto_run);
  // ClassDB::bind_method(D_METHOD("set_auto_run", "auto_run"),
  //                      &StateMachine::set_auto_run);

  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "initial_state",
                            PROPERTY_HINT_NODE_TYPE, "State"),
               "set_initial_state", "get_initial_state");

  /*ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_run"), "set_auto_run",
               "should_auto_run");*/
}

void godot::StateMachine::transition_to_next_state(StringName next_state_name,
                                                   Dictionary data) {
  // UtilityFunctions::print("transition_to_next_state ", next_state_name);

  if (!_states.has(next_state_name)) {
    godot::UtilityFunctions::push_error("Next state not found: '{}'",
                                        next_state_name);
  } else {
    _current_state->call("_exit_state");
    StringName current_state_name = _current_state->get_name();

    State *next_state = Object::cast_to<State>(_states[next_state_name]);
    set_current_state(next_state);

    _current_state->call("_enter_state", current_state_name, data);
  }
}

void StateMachine::_process(double delta) {
  if (_current_state != nullptr) {
    _current_state->call("_update", delta);
  }
}

void StateMachine::_physics_process(double delta) {
  if (_current_state != nullptr) {
    _current_state->call("_physics_update", delta);
  }
}

// void StateMachine::_ready() {
//   if (_auto_run) {
//     run();
//   }
// }

void StateMachine::_unhandled_input(const Ref<InputEvent> &input_event) {
  if (_current_state != nullptr) {
    _current_state->call("_handle_input", input_event);
  }
}

void StateMachine::run() {
  // godot::UtilityFunctions::print("StateMachine :: run");

  _states.clear();

  int32_t child_count = get_child_count();
  if (child_count < 1) {
    UtilityFunctions::push_error("StateMachine has no child states.");
    return;
  }

  for (size_t i = 0; i < child_count; i++) {
    State *state = Object::cast_to<State>(get_child(i));
    // state->connect("finished", Callable(this, "transition_to_next_state"));
    _states[state->get_name()] = state;
  }

  if (_initial_state == nullptr) {
    _initial_state = Object::cast_to<State>(get_child(0));
  }
  set_current_state(_initial_state);
  _initial_state->call("_enter_state", "", Dictionary());
}

State *StateMachine::get_initial_state() const { return _initial_state; }

void StateMachine::set_initial_state(State *state) { _initial_state = state; }

// bool StateMachine::should_auto_run() const { return _auto_run; }

// void StateMachine::set_auto_run(bool auto_run) { _auto_run = auto_run; }

State *StateMachine::get_current_state() const { return _current_state; }

void StateMachine::set_current_state(State *state) {
  /*godot::UtilityFunctions::print("StateMachine::set_active_state ",
                                 state->get_name());*/
  if (_current_state != NULL) {
    _current_state->disconnect("finished",
                               Callable(this, "transition_to_next_state"));
  }

  _current_state = state;
  _current_state->connect("finished",
                          Callable(this, "transition_to_next_state"));
}