#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

namespace godot {

class Labyrinth : public Area2D {
	GDCLASS(Labyrinth, Area2D)

private:
	bool isBeingClicked;

protected:
	static void _bind_methods();

public:
	Labyrinth();
	~Labyrinth();

	//void _ready() override;
	void _physics_process(double delta) override;
	void _input(InputEvent *event) override;

    void setClickedState(bool isClicked);
    void inputEvent(Node *viewport, InputEvent *event, int shapeIdx);
    void mouseExited();
};

}

#endif