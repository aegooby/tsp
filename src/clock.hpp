
#pragma	once
#include	"__common.hpp"

__begin_ns_tsp

using t_point = std::chrono::high_resolution_clock::time_point;
using nanosec = std::chrono::nanoseconds;

template	<typename duration_type>
inline __attribute__((always_inline))
nanosec	nano_cast(duration_type duration)
{
	return std::chrono::duration_cast<nanosec>(duration);
}

static constexpr float	nsps = 1000000000.0f;
static constexpr float	nspms = 1000000.0f;

class	clock
{
protected:
	static t_point	start;
	static t_point	now();
public:
	clock() = default;
	~clock() = default;
	void	reset();
	float	time_s();
	float	time_ms();
	std::string	date_time() const;
	
	//	Preventing copying and moving
	clock(const clock&) = delete;
	clock(const clock&&) = delete;
	clock&	operator =(const clock&) = delete;
	clock&	operator =(const clock&&) = delete;
};

__end_ns_tsp
