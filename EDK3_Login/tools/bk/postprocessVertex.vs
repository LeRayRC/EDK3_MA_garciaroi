#version 330
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;
layout(location = 3) in float a_height;
out vec2 uv;
out vec2 coord;
void main() {
    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
    uv = a_uv;
    coord = gl_Position.xy;
}
