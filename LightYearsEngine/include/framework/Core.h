#include <stdio.h>

namespace ly
{
	//macro
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}