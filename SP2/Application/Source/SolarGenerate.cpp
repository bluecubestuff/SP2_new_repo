#include "SolarGenerate.h"
#include "MyMath.h"
#include "GreenPlanet.h"
#include "DesertPlanet.h"
#include "BluePlanet.h"
#include "GalaxyGenerate.h"

SolarGenerate::SolarGenerate(SystemScene* scene) : myscene(scene)
{
	objfactory = new ObjectFactory(scene);
	SolarSystemID = 0;
	number_of_planets = 0;
	//planetID = 1;
	this->SolarSystemID = GalaxyGenerate::get_instance()->galaxy_id_getter();
}

SolarGenerate::~SolarGenerate()
{

}

void SolarGenerate::Init()
{
	if (GalaxyGenerate::get_instance()->system_database.size() <= 49) //check (should be redudant)
	{
		float ar, pr;
		number_of_planets = Math::RandIntMinMax(1, 3);
		planet_type = 0;

		//orbit line increases by scale by (3 + (3 * 2) * i)
		//planet translation by (3 + (3 * 2) * i)

		for (int i = 1; i <= number_of_planets; i++)
		{
			ar = Math::RandFloatMinMax(-4.f, 6.f);
			pr = Math::RandFloatMinMax(-2.f, 6.f);

			planet_type = Math::RandIntMinMax(1, 3);

			if (planet_type == 1) //GreenPlanet
			{
				GreenPlanet* gPlanet = new GreenPlanet(myscene, Vector3(6 * i, 0, 0), 1, 1, ar, pr);
				planet_storage.push_back(gPlanet);
				this->objfactory->createSystemObject(gPlanet);
			}
			else if (planet_type == 2) //DesertPlanet
			{
				DesertPlanet* dPlanet = new DesertPlanet(myscene, Vector3(6 * i, 0, 0), 1, 1, ar, pr);
				planet_storage.push_back(dPlanet);
				this->objfactory->createSystemObject(dPlanet);
			}
			else if (planet_type == 3) //BluePLanet
			{
				BluePlanet* bPlanet = new BluePlanet(myscene, Vector3(6 * i, 0, 0), 1, 1, ar, pr);
				planet_storage.push_back(bPlanet);
				this->objfactory->createSystemObject(bPlanet);
			}
		}
	}
}

void SolarGenerate::save_init()
{
	this->SolarSystemID = GalaxyGenerate::get_instance()->galaxy_id_getter();	//set the id of system
	GalaxyGenerate::get_instance()->system_database[SolarSystemID] = this;		//set this system into the database
}

void SolarGenerate::build_system(float aRotate,float pRotate)
{
	this->SolarSystemID = GalaxyGenerate::get_instance()->galaxy_id_getter();											//back_up
	GalaxyGenerate::get_instance()->system_database[SolarSystemID]->objfactory->renderSystemObjects(aRotate, pRotate);	//generate that id of the system
}

int SolarGenerate::num_of_planet_getter()
{
	return number_of_planets;
}

vector<ObjectRender*> SolarGenerate::planet_storage_getter()
{
	return planet_storage;
}

//int SolarGenerate::planetID_getter()
//{
//	return planetID;
//}

int SolarGenerate::solar_system_ID_getter()
{
	return SolarSystemID;
}