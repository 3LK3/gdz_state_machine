class_name InGameState
extends State

@export var root_node: Node
@export var in_game_scene: PackedScene

var _in_game_instance: InGameScene


func _enter_state(_previous_state_name: StringName, _data: Dictionary) -> void:
	print("InGameState :: enter")

	_in_game_instance = in_game_scene.instantiate()
	_in_game_instance.transitioned.connect(finish)
	root_node.add_child(_in_game_instance)


func _exit_state() -> void:
	print("InGameState :: exit")

	root_node.remove_child(_in_game_instance)
	_in_game_instance.queue_free()

# func _handle_input(event: InputEvent) -> void:
# 	print("Handle Input %s" % event)
