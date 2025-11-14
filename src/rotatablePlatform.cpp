#include "rotatablePlatform.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void RotatablePlatform::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setClickedState", "isClicked"), &RotatablePlatform::setClickedState);
    ClassDB::bind_method(D_METHOD("inputEvent", "viewport", "event", "shapeIdx"), &RotatablePlatform::inputEvent);
    ClassDB::bind_method(D_METHOD("mouseExited"), &RotatablePlatform::mouseExited);
}

RotatablePlatform::RotatablePlatform() {
	// Constructor
    set_pickable(true);
	isBeingClicked = false;
    connect("mouse_exited", godot::Callable(this, "mouseExited"));
    connect("input_event", godot::Callable(this, "inputEvent"));
}

RotatablePlatform::~RotatablePlatform() {
	// Destructor
    disconnect("mouse_exited", godot::Callable(this, "mouseExited"));
    disconnect("input_event", godot::Callable(this, "inputEvent"));
}

void RotatablePlatform::_physics_process(double delta) {
	if (isBeingClicked) {
        Vector2 mousePosition = get_global_mouse_position();
        look_at(mousePosition);
    }
}

void RotatablePlatform::setClickedState(bool isClicked) {
    isBeingClicked = isClicked;
}

void RotatablePlatform::inputEvent(Node* viewport, InputEvent* event, int shapeIdx) {
    if (event->is_class("InputEventMouseButton") || event->is_class("InputEventScreenTouch")) {
        if (event->is_pressed()) {
            isBeingClicked = true;
        }
        else {
            isBeingClicked = false;
        }
    }
}

void RotatablePlatform::mouseExited() {
    isBeingClicked = false;
}