#ifndef CHECKPOINTAREA_H
#define CHECKPOINTAREA_H

#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class CheckpointArea : public Area2D {
	GDCLASS(CheckpointArea, Area2D)

private:
	Vector2 checkpoint;

protected:
	static void _bind_methods();

public:
	CheckpointArea();
	~CheckpointArea();

    void bodyEntered(Node2D* body);

	void setCheckpoint(const Vector2 newCheckpoint);
    Vector2 getCheckpoint() const;
};

}

#endif