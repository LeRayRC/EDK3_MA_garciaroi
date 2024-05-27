#version 330
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;
layout(location = 3) in float a_height;
out vec2 uv;
out vec3 normal;
out vec3 position;
out float height;
vec3 transform_position;

void main() {
    transform_position = a_position;
    transform_position.y = sin((transform_position.x + transform_position.z) * 10.0 + u_time) * 10.0 * abs(cos(u_time));
    transform_position.y *= sin((transform_position.x - transform_position.z) * 20.0 + u_time) * 1.5 * clamp(cos(u_time), 0.5,1.0);
    //transform_position.y = sin((transform_position.x + transform_position.z) * 30.0 + u_time) * ;
    //transform_position.y += 10.0*clamp((sin((transform_position.x) * PI * 2.0),0.0,1.0));
    gl_Position = u_vp_matrix * u_m_matrix * vec4(transform_position, 1.0);
    uv = a_uv;
    normal = (u_m_matrix * vec4(a_normal,0.0)).xyz;
    position = (u_m_matrix * vec4(transform_position,1.0)).xyz;
    height = a_height;
    // normal = a_normal;
}