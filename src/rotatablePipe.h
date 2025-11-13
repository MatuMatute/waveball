#ifndef ROTATABLEPIPE_H
#define ROTATABLEPIPE_H

#include "waveball.h"
#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class RotatablePipe : public StaticBody2D {
	GDCLASS(RotatablePipe, StaticBody2D)

private:
    bool isBusy;
	float initialRotation;
	WaveBall* currentWaveball;

protected:
	static void _bind_methods();

public:
	RotatablePipe();
	~RotatablePipe();

	void _ready() override;

    void inputEvent(Node* viewport, InputEvent* event, int shapeIdx);
	void bodyLeftEntrance(Node2D* body);
	void bodyRightEntrance(Node2D* body);
	void rotationFinished();
	void leftWaveballLaunch();
	void rightWaveballLaunch();
	void restartRotation();
};

}

#endif