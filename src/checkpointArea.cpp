#include "checkpointArea.h"
#include "waveball.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void CheckpointArea::_bind_methods() {
    ClassDB::bind_method(D_METHOD("getCheckpoint"), &CheckpointArea::getCheckpoint);
	ClassDB::bind_method(D_METHOD("setCheckpoint", "checkpoint"), &CheckpointArea::setCheckpoint);
    ClassDB::bind_method(D_METHOD("bodyEntered", "body"), &CheckpointArea::bodyEntered);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "checkpointPosition"), "setCheckpoint", "getCheckpoint");
}

CheckpointArea::CheckpointArea() {
	// Constructor
	checkpoint = Vector2(0.0f, 0.0f);
    connect("body_entered", godot::Callable(this, "bodyEntered"));
}

CheckpointArea::~CheckpointArea() {
	// Destructor
    disconnect("body_entered", godot::Callable(this, "bodyEntered"));
}

void CheckpointArea::bodyEntered(Node2D* body) {
    if (body->is_class("WaveBall"))
    {
        WaveBall* waveBall = dynamic_cast<WaveBall*>(body);
        waveBall->setCheckpointPosition(checkpoint);
        queue_free();
    }
}

void CheckpointArea::setCheckpoint(const Vector2 newCheckpoint) { 
	checkpoint = newCheckpoint;
}

Vector2 CheckpointArea::getCheckpoint() const {
    return checkpoint;
}