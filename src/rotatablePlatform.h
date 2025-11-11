#ifndef ROTATABLEPLATFORM_H
#define ROTATABLEPLATFORM_H

#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class RotatablePlatform : public StaticBody2D {
	GDCLASS(RotatablePlatform, StaticBody2D)

private:
	bool isBeingClicked;

protected:
	static void _bind_methods();

public:
	RotatablePlatform();
	~RotatablePlatform();

	//void _ready() override;
	void _physics_process(double delta) override;

    void setClickedState(bool isClicked);
    void inputEvent(Node *viewport, InputEvent *event, int shapeIdx);
    void mouseExited();
};

}

#endif