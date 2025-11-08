extends WaveBall;

var isBeingClicked := false;

func _physics_process(_delta: float) -> void:
	if (isBeingClicked):
		global_transform.origin = get_global_mouse_position();

func onInputEvent(_viewport: Node, event: InputEvent, _shape_idx: int) -> void:
	var mouseEvent := event as InputEventMouseButton;
	if (mouseEvent != null):
		if (mouseEvent.is_pressed()):
			isBeingClicked = true;
			freeze = true;
		else:
			isBeingClicked = false;
			freeze = false;
			apply_central_impulse(Vector2.ZERO);

func mouseExited() -> void:
	isBeingClicked = false;
	freeze = false;
	apply_central_impulse(Vector2.ZERO);
