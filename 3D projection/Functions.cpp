#include "Functions.h"

void MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m)
{
	o.x = i.x * m.mat[0][0] + i.y * m.mat[1][0] + i.z * m.mat[2][0] + m.mat[3][0];
	o.y = i.x * m.mat[0][1] + i.y * m.mat[1][1] + i.z * m.mat[2][1] + m.mat[3][1];
	o.z = i.x * m.mat[0][2] + i.y * m.mat[1][2] + i.z * m.mat[2][2] + m.mat[3][2];
	float w = i.x * m.mat[0][3] + i.y * m.mat[1][3] + i.z * m.mat[2][3] + m.mat[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

vec3d crossProduct(triangle t)
{
	vec3d normal, line1, line2;

	line1.x = t.p[1].x - t.p[0].x;
	line1.y = t.p[1].y - t.p[0].y;
	line1.z = t.p[1].z - t.p[0].z;

	line2.x = t.p[2].x - t.p[0].x;
	line2.y = t.p[2].y - t.p[0].y;
	line2.z = t.p[2].z - t.p[0].z;

	normal.x = line1.y * line2.z - line1.z * line2.y;
	normal.y = line1.z * line2.x - line1.x * line2.z;
	normal.z = line1.x * line2.y - line1.y * line2.x;

	return normal;
}

vec3d normalize(vec3d v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= len;
	v.y /= len;
	v.z /= len;

	return v;
}

float dotProduct(vec3d v, vec3d o)
{
	return v.x * o.x + v.y * o.y + v.z * o.z;
}