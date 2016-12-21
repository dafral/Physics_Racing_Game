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

	//Music
	uint music;
	uint scream;
	uint check_point_fx;
	uint congratulations_fx;

	Cube platform;
	Sphere motor;

	Cube sensor;
	Cube s;
	PhysBody3D* body_sensor;

	Timer race_time;
	uint laps = 0;

	float cp_transforms[4][16];

	//these trasnforms make than whenever you respawn you respawn in the correct position and not looking to another direction or with the car upside down
	double trs_check_0[16] = { 1.00000000, 3.55736688e-06, 3.11943154e-07, 0.000000000, -3.55736825e-06, 1.00000000, 4.63879360e-06, 0.000000000, -3.11926669e-07, -4.63879451e-06, 1.00000000, 0.000000000, 2.05001743e-05, 0.942712605, -22.0000000, 1.00000000 };
	double trs_check_1[16] = { 0.0631858706, -0.000205953140, 0.998001695, 0.000000000, -0.000100776466, 1.00000000, 0.000212745901, 0.00000, -0.998001695, -0.000114017617, 0.0631858706, 0.000000000, -247.105850, 0.943301678, 181.244659, 1.00000000 };
	double trs_check_2[16] = { -0.519562244, 0.000487311278, -0.854432404, 0.000000000, 0.000972712180, 0.999999523, -2.11526640e-05, 0.000000000, 0.854432046, -0.000842106936, -0.519562483, 0.000000000, -351.236053, 0.942809284, 357.682098, 1.00000000 };
	double trs_check_3[16] = { 0.0142891407, 2.21712980e-06, 0.999897957, 0.000000000, -0.00144030584, 0.999998987, 1.83655648e-05, 0.000000000, -0.999896884, -0.00144042121, 0.0142891407, 0.000000000, -159.197052, -2.55745268, 70.5717545, 1.00000000 };
	double trs_check_4[16];
};
