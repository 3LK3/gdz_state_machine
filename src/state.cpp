#include "state.h"

using namespace godot;

State::State() {}

State::~State() {}

void State::_bind_methods() {
  GDVIRTUAL_BIND(_update, "delta");
  GDVIRTUAL_BIND(_physics_update, "delta");

  GDVIRTUAL_BIND(_enter_state, "previous_state_name", "data");
  GDVIRTUAL_BIND(_exit_state);
  GDVIRTUAL_BIND(_handle_input, "event");

  ClassDB::bind_method(D_METHOD("finish", "next_state_name", "data"),
                       &State::finish);

  ADD_SIGNAL(MethodInfo("finished",
                        PropertyInfo(Variant::STRING_NAME, "next_state_name"),
                        PropertyInfo(Variant::DICTIONARY, "data")));
}

void State::finish(StringName next_state_name, Dictionary data) {
  emit_signal("finished", next_state_name, data);
}
