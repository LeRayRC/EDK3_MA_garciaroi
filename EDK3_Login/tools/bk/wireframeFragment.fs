#version 330
uniform sampler2D u_texture;
uniform sampler2D u_albedo_1;
uniform sampler2D u_albedo_2;
uniform int u_use_texture;
uniform vec4 u_color;
out vec4 fragColor;
in vec2 uv;
in vec3 normal;
void main() {
   fragColor = vec4(0.0,0.0,0.0,1.0);
} 