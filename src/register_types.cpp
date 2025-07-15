#include "register_types.h"

#include "state.h"
#include "state_machine.h"

void initialize_state_machine_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  GDREGISTER_VIRTUAL_CLASS(State);
  GDREGISTER_CLASS(StateMachine);
}

void uninitialize_state_machine_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
gdz_state_machine_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                       const GDExtensionClassLibraryPtr p_library,
                       GDExtensionInitialization *r_initialization) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initialization);

  init_obj.register_initializer(initialize_state_machine_module);
  init_obj.register_terminator(uninitialize_state_machine_module);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}