extends Area2D

func onBodyEntered(body: Node2D) -> void:
	if (body is WaveBall):
		body.returnToCheckpoint();
		get_tree().call_group("RotatablePlatforms", "set_rotation", 0.0);
		get_tree().call_group("PhysicNodes", "returnToCheckpoint");
