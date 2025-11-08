#ifndef WAVEBALL_H
#define WAVEBALL_H

#include <godot_cpp/classes/rigid_body2d.hpp>

namespace godot {

class WaveBall : public RigidBody2D {
	GDCLASS(WaveBall, RigidBody2D)

private:
	Vector2 checkpointPosition;

protected:
	static void _bind_methods();

public:
	WaveBall();
	~WaveBall();

	void _ready() override;
	//void _process(double delta) override;
	void returnToCheckpoint();
};

}

#endif