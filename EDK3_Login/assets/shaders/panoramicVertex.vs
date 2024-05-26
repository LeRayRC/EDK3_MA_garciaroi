#version 330
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;
//out vec2 uv;
//out vec3 normal;
out vec3 pos;

void main() {
    gl_Position = (u_vp_matrix * vec4(a_position, 0.0)).xyww;
    //uv = a_uv;
    //normal = (u_m_matrix * vec4(a_normal,0.0)).xyz;
    pos = a_position;
}