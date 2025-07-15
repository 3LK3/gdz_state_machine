extends Node

@export var state_machine: StateMachine


func _ready():
	state_machine.run()
