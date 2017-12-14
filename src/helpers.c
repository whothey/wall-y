#ifndef HELPERS_FUNCS

#define HELPERS_FUNCS

#include <iostream>
#include <cmath>

#define DUMP_COORDS_3v(prefix, v) (std::cout << prefix <<  ": (" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl)

#define VEC(v, v1, v2) \
    (v)[0] = (v1)[0] - (v2)[0]; \
    (v)[1] = (v1)[1] - (v2)[1]; \
    (v)[2] = (v1)[2] - (v2)[2];

#define CROSS(v, a, b) \
	(v)[0] = (a)[1] * (b)[2] - (b)[1] * (a)[2]; \
	(v)[1] = (a)[2] * (b)[0] - (b)[2] * (a)[0]; \
	(v)[2] = (a)[0] * (b)[1] - (b)[0] * (a)[1];

#define NORM(v) \
    sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2))

#define NORMALIZE(v) \
    v[0] = v[0] / NORM(v); \
    v[1] = v[1] / NORM(v); \
    v[2] = v[2] / NORM(v);

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180)

#define VECTORIZE(v, x, y, z) \
    v[0] = x; \
    v[1] = y; \
    v[2] = z;

#endif
