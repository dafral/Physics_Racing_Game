#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"

#define WHITE (cube->color.r == 1) && (cube->color.g == 1) && (cube->color.b == 1)
#define BLACK (cube->color.r == 0) && (cube->color.g == 0) && (cube->color.b == 0)
#define RED (cube->color.r == 1) && (cube->color.g == 0) && (cube->color.b == 0)
#define GREEN (cube->color.r == 0) && (cube->color.g == 1) && (cube->color.b == 0)

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
	
	//----------ROTATING PLATFORM--------------
	/*motor.radius = 1.0;
	motor.SetPos(0, 2, 100);
	//motor.SetRotation(90.0, vec3(-1,0,0));

	platform.size = vec3(25, 1, 25);
	platform.SetPos(0, 0, 200);

	PhysBody3D* bodyA = App->physics->AddBody(motor, 0);
	PhysBody3D* bodyB = App->physics->AddBody(platform, 10);

	App->physics->AddConstraintHinge(*bodyA, *bodyB, vec3(0,0,0), vec3(25,0,25), vec3(0, 1, 0), vec3(0, 1, 0), true);*/


	//normal blocks
	floor.size = vec3(10, 1, 20);
	floor.SetPos(0, 0, 5);
	
	road_cubes.PushBack(floor);

	block1.SetPos(0, 0, 0);
	block1.size = { 20, 10, 50 };
	App->physics->AddBody(block1, 0);
	circuit.PushBack(&block1);

	block2.SetPos(-10, 0, 17.5f);
	block2.size = { 20,10,15 };
	block2.SetRotation(45.0f, { 0,1,0 });
	App->physics->AddBody(block2, 0);
	circuit.PushBack(&block2);

	block3.SetPos(-25, 0, 15);
	block3.size = { 20,10,15 };
	block3.SetRotation(30.0f, { 0,1,0 });
	App->physics->AddBody(block3, 0);
	circuit.PushBack(&block3);

	ramp.SetPos(-28, 0, 10);
	ramp.size = { 20,10,15 };
	ramp.SetRotation(25.0f, { 1,1,0 });
	App->physics->AddBody(ramp, 0);
	circuit.PushBack(&ramp);

	ramp2.SetPos(-28, 0, -20);
	ramp2.size = { 20,10,15 };
	ramp2.SetRotation(-25.0f, { 1,0,0 });
	App->physics->AddBody(ramp2, 0);
	circuit.PushBack(&ramp2);

	block4.SetPos(-28, 0, -27);
	block4.size = { 20,6, 20 };
	App->physics->AddBody(block4, 0);
	circuit.PushBack(&block4);

	block5.SetPos(-35, 0, -40);
	block5.size = { 17,6, 20 };
	block5.SetRotation(25.0f, { 0,1,0 });
	App->physics->AddBody(block5, 0);
	circuit.PushBack(&block5);

	block6.SetPos(-45, 0, -35);
	block6.size = { 17,6, 20 };
	block6.SetRotation(20.0f, { 0,1,0 });
	App->physics->AddBody(block6, 0);
	circuit.PushBack(&block6);

	block7.SetPos(-45, 0, -25);
	block7.size = { 17,6, 20 };
	App->physics->AddBody(block7, 0);
	circuit.PushBack(&block7);


	block8.SetPos(-45, 0, -10);
	block8.size = { 17,6, 20 };
	block8.SetRotation(20.0f, { 0,1,0 });
	App->physics->AddBody(block8, 0);
	circuit.PushBack(&block8);

	block9.SetPos(-35, 0, -10);
	block9.size = { 17,4, 20 };
	block9.SetRotation(20.0f, { 0,1,0 });
	App->physics->AddBody(block9, 0);
	circuit.PushBack(&block9);

	sens.size = vec3(17, 1, 17);
	sens.SetPos(-28, 5, -10);
	ramp_sensor = App->physics->AddBody(sens, 0.0f);
	ramp_sensor->SetAsSensor(true);
	ramp_sensor->collision_listeners.add(this);

	block10.SetPos(-25, 0, -10);
	block10.size = { 17,4, 20 };
	block10.SetRotation(-10.0f, { 0,1,0 });
	App->physics->AddBody(block10, 0);
	circuit.PushBack(&block10);

	block11.SetPos(-20, 0, -10);
	block11.size = { 17,4, 20 };
	block11.SetRotation(-30.0f, { 0,1,0 });
	App->physics->AddBody(block11, 0);
	circuit.PushBack(&block11);

	block12.SetPos(-20, 0, -20);
	block12.size = { 20,4, 20 };
	block12.SetRotation(-10.0f, { 0,1,0 });
	App->physics->AddBody(block12, 0);
	circuit.PushBack(&block12);

	block13.SetPos(-20, 0, -30);
	block13.size = { 20,4, 20 };
	App->physics->AddBody(block13, 0);
	circuit.PushBack(&block13);



	//turbo block
	/*turbo.size = vec3(10, 1, 20);
	turbo.SetPos(0, 0, 25);
	turbo.color = Green;

	road_cubes.PushBack(turbo);

	Cube turbo_sensor;
	turbo_sensor.size = vec3(10, 10, 20);
	turbo_sensor.SetPos(0, 0, 25);
	
	PhysBody3D* turbo;
	turbo = App->physics->AddBody(turbo_sensor, 0);
	turbo->SetAsSensor(true);
	turbo->collision_listeners.add(this);

	turbo_road.PushBack(turbo);


	//slow block
	slow.size = vec3(10, 1, 20);
	slow.SetPos(0, 0, 45);
	slow.color = Black;
	
	road_cubes.PushBack(slow);

	Cube slow_sensor;
	slow_sensor.size = vec3(10, 10, 20);
	slow_sensor.SetPos(0, 0, 45);

	PhysBody3D* slow;
	slow = App->physics->AddBody(slow_sensor, 0);
	slow->SetAsSensor(true);
	slow->collision_listeners.add(this);

	slow_road.PushBack(slow);

	//falling block
	falling.size = vec3(10, 1, 20);
	falling.SetPos(0, 0, 65);
	falling.color = Red;
	
	road_cubes.PushBack(falling);*/

	/*for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);*/
		/*if (road_cubes[i].size.y == 3) {
			turbo_road.PushBack(body);
			turbo_road[turbo_road.Count() - 1]->SetAsSensor(true);
			//turbo_road[turbo_road.Count() - 1]->collision_listeners.add(this);
		}
	}*/

	/*s.size = vec3(5, 3, 1);
	s.SetPos(100, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);
	*/
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
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	/*sensor->GetTransform(&s.transform);
	s.Render();*/

	for (uint i = 0; i < circuit.Count(); i++) {
		circuit[i]->Render();
	}
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

