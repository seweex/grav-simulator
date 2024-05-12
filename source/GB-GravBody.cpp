#include "GravBody.h"

/*
	GravBody:

	Класс для описания тела, для которого будут применены
	физические взаимодействия
*/

GravBody::GravBody()
	: GravBody{ vec2(0., 0.), 1., vec2(0., 0.) } {}
GravBody::GravBody(
	vec2		pos, 
	sfloat_t	mass,
	vec2		vel = vec2(0., 0.))
	: 
	m_position {pos},
	m_acceleration {vel},
	m_mass	   {mass} {}

vec2		GravBody::get_position() const
{
	return m_position;
}
vec2		GravBody::get_acceleration() const
{
	return m_acceleration;
}
sfloat_t	GravBody::get_mass() const
{
	return m_mass;
}

void GravBody::apply_force(Force force)
{
	// force = acceler * mass, so: acceler = force / mass: 
	m_acceleration += (force.get_direction() * force.get_scalar()) / m_mass;
}

void GravBody::apply_time(sfloat_t time_s)
{
	m_position += m_acceleration * (time_s * time_s);
}