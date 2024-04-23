#version 330

out vec4 FragColor;
in vec2 uv;
in vec3 normal;

struct Light{
    int type;
    vec3 pos;
    vec3 dir;
    vec3 diff_color;
    vec3 spec_color;
    vec3 camera_pos;
    float linear_att;
    float quad_att;
    float constant_att;
    float shininess;
    float strength;
};

const int kMaxLights = 8;
uniform int u_number_lights;
uniform vec3 u_ambient;
//uniform sampler2D u_texture;
uniform Light u_lights[kMaxLights];
//uniform vec3 u_camera_pos;

vec3 DirectionaLight(){

    return vec3(0.0, 0.0, 0.0);
}

vec3 SpotLight(){


    return vec3(0.0, 0.0, 0.0);
}

vec3 PointLight(){

    return vec3(0.0, 0.0, 0.0);
}

void main(){
    vec3 final_color = vec3(0.0, 0.0, 0.0);

    for(int i=0; i<kMaxLights;i++){
        if( i < u_number_lights){
            switch(u_lights[i].type){
                case 0: {
                    final_color = DirectionaLight();
                    break;
                }
                case 1: {
                    final_color = SpotLight();
                    break;
                }
                case 2: {
                    final_color = PointLight();
                    break;
                }

            }
        }
    }
    final_color += u_ambient;
    //final_color += normal;
    //FragColor = vec4(final_color, 1.0) * texture(u_texture,uv );

    FragColor = vec4(final_color, 1.0);
}