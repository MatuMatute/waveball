#include "waveball.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void WaveBall::_bind_methods() {
	ClassDB::bind_method(D_METHOD("returnToCheckpoint"), &WaveBall::returnToCheckpoint);
	ClassDB::bind_method(D_METHOD("setCheckpointPosition", "checkpoint"), &WaveBall::setCheckpointPosition);
}

WaveBall::WaveBall() {
	// Constructor
	checkpointPosition = Vector2(0.0f, 0.0f);
}

WaveBall::~WaveBall() {
	// Destructor
}

void WaveBall::_ready() {
	checkpointPosition = get_position();
}

void WaveBall::returnToCheckpoint() {
	Transform2D globalTransform = get_global_transform();
	transform.set_origin(checkpointPosition);
	rotate(0.0f);
	set_linear_velocity(Vector2(0.0f, 0.0f));
	set_global_transform(transform);
}

void WaveBall::setCheckpointPosition(Vector2 checkpoint) { 
	checkpointPosition = checkpoint;
}