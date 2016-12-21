#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

#define CHEATING1 App->player->check_position.x == cp_coords[0].x && App->player->check_position.y == cp_coords[0].y && App->player->check_position.y == cp_coords[0].y 
#define CHEATING2 App->player->check_position.x == cp_coords[1].x && App->player->check_position.y == cp_coords[1].y && App->player->check_position.y == cp_coords[1].y 
#define CHECK3 App->player->check_position.x == cp_coords[3].x && App->player->check_position.y == cp_coords[3].y && App->player->check_position.z == cp_coords[3].z
#define CHECK0 App->player->check_position.x == cp_coords[0].x && App->player->check_position.y == cp_coords[0].y && App->player->check_position.z == cp_coords[0].z

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
	//ACORDARSE DE CAMBIAR ESTO!!!!!!!!!! 
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
	road_cubes[16].size = vec3(14, 1, 60);
	road_cubes[16].SetRotation(-45.0f, vec3(0.2, 1, 0.2));

	//esto es lo que tienes que hacer
	road_cubes[17].SetPos(-300, -11, 300);
	road_cubes[17].size = vec3(15, 1, 30);


	road_cubes[24].SetPos(-304, -11, 275);
	road_cubes[24].size = vec3(7, 1, 20);
	road_cubes[24].color  = Black;
	sensor.size = vec3(7, 20, 20);
	sensor.SetPos(-304, -11, 275);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[25].SetPos(-297, -11, 275);
	road_cubes[25].size = vec3(7, 1, 20);

	road_cubes[26].SetPos(-297, -11, 245);
	road_cubes[26].size = vec3(7, 1, 20);
	road_cubes[26].color = Black;
	sensor.size = vec3(7, 20, 20);
	sensor.SetPos(-297, -11, 245);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[27].SetPos(-304, -11, 245);
	road_cubes[27].size = vec3(7, 1, 20);

	road_cubes[28].SetPos(-300.5, -11, 225);
	road_cubes[28].size = vec3(14, 1, 20);

	road_cubes[29].SetPos(-300.5, -11, 260);
	road_cubes[29].size = vec3(14, 1, 10);

	road_cubes[30].SetPos(-300.5, -11, 205);
	road_cubes[30].size = vec3(4, 1, 20);

	road_cubes[31].SetPos(-300.5, -11, 190);
	road_cubes[31].size = vec3(12, 1, 10);

	road_cubes[32].SetPos(-296.5, -11, 180);
	road_cubes[32].size = vec3(4, 1, 10);

	road_cubes[33].SetPos(-304.5, -11, 180);
	road_cubes[33].size = vec3(4, 1, 10);
	road_cubes[33].color = Green;
	sensor.size = vec3(4, 20, 10);
	sensor.SetPos(-304.5, -11, 180);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[34].SetPos(-300.5, -11, 170);
	road_cubes[34].size = vec3(12, 1, 10);

	road_cubes[35].SetPos(-300.5, -11, 160);
	road_cubes[35].size = vec3(12, 1, 20);

	road_cubes[36].SetPos(-288.5, -11, 160);
	road_cubes[36].size = vec3(12, 1, 20);

	road_cubes[37].SetPos(-276.5, -11, 160);
	road_cubes[37].size = vec3(12, 1, 20);

	road_cubes[38].SetPos(-264.5, -11, 152.5);
	road_cubes[38].size = vec3(12, 1, 5);

	road_cubes[39].SetPos(-264.5, -11, 165);
	road_cubes[39].size = vec3(12, 1, 5);
	road_cubes[39].color = Black;
	sensor.size = vec3(12, 20, 5);
	sensor.SetPos(-264.5, -11, 165);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[40].SetPos(-252.5, -11, 160);
	road_cubes[40].size = vec3(12, 1,20);

	road_cubes[41].SetPos(-240.5, -9, 160);
	road_cubes[41].size = vec3(12, 1, 10);
	road_cubes[41].SetRotation(20.0f, vec3(0, 0, 1));

	road_cubes[42].SetPos(-229.25, -7, 160);
	road_cubes[42].size = vec3(12, 1, 10);

	road_cubes[43].SetPos(-217.25, -7, 160);
	road_cubes[43].size = vec3(12, 1, 10);
	
	road_cubes[43].SetPos(-217.25, -7, 160);
	road_cubes[43].size = vec3(12, 1, 10);

	road_cubes[44].SetPos(-217.25, -7, 150);
	road_cubes[44].size = vec3(12, 1, 10);

	road_cubes[45].SetPos(-217.25, -7, 140);
	road_cubes[45].size = vec3(12, 1, 10);

	road_cubes[46].SetPos(-205.25, -7, 140);
	road_cubes[46].size = vec3(12, 1, 10);

	road_cubes[47].SetPos(-205.25, -7, 130);
	road_cubes[47].size = vec3(12, 1, 10);

	road_cubes[48].SetPos(-205.25, -7, 120);
	road_cubes[48].size = vec3(12, 1, 10);

	road_cubes[49].SetPos(-193.25, -7, 120);
	road_cubes[49].size = vec3(12, 1, 10);

	road_cubes[50].SetPos(-181.25, -7, 120);
	road_cubes[50].size = vec3(12, 1, 10);

	road_cubes[51].SetPos(-169.25, -7, 120);
	road_cubes[51].size = vec3(12, 1, 10);

	road_cubes[52].SetPos(-157.25, -7, 120);
	road_cubes[52].size = vec3(12, 1, 10);

	road_cubes[53].SetPos(-157.25, -7, 110);
	road_cubes[53].size = vec3(12, 1, 10);

	road_cubes[54].SetPos(-157.25, -5.5, 101);
	road_cubes[54].size = vec3(12, 1, 10);
	road_cubes[54].SetRotation(20.0f, vec3(1, 0, 0));

	road_cubes[55].SetPos(-157.25, -3.5, 91);
	road_cubes[55].size = vec3(12, 1, 10);

	road_cubes[56].SetPos(-157.25, -3.5, 81);
	road_cubes[56].size = vec3(12, 1, 10);

	road_cubes[57].SetPos(-157.25, -3.5, 71);
	road_cubes[57].size = vec3(12, 1, 10);

	road_cubes[58].SetPos(-169.25, -3.5, 71);
	road_cubes[58].size = vec3(12, 1, 10);

	road_cubes[59].SetPos(-157.25, -3.5, 61);
	road_cubes[59].size = vec3(12, 1, 10);

	road_cubes[60].SetPos(-169.25, -3.5, 61);
	road_cubes[60].size = vec3(12, 1, 10);

	road_cubes[61].SetPos(-180.25, -5.5, 61);
	road_cubes[61].size = vec3(12, 1, 10);
	road_cubes[61].SetRotation(20.0f, vec3(0, 0, 1));

	road_cubes[62].SetPos(-180.25, -5.5, 71);
	road_cubes[62].size = vec3(12, 1, 10);
	road_cubes[62].SetRotation(20.0f, vec3(0, 0, 1));

	road_cubes[63].SetPos(-192.25, -7.5, 71);
	road_cubes[63].size = vec3(12, 1, 10);
	road_cubes[63].color = Black;
	sensor.size = vec3(12, 20, 5);
	sensor.SetPos(-192.25, -7.5, 715);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);

	road_cubes[64].SetPos(-192.25, -7.5, 61);
	road_cubes[64].size = vec3(12, 1, 10);
	road_cubes[64].color = Green;
	sensor.size = vec3(12, 20, 5);
	sensor.SetPos(-192.25, -7.5, 61);
	body_sensor = App->physics->AddBody(sensor, 0);
	body_sensor->SetAsSensor(true);
	body_sensor->collision_listeners.add(this);
	turbo_road.PushBack(body_sensor);
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

	for (uint i = 0; i < road_cubes.Count(); i++) {
		PhysBody3D* body;
		body = App->physics->AddBody(road_cubes[i], 0);
		road.PushBack(body);
	}

	//CHECKPOINT CREATION
	cp_coords.PushBack(vec3( 0, 2, -22 ));
	cp_coords.PushBack(vec3( -250, 2, 182 ));
	cp_coords.PushBack(vec3(-349, 2, 355));
	cp_coords.PushBack(vec3( -300, -18, -100 ));

	for (uint i = 0; i < 4; i++) {
		Cube map_cube;
		map_cube.size = vec3(2, 100, 2);
		map_cube.SetPos(cp_coords[i].x, cp_coords[i].y, cp_coords[i].z);
		map_cube.color = Red;

		cp_cubes.PushBack(map_cube);

		checkpoints.PushBack(App->physics->AddBody(map_cube, 0));
		checkpoints[i]->SetAsSensor(true);
		checkpoints[i]->collision_listeners.add(this);
	}

	//DEATH BLOCKS CREATION
	Cube map_cube;
	map_cube.size = vec3(1000, 1, 1000);
	map_cube.SetPos( 0, -8, 0 );

	//anti-cheaters block :^)
	death_blocks.PushBack(App->physics->AddBody(map_cube, 0));
	death_blocks[0]->SetAsSensor(true);
	death_blocks[0]->collision_listeners.add(this);

	map_cube.SetPos(0, -25, 0);
	death_blocks.PushBack(App->physics->AddBody(map_cube, 0));
	death_blocks[1]->SetAsSensor(true);
	death_blocks[1]->collision_listeners.add(this);
	

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

	for (uint i = 0; i < road_cubes.Count(); i++)
		road_cubes[i].Render();

	if((cp_coords[3].x == App->player->check_position.x && cp_coords[3].y == App->player->check_position.y && cp_coords[3].z == App->player->check_position.z))
		cp_cubes[0].Render();

	else {
		for (uint i = 0; i < cp_coords.Count() - 1; i++) {
			if (cp_coords[i].x == App->player->check_position.x && cp_coords[i].y == App->player->check_position.y && cp_coords[i].z == App->player->check_position.z)
				cp_cubes[i + 1].Render();
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	for (int i = 0; i < turbo_road.Count(); i++) {
		if (turbo_road[i] == body1) {
			App->player->car_state = FAST;
		}

		//CUANDO PONGAS BLOQUES DE SLOW QUITA ESTE COMENT
		/*for (int i = 0; i < turbo_road.Count(); i++) {
			if (slow_road[i] == body1) {
				App->player->car_state = SLOW;
			}
		}*/

		for (int i = 0; i < checkpoints.Count(); i++) {
			if (checkpoints[i] == body1) {
				//these ifs avoid skipping checkpoints
				if (i == 0 && (CHECK0 || CHECK3)) {
					App->player->check_position = cp_coords[i];
					App->player->vehicle->GetTransform(App->player->idle_trans);
					if (CHECK3)
						laps++;
				}
				else if (App->player->check_position.x == cp_coords[i - 1].x && App->player->check_position.y == cp_coords[i - 1].y && App->player->check_position.z == cp_coords[i - 1].z){
					App->player->check_position = cp_coords[i];
					App->player->vehicle->GetTransform(App->player->idle_trans);
				}
			}

		if (death_blocks[1] == body1) {
			App->player->vehicle->SetPos(App->player->check_position.x, App->player->check_position.y, App->player->check_position.z);
			App->player->vehicle->SetTransform(App->player->idle_trans);
		}

		else if(death_blocks[0] == body1)
			if (CHEATING1 || CHEATING2) {
				App->player->vehicle->SetPos(App->player->check_position.x, App->player->check_position.y, App->player->check_position.z);
				App->player->vehicle->SetTransform(App->player->idle_trans);
			}
		}
	}
}

