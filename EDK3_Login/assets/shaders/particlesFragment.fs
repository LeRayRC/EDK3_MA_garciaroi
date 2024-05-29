#version 330

uniform sampler2D u_texture_1;
uniform int u_show_normal;

out vec4 FragColor;
in vec2 uv;
in vec3 normal;

vec3 final_color = vec3(0.0, 0.0, 0.0);

void main(){
    
    if(1 == u_show_normal){
      FragColor = vec4(normal, 1.0);
    }else{
        FragColor = texture(u_texture_1,uv);
      }
}