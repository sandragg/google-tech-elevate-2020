#include "route.h"


namespace graph
{

bool Route::operator<(const Route& rhs) const
{
	if (price != rhs.price)
		return price < rhs.price;

	if (airports.size() != rhs.airports.size())
		return airports.size() < rhs.airports.size();

	return airports < rhs.airports;
}

} // namespace graph
