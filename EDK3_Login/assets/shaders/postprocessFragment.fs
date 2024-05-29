
#version 330
uniform sampler2D u_texture;
uniform int u_use_texture;
uniform vec4 u_color;
out vec4 fragColor;
in vec2 uv;
void main() {
    float pixel_size = 0.008; 
    vec2 pixel_coord = (uv / pixel_size);
    vec2 pixelated_uv = (floor(pixel_coord) + 0.5) * pixel_size;
    fragColor = texture(u_texture,pixelated_uv);


    // float pixel_size = 0.008; 
    // vec2 pixel_coord = (uv / pixel_size);
    // vec2 pixelated_uv = (floor(pixel_coord) + 0.5) * pixel_size;
    // fragColor = texture(u_texture, pixelated_uv);
}