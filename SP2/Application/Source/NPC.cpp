#include "NPC.h"

NPC::NPC(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_NPC;
}
void NPC::interact()
{

}