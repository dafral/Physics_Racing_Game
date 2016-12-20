#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

//this defines are for the lookat()
#define CAMERA_X App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() + 10 * App->player->vehicle->vehicle->getForwardVector().getX()
#define CAMERA_Y App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() - 3 //* App->player->vehicle->vehicle->getForwardVector().getY()
#define CAMERA_Z App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() + 10 * App->player->vehicle->vehicle->getForwardVector().getZ()

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;
	
	check_position = App->scene_intro->cp_coords[0];
	StartCar(check_position);

	vehicle->GetTransform(idle_trans);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{

		acceleration = MAX_ACCELERATION;

		if (car_state == FAST) {
			acceleration = acceleration * 1.2;
			car_state = NORMAL;
		}

		else if (car_state == SLOW) {
			acceleration = 0.00000001;
			/*if(acceleration > 400)
				brake = 20;
			//brake = 20;*/
			car_state = NORMAL;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		acceleration = -1000.0;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->SetPos(check_position.x, check_position.y, check_position.z);
		vehicle->SetTransform(idle_trans);
	}


	//camera following the car
	App->camera->Position.x = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() - 10 * App->player->vehicle->vehicle->getForwardVector().getX();
	App->camera->Position.z = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() - 10 * App->player->vehicle->vehicle->getForwardVector().getZ();
	App->camera->Position.y = App->player->vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() + 8 * App->player->vehicle->vehicle->getUpAxis();

	App->camera->LookAt(vec3(CAMERA_X, CAMERA_Y, CAMERA_Z));

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h // Time: %ds // Laps: %d", vehicle->GetKmh(), App->scene_intro->race_time.Read()/1000, App->scene_intro->laps);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::StartCar(vec3 pos) {

	VehicleInfo car;
	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 250.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(pos.x, pos.y, pos.z);

}



