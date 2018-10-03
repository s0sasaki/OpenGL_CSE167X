// Transform.cpp: implementation of the Transform class.

//#include <stdio.h>
#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float radians = degrees * pi /180.0f;
	mat3 m1(1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f);
	mat3 m2(x*x, x*y, x*z,  y*x, y*y, y*z,  z*x, z*y, z*z);
	mat3 m3(0.0f, z, -y,  -z, 0.0f, x,  y, -x, 0.0f);
	return cos(radians)*m1 + (1.0f-cos(radians))*m2 + sin(radians)*m3;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = rotate(degrees, up) * eye;
	//printf("Left Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 eye_prev = eye;
	vec3 up_prev = up;
	eye = rotate(degrees, normalize(cross(eye_prev, up_prev))) * eye_prev;
	up = rotate(degrees, normalize(cross(eye_prev, up_prev))) * up_prev;
	//printf("Up   Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 a = eye - vec3(0.0f);
	vec3 b = up;
	vec3 u, v, w;
	w = normalize(a);
	u = normalize(cross(b, w));
	v = cross(w, u);
	mat4 r(u.x, v.x, w.x, 0.0f,  u.y, v.y, w.y, 0.0f,  u.z, v.z, w.z, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f);
	mat4 t(1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  -eye.x, -eye.y, -eye.z, 1.0f);
	return r * t;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
