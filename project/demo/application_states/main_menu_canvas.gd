class_name MainMenuCanvas
extends CanvasLayer

signal transitioned(next_state_name: StringName, data: Dictionary)


func on_start_pressed() -> void:
	transitioned.emit("InGameState", {})


func on_settings_pressed() -> void:
	transitioned.emit("SettingsMenuState", {})


func on_quit_pressed() -> void:
	get_tree().quit()
