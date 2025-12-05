extends Node

@onready var waveball : WaveBall = $WaveBall;
@onready var camera : Camera2D = $WaveBall/Camera;
@onready var labyrinth : Labyrinth = $Labyrinth;

func _on_labyrinth_body_entered(body: Node2D) -> void:
	if (body is WaveBall):
		camera.reparent(labyrinth);

func _on_labyrinth_body_exited(body: Node2D) -> void:
	if (body is WaveBall):
		camera.reparent(waveball);
