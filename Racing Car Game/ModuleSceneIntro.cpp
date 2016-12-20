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
	road_cubes[0].size = vec3(10, 1, 20);
	road_cubes[0].SetPos(0, 0, 5);

	road_cubes[1].size = vec3(10, 1, 20);
	road_cubes[1].SetPos(0, 0, 25);
	road_cubes[1].color = Green;

	sensor.size = vec3(10, 10, 20);
	sensor.SetPos(0, 0, 25);
	
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	//slow block
	road_cubes[2].size = vec3(10, 1, 20);
	road_cubes[2].SetPos(0, 0, 45);
	road_cubes[2].color = Black;

	sensor.SetPos(0, 0, 45);

	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	slow_road.PushBack(body_sensor);

	//falling block
	road_cubes[3].size = vec3(10, 1, 20);
	road_cubes[3].SetPos(0, 0, 65);
	road_cubes[3].color = Red;

	for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);
	}

	s.size = vec3(5, 3, 1);
	s.SetPos(100, 2.5f, 20);

	body_sensor = App->physics->AddBody(s, 0.0f);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);

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

	body_sensor->GetTransform(&s.transform);
	s.Render();

	for (uint i = 0; i < road_cubes.Count(); i++)
		road_cubes[i].Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	for (int i = 0; i < turbo_road.Count(); i++) {
		if (turbo_road[i] == body1) {
			App->player->car_state = FAST;
		}

		for (int i = 0; i < turbo_road.Count(); i++) {
			if (slow_road[i] == body1) {
				App->player->car_state = SLOW;
			}
		}
	}
}

