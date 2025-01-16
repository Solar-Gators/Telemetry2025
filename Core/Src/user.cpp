#include "user.hpp"
#include "notecard.hpp"

// Main C++ loop
void user_loop_cpp()
{
	Notecard notecard(&huart2);

	while(1) {

	}
}

extern "C"
{
    void user_loop_c()
    {
        user_loop_cpp();
    }
}
