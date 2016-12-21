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
	p2DynArray<PhysBody3D*> death_blocks;

	p2DynArray<Cube> road_cubes;

	p2DynArray<vec3> cp_coords;
	p2DynArray<Cube> cp_cubes;
	p2DynArray<PhysBody3D*> checkpoints;

	Cube sens;
	PhysBody3D* ramp_sensor;
	//special cubes
	Cube platform;
	Sphere motor;

	Cube sensor;
	Cube s;
	PhysBody3D* body_sensor;

	Timer race_time;
	uint laps = 0;
};
