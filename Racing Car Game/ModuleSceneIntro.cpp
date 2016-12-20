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
	road_cubes[0].size = vec3(15, 1, 80);

	road_cubes[1].SetPos(-5, 0, 50);
	road_cubes[1].size = vec3(15, 1, 30);
	road_cubes[1].SetRotation(-45.0f, { 0,1,0 });

	road_cubes[2].SetPos(-15, 0, 80);
	road_cubes[2].size = vec3(15, 1, 40);

	//turbo 1
	road_cubes[3].SetPos(-18.75, 0, 115);
	road_cubes[3].size = vec3(7.5, 1, 30);
	road_cubes[3].color = Green;
	sensor.size = vec3(7.5, 20, 30);
	sensor.SetPos(-18.75, 0, 115);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[4].SetPos(-11.25, 0, 115);
	road_cubes[4].size = vec3(7.5, 1, 30);

	//turbo 2
	road_cubes[5].SetPos(-11.25, 0, 145);
	road_cubes[5].size = vec3(7.5, 1, 30);
	road_cubes[5].color = Green;
	sensor.size = vec3(7.5, 20, 30);
	sensor.SetPos(-11.25, 0, 145);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[6].SetPos(-18.75, 0, 145);
	road_cubes[6].size = vec3(7.5, 1, 30);

	road_cubes[7].SetPos(-25, 0, 170);
	road_cubes[7].size = vec3(15, 1, 30);
	road_cubes[7].SetRotation(-45.0f, { 0,1,0 });

	road_cubes[8].SetPos(-50, 0, 182);
	road_cubes[8].size = vec3(15, 1, 40);
	road_cubes[8].SetRotation(-90.0f, { 0,1,0 });

	//turbo 3
	road_cubes[9].SetPos(-80, 0, 182);
	road_cubes[9].size = vec3(15, 1, 20);
	road_cubes[9].SetRotation(-90.0f, { 0,1,0 });
	road_cubes[9].color = Green;
	sensor.size = vec3(15, 20, 20);
	sensor.SetPos(-80, 0, 182);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	//rampa 1
	road_cubes[10].SetPos(-90, 0, 182);
	road_cubes[10].size = vec3(15, 1, 20);
	road_cubes[10].SetRotation(-90.0f, vec3(0.2, 1, 0.2));

	road_cubes[11].SetPos(-250, 0, 182);
	road_cubes[11].size = vec3(40, 1, 150);
	road_cubes[11].SetRotation(-90.0f, vec3(0, 1, 0));

	road_cubes[12].SetPos(-330, 0, 210);
	road_cubes[12].size = vec3(15, 1, 40);
	road_cubes[12].SetRotation(-45.0f, vec3(0, 1, 0));

	//thin platform
	road_cubes[13].SetPos(-345, 0, 250);
	road_cubes[13].size = vec3(5, 1, 60);

	road_cubes[14].SetPos(-348, 0, 310);
	road_cubes[14].size = vec3(5, 1, 60);

	road_cubes[15].SetPos(-349, 0, 355);
	road_cubes[15].size = vec3(30, 1, 30);

	road_cubes[16].SetPos(-315, -6, 330);
	road_cubes[16].size = vec3(15, 1, 60);
	road_cubes[16].SetRotation(-45.0f, vec3(0.2, 1, 0.2));

	//esto es lo que tienes que hacer
	road_cubes[17].SetPos(-300, -12, 210);
	road_cubes[17].size = vec3(30, 1, 200);








	//ROTATING PLATFORM
	motor.radius = 1.0;
	motor.SetPos(-300, -15, 20);
	//motor.SetRotation(90.0, vec3(-1,0,0));
	platform.size = vec3(50, 1, 50);
	platform.SetPos(0, 0, 200);

	PhysBody3D* bodyA = App->physics->AddBody(motor, 0);
	PhysBody3D* bodyB = App->physics->AddBody(platform, 10);
	App->physics->AddConstraintHinge(*bodyA, *bodyB, vec3(0, 0, 0), vec3(50, 0, 50), vec3(0, 1, 0), vec3(0, 1, 0), true);

	//After rotating platform
	road_cubes[18].SetPos(-300, -18, -100);
	road_cubes[18].size = vec3(50, 1, 50);

	road_cubes[19].SetPos(-260, -13, -120);
	road_cubes[19].size = vec3(50, 1, 15);
	road_cubes[19].SetRotation(45.0f, vec3(0.2, 1, 0.2));

	road_cubes[20].SetPos(-200, -8, -120);
	road_cubes[20].size = vec3(30, 1, 80);
	road_cubes[20].SetRotation(-90.0f, vec3(-0.2, 1, -0.2));

	road_cubes[21].SetPos(-100, 0, -120);
	road_cubes[21].size = vec3(80, 1, 20);
	road_cubes[21].SetRotation(20.0f, vec3(0, 1, 0));

	road_cubes[22].SetPos(-50, 0, -100);
	road_cubes[22].size = vec3(80, 1, 20);
	road_cubes[22].SetRotation(-30.0f, vec3(0, 1, 0));

	road_cubes[23].SetPos(-20, 0, -60);
	road_cubes[23].size = vec3(90, 1, 20);
	road_cubes[23].SetRotation(-60.0f, vec3(0, 1, 0));

	//final : 0 0 -35

	for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);
	}

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

