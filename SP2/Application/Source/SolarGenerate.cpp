#include "SolarGenerate.h"
#include "MyMath.h"
#include "GreenPlanet.h"

SolarGenerate::SolarGenerate(SystemScene* scene) : myscene(scene), objfactory(scene)
{
	number_of_planets = 0;
}

SolarGenerate::~SolarGenerate()
{

}

void SolarGenerate::Init()
{
	float ar, pr;
	number_of_planets = Math::RandIntMinMax(1, 3);
	
	//orbit line increases by scale by (3 + (3 * 2) * i)
	//planet translation by (3 + (3 * 2) * i)

	for (int i = 1; i <= number_of_planets; i++)
	{
		ar = Math::RandFloatMinMax(-5.f, 5.f);
		pr = Math::RandFloatMinMax(-2.f, 6.f);

		GreenPlanet* gPlanet = new GreenPlanet(myscene, Vector3(9 * i, 0, 0), 1, 1, ar, pr);
		planet_storage.push_back(gPlanet);
		this->objfactory.createSystemObject(gPlanet);

		//std::cout << ar << "\n";
		//std::cout << pr << "\n";
	}

}

void SolarGenerate::build_system(float aRotate,float pRotate)
{
	objfactory.renderSystemObjects(aRotate, pRotate);
}

int SolarGenerate::num_of_planet_getter()
{
	return number_of_planets;
}

vector<ObjectRender*> SolarGenerate::planet_storage_getter()
{
	return planet_storage;
}