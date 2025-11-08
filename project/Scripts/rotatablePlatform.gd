extends StaticBody2D

var isBeingClicked := false;

func _physics_process(_delta: float) -> void:
	if (isBeingClicked):
		var mousePosition := get_global_mouse_position();
		look_at(mousePosition);

func onInputEvent(_viewport: Node, event: InputEvent, _shape_idx: int) -> void:
	var mouseEvent := event as InputEventMouseButton;
	if (mouseEvent != null):
		if (mouseEvent.is_pressed()):
			isBeingClicked = true;
		else:
			isBeingClicked = false;

func onMouseExited() -> void:
	isBeingClicked = false;
