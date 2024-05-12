#include "GravSim.h"

/*
	Scene:

	Класс для хранения физических тел и обработки
	взаимодействия между ними
*/

const long double GRAV_CONSTANT = 6.67430e-11L;

Scene::Scene()
	: m_objects{} {}
Scene::Scene(const vector<GravBody>& right)
	: m_objects{ right } {}

size_t Scene::objects_count() const
{
	return m_objects.size();
}
const GravBody& Scene::object_at(size_t index) const
{
	return m_objects.at(index);
}
GravBody& Scene::object_at(size_t index)
{
	return m_objects.at(index);
}

void Scene::add_object(GravBody newObject)
{
	m_objects.push_back(newObject);
}

void Scene::physics_tick()
{
	for(auto& me : m_objects)
		for (auto& other : m_objects)
		{
			vec2 my_pos		= me.get_position();
			vec2 others_pos = other.get_position();
			vec2 pos_diff	= others_pos - my_pos;
			if (pos_diff == vec2(.0, .0)) continue;

			sfloat_t distance = (sfloat_t)sqrtl(pos_diff.x * pos_diff.x + pos_diff.y * pos_diff.y);

			sfloat_t my_mass		= me.get_mass();
			sfloat_t others_mass	= other.get_mass();

			Force force(pos_diff, GRAV_CONSTANT * (my_mass * others_mass) / (distance * distance));
			me.apply_force(force);
		}
}
void Scene::apply_time(sfloat_t time_s)
{
	for (auto& me : m_objects)
		me.apply_time(time_s);
}

void Scene::apply_force_to_all(Force force)
{
	for (auto& me : m_objects)
		me.apply_force(force);
}
void Scene::apply_force(Force force, size_t object_i)
{
	m_objects[object_i].apply_force(force);
}