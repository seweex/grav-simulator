#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

using sfloat_t = long double;	// simulation float type
typedef Vector2<sfloat_t> vec2;

/* Класс для описания силы применяемой для объектов */
class Force
{
	vec2		m_direction;
	sfloat_t	m_scalar;

public:

	Force();
	Force(vec2 direction, sfloat_t force);

	vec2		get_direction() const;
	sfloat_t	get_scalar() const;
};

/* 
	Класс для описания тела, для которого будут применены
	физические взаимодействия
*/
class GravBody
{
	vec2		m_position;
	vec2		m_acceleration;
	sfloat_t	m_mass;

public:

	GravBody();
	GravBody(vec2 pos, sfloat_t mass, vec2 vel);

	vec2		get_position() const;
	vec2		get_acceleration() const;
	sfloat_t	get_mass() const;

	void		apply_force(Force force);

	void		apply_time(sfloat_t time_ms);
};

/* 
	Класс для хранения физических тел и обработки
	взаимодействия между ними 
*/
class Scene
{
	vector<GravBody> m_objects;

public:

	Scene();
	Scene(const vector<GravBody>& right);

	size_t			objects_count() const;
	const GravBody& object_at(size_t index) const;
	GravBody&		object_at(size_t index);

	void	add_object(GravBody newObject);
	
	void	physics_tick();
	void	apply_time(sfloat_t time_ms);

	void	apply_force_to_all(Force force);
	void	apply_force(Force force, size_t object_i);
};

// Time for one tick in seconds.
const sfloat_t DELTA_TIME = 3600.00;		// one hour in one tick

const GravBody EARTH
(
	vec2(150'597'870'700.L, 0),		// location in world in meters
	5.9722e24L,						// mass in kg
	vec2(0, 29'000 / DELTA_TIME)	// start acceleration in m/s^2 or (m/s) / DELTA_TIME
);
const GravBody SUN
(
	vec2(0., 0),		// location
	1.9885e30L,			// mass
	vec2(0., 0.)		// acceleration
);
const GravBody MOON
(
	vec2(EARTH.get_position().x + 380'000'000, 0),
	7.35e22,
	vec2(0., EARTH.get_acceleration().y + 1'000. / DELTA_TIME)
);