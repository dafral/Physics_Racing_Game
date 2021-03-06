#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 600.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

enum state { NORMAL, FAST, SLOW };

class ModulePlayer : public Module
{
private:
	//VehicleInfo car;
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	void StartCar(vec3 pos);
	update_status Update(float dt);
	bool CleanUp();

public:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	//Fx
	
	uint start_fx;
	float idle_trans[16];
	vec3 check_position;
	state car_state = NORMAL;
	float km;
};