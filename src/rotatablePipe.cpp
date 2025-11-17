#include "rotatablePipe.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/tweener.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

using namespace godot;

#define M_PI_2 1.57079632679489661923
#define Math_TAU 6.2831853071795864769252867666

void RotatablePipe::_bind_methods() {
    ClassDB::bind_method(D_METHOD("inputEvent", "viewport", "event", "shapeIdx"), &RotatablePipe::inputEvent);
    ClassDB::bind_method(D_METHOD("setLaunchSpeed", "newLaunchSpeed"), &RotatablePipe::setLaunchSpeed);
    ClassDB::bind_method(D_METHOD("getLaunchSpeed"), &RotatablePipe::getLaunchSpeed);
    ClassDB::bind_method(D_METHOD("bodyLeftEntrance", "body"), &RotatablePipe::bodyLeftEntrance);
    ClassDB::bind_method(D_METHOD("bodyRightEntrance", "body"), &RotatablePipe::bodyRightEntrance);
    ClassDB::bind_method(D_METHOD("rotationFinished"), &RotatablePipe::rotationFinished);
    ClassDB::bind_method(D_METHOD("leftWaveballLaunch"), &RotatablePipe::leftWaveballLaunch);
    ClassDB::bind_method(D_METHOD("rightWaveballLaunch"), &RotatablePipe::rightWaveballLaunch);
    ClassDB::bind_method(D_METHOD("restartRotation"), &RotatablePipe::restartRotation);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "launchSpeed"), "setLaunchSpeed", "getLaunchSpeed");
}

RotatablePipe::RotatablePipe() {
    // Constructor
    launchSpeed = 200;
    isBusy = false;
    currentWaveball = nullptr;
}

RotatablePipe::~RotatablePipe() {
    // Destructor
    delete currentWaveball;
}

void RotatablePipe::_ready() {
    initialRotation = get_rotation();
    get_node<Area2D>("Clickable")->connect("input_event", godot::Callable(this, "inputEvent"));
    get_node<Area2D>("LeftEntrance")->connect("body_entered", godot::Callable(this, "bodyLeftEntrance"));
    get_node<Area2D>("RightEntrance")->connect("body_entered", godot::Callable(this, "bodyRightEntrance"));
}

void RotatablePipe::setLaunchSpeed(int newLaunchSpeed) { launchSpeed = newLaunchSpeed; }
int RotatablePipe::getLaunchSpeed() { return launchSpeed; }

void RotatablePipe::inputEvent(Node* viewport, InputEvent* event, int shapeIdx) {
    if (isBusy) {
        return;
    }

    if (event->is_class("InputEventMouseButton") || event->is_class("InputEventScreenTouch")) {
        if (event->is_pressed()) {
            Ref<Tween> tween = create_tween();
            tween->connect("finished", godot::Callable(this, "rotationFinished"), 4);
            tween->tween_property(this, "rotation", get_rotation() + M_PI_2, 0.5f);
            tween->play();
            isBusy = true;
        }
    }
}

void RotatablePipe::bodyLeftEntrance(Node2D* body) {
    if (isBusy) {
        return;
    }

    if (body->is_class("WaveBall")) {
        currentWaveball = dynamic_cast<WaveBall*>(body);
        Ref<Tween> tween = create_tween();
        tween->tween_property(body, "position", get_position(), 0.5f);
        tween->connect("finished", godot::Callable(this, "leftWaveballLaunch"), 4);
        tween->play();
        isBusy = true;
    }
}

void RotatablePipe::bodyRightEntrance(Node2D* body) {
    if (isBusy) {
        return;
    }

    if (body->is_class("WaveBall")) {
        currentWaveball = dynamic_cast<WaveBall*>(body);
        Ref<Tween> tween = create_tween();
        tween->tween_property(body, "position", get_position(), 0.5f);
        tween->connect("finished", godot::Callable(this, "rightWaveballLaunch"), 4);
        tween->play();
        isBusy = true;
    }
}

void RotatablePipe::rotationFinished() {
    if (get_rotation() >= Math_TAU) {
        set_rotation(0.0f);
    }

    isBusy = false;
}

void RotatablePipe::leftWaveballLaunch() {
    currentWaveball->set_linear_velocity(Vector2(0.0f, 0.0f));
    Vector2 launchDirection = Vector2(0.0f, 0.0f);
    launchDirection = get_node<Node2D>("LeftLaunchPoint")->get_global_position() - currentWaveball->get_position();
    launchDirection.normalize();
    launchDirection *= launchSpeed;
    UtilityFunctions::print(launchDirection);

    currentWaveball->apply_impulse(launchDirection);
    isBusy = false;
}

void RotatablePipe::rightWaveballLaunch() {
    currentWaveball->set_linear_velocity(Vector2(0.0f, 0.0f));
    Vector2 launchDirection = Vector2(0.0f, 0.0f);
    launchDirection = get_node<Node2D>("RightLaunchPoint")->get_global_position() - currentWaveball->get_position();
    launchDirection.normalize();
    launchDirection *= launchSpeed;

    currentWaveball->apply_impulse(launchDirection);
    UtilityFunctions::print(currentWaveball->get_linear_velocity());
    isBusy = false;
}

void RotatablePipe::restartRotation() {
    set_rotation(initialRotation);
}