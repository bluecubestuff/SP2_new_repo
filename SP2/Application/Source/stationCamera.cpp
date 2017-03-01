#include "stationCamera.h"

StationCamera::StationCamera()
{
	Area = new Func_AABB(Vector3(-100, 0, -59), Vector3(100, 30, 339));
	//=========================================================================
	hitbox = new Func_AABB(Vector3(-90, 0, 40), Vector3(-30, 10, 50));	//right wall
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(-40, 0, 80), Vector3(-30, 10, 200));	//hardcode is best code
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(-90, 0, 230), Vector3(-30, 10, 240));//this is disgusting me
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(-90, 0, 97.5), Vector3(-70, 10, 182.5)); //3
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(-100, 0, 40), Vector3(-90, 10, 240));
	hitboxes.push_back(hitbox);
	//=========================================================================
	hitbox = new Func_AABB(Vector3(30, 0, 40), Vector3(90, 10, 50));	//left wall
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(30, 0, 80), Vector3(40, 10, 200));	//hardcode is best code
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(30, 0, 230), Vector3(90, 10, 240));	//this is disgusting me
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(70, 0, 97.5), Vector3(90, 0, 182.5)); //8
	hitboxes.push_back(hitbox);
	hitbox = new Func_AABB(Vector3(90, 0, 40), Vector3(100, 10, 240));
	hitboxes.push_back(hitbox); 
}

StationCamera::~StationCamera()
{

}

void StationCamera::Init(Vector3 pos, Vector3 target, Vector3 up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	forward = target - position;
	forward.Normalize();
	right = forward.Cross(up);
	right.Normalize();
	pitchLimit = 0.f;
}

void StationCamera::Update(double dt)
{
	static const float CAMERA_SPEED = 0.1f * dt;
	static float MOVEMENT_SPEED = 40.f * dt;

	Vector3 temp = forward;
	temp.y = 0;
	temp.Normalize();
	Vector3 rTemp = right;
	rTemp.y = 0;
	rTemp.Normalize();

	Vector3 infront = position + temp;
	Vector3 behind = position - temp;
	Vector3 left = position - rTemp;
	Vector3 righty = position + rTemp;

	if (Application::IsKeyPressed('W'))
	{
		bool move = true;
		for (auto &i : hitboxes)
		{
			if(i->pointInAABB(infront))
			{
				move = false;
			}
		}
		if (move)
		{
			if (Area->pointInAABB(infront))
				position += temp * MOVEMENT_SPEED;
		}
	}
	else if (Application::IsKeyPressed('S'))
	{
		bool move = true;
		for (auto &i : hitboxes)
		{
			if (i->pointInAABB(behind))
			{
				move = false;
			}
		}
		if (move)
		{
			if (Area->pointInAABB(behind))
				position -= temp * MOVEMENT_SPEED;
		}
	}

	if (Application::IsKeyPressed('A'))
	{
		bool move = true;
		for (auto &i : hitboxes)
		{
			if (i->pointInAABB(left))
			{
				move = false;
			}
		}
		if (move)
		{
			if (Area->pointInAABB(left))
				position -= rTemp * MOVEMENT_SPEED * 0.5;
		}
	}
	else if (Application::IsKeyPressed('D'))
	{
		bool move = true;
		for (auto &i : hitboxes)
		{
			if (i->pointInAABB(righty))
			{
				move = false;
			}
		}
		if (move)
		{
			if (Area->pointInAABB(righty))
				position += rTemp * MOVEMENT_SPEED * 0.5;
		}
	}

	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		MOVEMENT_SPEED = 60.f * dt;
	}
	else
	{
		MOVEMENT_SPEED = 40.f * dt;
	}

	static bool selling = false;;
	if (hitboxes[3]->pointInAABB(infront))	//right
	{
		static bool pressing = false;
		if (Application::IsKeyPressed('E') && pressing == false)
		{
			if (selling)
				selling = false;
			else
				selling = true;
			pressing = true;
		}
		else if (!Application::IsKeyPressed('E'))
		{
			pressing = false;
		}
	}
	if (selling)
	{
		npc.sell();
	}

	static bool crafting = false;
	if (hitboxes[8]->pointInAABB(infront))	//left
	{
		static bool pressing = false;
		
		if (Application::IsKeyPressed('E') && pressing == false)
		{
			if (crafting)
				crafting = false;
			else
				crafting = true;
			pressing = true;
		}
		else if (!Application::IsKeyPressed('E'))
		{
			pressing = false;
		}
	}
	if (crafting)
	{
		npc.craft();
	}

	//if (Area->pointInAABB(infront) && Area->pointInAABB(behind) && Area->pointInAABB(left) && Area->pointInAABB(righty))
	//	std::cout << "Kitson" << std::endl;
	//else
	//	std::cout << "wall" << std::endl;
	//std::cout << MOVEMENT_SPEED << std::endl;

	mousePos = mouse.mouseMovement();
	if (mousePos.x)
	{
		Mtx44 rotation;
		rotation.SetToRotation(-mousePos.x * CAMERA_SPEED, 0, 1, 0);
		forward = rotation * forward;
		right = rotation * right;
	}

	if (mousePos.y > 0 && pitchLimit < 89)
	{
		Mtx44 rotation;
		rotation.SetToRotation(-mousePos.y * CAMERA_SPEED, right.x, right.y, right.z);
		forward = rotation * forward;
		pitchLimit += mousePos.y * CAMERA_SPEED;
	}
	else if (mousePos.y < 0 && pitchLimit > -89)
	{
		Mtx44 rotation;
		rotation.SetToRotation(-mousePos.y * CAMERA_SPEED, right.x, right.y, right.z);
		forward = rotation * forward;
		pitchLimit += mousePos.y * CAMERA_SPEED;
	}

	target = position + forward;
	up = right.Cross(forward).Normalized();
}