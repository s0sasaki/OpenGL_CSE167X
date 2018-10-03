// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
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
//mat4 Transform::lookAt(vec3 eye, vec3 up) {
mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float theta = fovy/2.0f;
  float d = 1.0f / tan(theta);
  float A = - (zFar + zNear)/ (zFar - zNear);
  float B = - 2.0f * zFar * zNear / (zFar - zNear);
  mat4 p(d/aspect,    0.0f, 0.0f,  0.0f,
            0.0f,        d, 0.0f,  0.0f,
            0.0f,     0.0f,    A, -1.0f,
            0.0f,     0.0f,    B,  0.0f);
  return p;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  //mat4 ret;
  //// YOUR CODE FOR HW2 HERE
  //// Implement scaling
  //return ret;

  mat4 s(   sx, 0.0f, 0.0f, 0.0f,
          0.0f,   sy, 0.0f, 0.0f,
          0.0f, 0.0f,   sz, 0.0f,
          0.0f, 0.0f, 0.0f, 1.0f);
  return s;

}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  //mat4 ret;
  //// YOUR CODE FOR HW2 HERE
  //// Implement translation
  //return ret;

  mat4 t( 1.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 1.0f, 0.0f,
            tx,   ty,   tz, 1.0f);
  return t;

}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
