#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <iostream>
#include <chrono>
#include <map>

using namespace std::chrono;

float logBase2(const float number)
{
	float res = (float)(*(int*)&number) * 0.00000011920928955078125 + 0.043 - 127;
	for (int i = 0; i < 0; i++)
		res = res + 1 - pow(2, res) / number;
	return res;
}

float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	return y;
}

int main()
{
	std::map<int, int> mapa;
	//mapa[1]++;
	std::cout << mapa[1] << std::endl;

	srand(time(NULL));
	float res = (rand() % 10 + 1) / 10.f;
	std::cout << logBase2(0.001) << std::endl;
	{
		float res2 = 0;
		auto start = high_resolution_clock::now();

		for (long i = 0; i < 20000; i++)
			res2=logBase2(res+i);

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);

		std::cout << duration.count() << " : " << res2 << " : " << res << std::endl;
	}

	{
		float res2 = 0;
		auto start = high_resolution_clock::now();

		for (long i = 0; i < 20000; i++)
			res2=log2(res+i);

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);

		std::cout << duration.count() << " : " << res2 << " : " << res << std::endl;
	}
	return 0;
}