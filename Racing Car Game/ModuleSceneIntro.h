#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	
	p2DynArray<PhysBody3D*> road;
	p2DynArray<PhysBody3D*> turbo_road;
	p2DynArray<PhysBody3D*> slow_road;
	p2DynArray<Cube*>circuit;
	p2DynArray<Cube> road_cubes;
	// Normal cubes

	Cube block1;
	Cube block2;
	Cube block3;
	Cube ramp;
	Cube ramp2;
	Cube block4;
	Cube block5;
	Cube block6;
	Cube block7;
	Cube block8;
	Cube block9;
	Cube block10;
	Cube block11;
	Cube block12;
	Cube block13;
	Cube sens;
	PhysBody3D* ramp_sensor;

	//special cubes
	Cube platform;
	Sphere motor;

	Cube floor;

	Cube turbo;
	
	Cube falling;
	
	Cube slow;

	Cube s;
	PhysBody3D* sensor;
};
