
#include	"clock.hpp"

__begin_ns_tsp

t_point	clock::start = std::chrono::high_resolution_clock::now();

t_point	clock::now()
{
	return	std::chrono::high_resolution_clock::now();
}

void	clock::reset()
{
	start = std::chrono::high_resolution_clock::now();
}
float	clock::time_s()
{
	return	nano_cast(now() - start).count() / nsps;
}
float	clock::time_ms()
{
	return	nano_cast(now() - start).count() / nspms;
}
std::string	clock::date_time() const
{
	std::time_t	time = std::time(0);
	std::tm*	date = std::localtime(&time);
	return (std::to_string(date->tm_mday) + "/" + std::to_string(date->tm_mon + 1) + "/" + std::to_string(date->tm_year + 1900) + ", " + std::to_string(date->tm_hour) + ":" + std::to_string(date->tm_min) + ":" + std::to_string(date->tm_sec) + " UTC");
}

__end_ns_tsp
