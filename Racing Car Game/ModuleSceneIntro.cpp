#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	
	race_time.Start();

	//----------ROTATING PLATFORM--------------
	/*motor.radius = 1.0;
	motor.SetPos(0, 2, 100);
	//motor.SetRotation(90.0, vec3(-1,0,0));

	platform.size = vec3(25, 1, 25);
	platform.SetPos(0, 0, 200);

	PhysBody3D* bodyA = App->physics->AddBody(motor, 0);
	PhysBody3D* bodyB = App->physics->AddBody(platform, 10);

	App->physics->AddConstraintHinge(*bodyA, *bodyB, vec3(0,0,0), vec3(25,0,25), vec3(0, 1, 0), vec3(0, 1, 0), true);*/

	//We create here how many cubes we need to make the map
	for (uint i = 0; i < 100; i++) {
		Cube map_cube;
		road_cubes.PushBack(map_cube);
	}

	//position, color and size of the blocks (MAP CREATION)
	//Green for turbo, Black for slow, Red for falling and no color specification to normal cubes
	//si necesitas acordarte de algun cubo especifico pon un comentario

	/*-----EJEMPLO DE COMO CREAR UN CUBO ESPECIAL CON SENSOR------

	road_cubes[1].size = vec3(10, 1, 20);
	road_cubes[1].SetPos(0, 0, 25);
	road_cubes[1].color = Green; ----------> (Green es turbo);
	
	-------AQUI CREAMOS EL SENSOR--------

	sensor.size = vec3(10, 10, 20); -----------------> usa siempre sensor y body_sensor, no crees mas variables
	sensor.SetPos(0, 0, 25);

	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor); ------------------> lo metes en la array de esos cubos (este es verde asi que va en turbo)
	
	*/


	road_cubes[0].SetPos(0, 0, 5);
	road_cubes[0].size = vec3(10, 1, 20); //<------------ pon todos con vec3 como este
	
	road_cubes[1].SetPos(0, 0, 0);
	road_cubes[1].size = { 20, 10, 50 };

	road_cubes[2].SetPos(-10, 0, 17.5f);
	road_cubes[2].size = { 20,10,15 };
	road_cubes[2].SetRotation(45.0f, { 0,1,0 });

	road_cubes[3].SetPos(-25, 0, 15);
	road_cubes[3].size = { 20,10,15 };
	road_cubes[3].SetRotation(30.0f, { 0,1,0 });
	
	road_cubes[4].SetPos(-28, 0, 10);
	road_cubes[4].size = { 20,10,15 };
	road_cubes[4].SetRotation(25.0f, { 1,1,0 });

	road_cubes[5].SetPos(-28, 0, -20);
	road_cubes[5].size = { 20,10,15 };
	road_cubes[5].SetRotation(-25.0f, { 1,0,0 });

	road_cubes[6].SetPos(-28, 0, -27);
	road_cubes[6].size = { 20,6, 20 };

	road_cubes[7].SetPos(-35, 0, -40);
	road_cubes[7].size = { 17,6, 20 };
	road_cubes[7].SetRotation(25.0f, { 0,1,0 });

	road_cubes[8].SetPos(-45, 0, -35);
	road_cubes[8].size = { 17,6, 20 };
	road_cubes[8].SetRotation(20.0f, { 0,1,0 });

	road_cubes[9].SetPos(-45, 0, -25);
	road_cubes[9].size = { 17,6, 20 };

	road_cubes[10].SetPos(-45, 0, -10);
	road_cubes[10].size = { 17,6, 20 };
	road_cubes[10].SetRotation(20.0f, { 0,1,0 });

	road_cubes[11].SetPos(-35, 0, -10);
	road_cubes[11].size = { 17,4, 20 };
	road_cubes[11].SetRotation(20.0f, { 0,1,0 });

	road_cubes[12].SetPos(-25, 0, -10);
	road_cubes[12].size = { 17,4, 20 };
	road_cubes[12].SetRotation(-10.0f, { 0,1,0 });

	road_cubes[13].SetPos(-20, 0, -10);
	road_cubes[13].size = { 17,4, 20 };
	road_cubes[13].SetRotation(-30.0f, { 0,1,0 });
	
	road_cubes[14].SetPos(-20, 0, -20);
	road_cubes[14].size = { 20,4, 20 };
	road_cubes[14].SetRotation(-10.0f, { 0,1,0 });
	
	road_cubes[15].SetPos(-20, 0, -30);
	road_cubes[15].size = { 20, 4, 20 };

	
	for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);
	}

	/*sens.size = vec3(17, 1, 17);
	sens.SetPos(-28, 5, -10);
	ramp_sensor = App->physics->AddBody(sens, 0.0f);
	ramp_sensor->SetAsSensor(true);
	ramp_sensor->collision_listeners.add(this);*/

	return ret;

}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/*Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	body_sensor->GetTransform(&s.transform);
	s.Render();*/

	for (uint i = 0; i < road_cubes.Count(); i++)
		road_cubes[i].Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	/*for (int i = 0; i < turbo_road.Count(); i++) {
		if (turbo_road[i] == body1) {
			App->player->car_state = FAST;
		}

		for (int i = 0; i < turbo_road.Count(); i++) {
			if (slow_road[i] == body1) {
				App->player->car_state = SLOW;
			}
		}
	}*/
}

