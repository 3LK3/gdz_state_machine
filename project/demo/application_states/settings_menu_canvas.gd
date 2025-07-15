class_name SettingsMenuCanvas
extends CanvasLayer

signal transitioned(next_state_name: StringName, data: Dictionary)


func on_back_to_menu_pressed() -> void:
	transitioned.emit("MainMenuState", {})
