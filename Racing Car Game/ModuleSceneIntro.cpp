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
	motor.radius = 1.0;
	motor.SetPos(0, 2, 100);
	//motor.SetRotation(90.0, vec3(-1,0,0));

	platform.size = vec3(25, 1, 25);
	platform.SetPos(0, 0, 200);

	PhysBody3D* bodyA = App->physics->AddBody(motor, 0);
	PhysBody3D* bodyB = App->physics->AddBody(platform, 10);

	App->physics->AddConstraintHinge(*bodyA, *bodyB, vec3(0,0,0), vec3(25,0,25), vec3(0, 1, 0), vec3(0, 1, 0), true);


	//normal blocks
	floor.size = vec3(10, 1, 20);
	floor.SetPos(0, 0, 5);
	
	road_cubes.PushBack(floor);

	//turbo block
	turbo.size = vec3(10, 3, 20);
	turbo.SetPos(0, -1, 25);
	turbo.color = Green;

	road_cubes.PushBack(turbo);


	//slow block
	slow.size = vec3(10, 1, 20);
	slow.SetPos(0, 0, 45);
	slow.color = Black;
	
	road_cubes.PushBack(slow);

	//falling block
	falling.size = vec3(10, 1, 20);
	falling.SetPos(0, 0, 65);
	falling.color = Red;
	
	road_cubes.PushBack(falling);

	for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);
		if (road_cubes[i].size.y == 3) {
			turbo_road.PushBack(body);
			turbo_road[turbo_road.Count() - 1]->SetAsSensor(true);
			//turbo_road[turbo_road.Count() - 1]->collision_listeners.add(this);
		}
	}

	s.size = vec3(5, 3, 1);
	s.SetPos(100, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

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

	sensor->GetTransform(&s.transform);
	s.Render();

	for (uint i = 0; i < road_cubes.Count(); i++)
		road_cubes[i].Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	/*for (uint i = 0; i < road.Count(); i++) {
		if (WHITE) {
			LOG("BLANCOOOOO____________________________");
		}
		else if (GREEN) {
			LOG("VERDEEEEE____________________________");
		}
		else if (RED) {
			LOG("ROJOOOO____________________________");
		}
	}*/

	LOG("HIT");
}

