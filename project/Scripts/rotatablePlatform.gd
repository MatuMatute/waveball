extends RotatablePlatform;

func onInputEvent(_viewport: Node, event: InputEvent, _shape_idx: int) -> void:
	var mouseEvent := event as InputEventMouseButton;
	if (mouseEvent != null):
		if (event.button_index == 1 and mouseEvent.is_pressed()):
			setClickedState(true);
		else:
			setClickedState(false);
