class_name SettingsMenuState
extends State

@export var root_node: Node
@export var canvas_scene: PackedScene

var _canvas_instance: SettingsMenuCanvas


func _enter_state(_previous_state_name: StringName, _data: Dictionary) -> void:
	print("SettingsMenuState :: enter")

	_canvas_instance = canvas_scene.instantiate()
	_canvas_instance.transitioned.connect(finish)
	root_node.add_child(_canvas_instance)


func _exit_state() -> void:
	print("SettingsMenuState :: exit")

	root_node.remove_child(_canvas_instance)
	_canvas_instance.queue_free()
