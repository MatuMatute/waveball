#include "labyrinth.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Labyrinth::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setClickedState", "isClicked"), &Labyrinth::setClickedState);
    ClassDB::bind_method(D_METHOD("inputEvent", "viewport", "event", "shapeIdx"), &Labyrinth::inputEvent);
    ClassDB::bind_method(D_METHOD("mouseExited"), &Labyrinth::mouseExited);
}

Labyrinth::Labyrinth() {
	// Constructor
	isBeingClicked = false;
    connect("mouse_exited", godot::Callable(this, "mouseExited"));
    connect("input_event", godot::Callable(this, "inputEvent"));
}

Labyrinth::~Labyrinth() {
	// Destructor
    disconnect("mouse_exited", godot::Callable(this, "mouseExited"));
    disconnect("input_event", godot::Callable(this, "inputEvent"));
}

void Labyrinth::_physics_process(double delta) {
	if (isBeingClicked) {
        Vector2 mousePosition = get_global_mouse_position();
        look_at(mousePosition);
    }
}

void Labyrinth::setClickedState(bool isClicked) {
    isBeingClicked = isClicked;
}

void Labyrinth::inputEvent(Node* viewport, InputEvent* event, int shapeIdx) {
    if (event->is_class("InputEventMouseButton") || event->is_class("InputEventScreenTouch")) {
        if (event->is_pressed()) {
            isBeingClicked = true;
        }
        else {
            isBeingClicked = false;
        }
    }
}

void Labyrinth::mouseExited() {
    isBeingClicked = false;
}