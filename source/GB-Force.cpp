#include "GravSim.h"

/*
	Force:
	
	Класс для описания силы применяемой для объектов 
*/

Force::Force()
	: Force{ vec2(0., 0.), 0. } {}
Force::Force(vec2 direction, sfloat_t force)
	:
	m_scalar{ force }
{
	sfloat_t dir_length = (sfloat_t)sqrtl(direction.x * direction.x + direction.y * direction.y);
	if (dir_length == .0)
		m_direction = vec2(.0, .0);
	else
		m_direction = direction / dir_length;
}

vec2 Force::get_direction() const
{
	return m_direction;
}
sfloat_t Force::get_scalar() const
{
	return m_scalar;
}