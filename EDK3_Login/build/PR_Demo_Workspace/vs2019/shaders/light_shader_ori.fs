#version 330

struct Light{
    int enabled;
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
    vec3 spot_dir;
    float cutoff;
    float outer_cutoff;
};

const int kMaxLights = 8;
uniform int u_number_lights;
uniform vec3 u_ambient;
uniform Light u_lights[kMaxLights];
uniform sampler2D u_texture;
uniform int u_use_texture;

out vec4 FragColor;
in vec2 uv;
in vec3 normal;
in vec3 position;

vec3 final_color = vec3(0.0, 0.0, 0.0);


vec3 DirectionalLight(Light conf){
  vec3 normal_norm = normalize(normal);
  float directionalIncidence = max(dot(normal_norm, conf.dir), 0.0);
  //Specular
  vec3 viewDirection = normalize(conf.camera_pos - position);
  vec3 reflectDirection = reflect(-conf.dir, normal_norm);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.shininess);

  vec3 diffuse = directionalIncidence * conf.diff_color;
  vec3 specular = conf.strength * specularValue * conf.spec_color;
  return diffuse + specular;
  //return diffuse;
}

vec3 PointLight(Light conf){
  conf.dir = normalize(conf.pos - position);
  float directionalIncidence = max(dot(normal, conf.dir), 0.0);
  //Specular
  vec3 viewDirection = normalize(conf.camera_pos - position);
  vec3 reflectDirection = reflect(-conf.dir, normal);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.shininess);

  vec3 diffuse = directionalIncidence * conf.diff_color;
  vec3 specular = conf.strength * specularValue * conf.spec_color;
  //Attenuation
  float distance = length(conf.pos - position);
  float attenuation = 1.0 / (conf.constant_att + conf.linear_att * distance + conf.quad_att * distance * distance);
  return diffuse * attenuation + specular * attenuation;
}

vec3 SpotLight(Light conf){
  conf.dir = normalize(conf.pos - position);
  float theta = dot(conf.dir,normalize(-conf.spot_dir));
  vec3 result = vec3(0.0,0.0,0.0);
    float directionalIncidence = max(dot(normal, conf.dir), 0.0);
    //Specular
    vec3 viewDirection = normalize(conf.camera_pos - position);
    vec3 reflectDirection = reflect(-conf.dir, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.shininess);

    vec3 diffuse = directionalIncidence * conf.diff_color;
    vec3 specular = conf.strength * specularValue * conf.spec_color;
    //Attenuation
    float distance = length(conf.pos - position);
    float attenuation = 1.0 / (conf.constant_att + conf.linear_att * distance + conf.quad_att * distance * distance);
    
    //Intensity
    float epsilon   = conf.cutoff - conf.outer_cutoff;
    float intensity = clamp((theta - conf.outer_cutoff) / epsilon, 0.0, 1.0);   
    
    result = (diffuse * intensity  * attenuation) + (specular * intensity * attenuation);
  return result;
}

void main(){
    


    final_color += u_ambient;
    for(int i=0; i<kMaxLights;i++){
        if( u_lights[i].enabled != 0){
            switch(u_lights[i].type){
                case 0: {
                    final_color += DirectionalLight(u_lights[i]);
                    break;
                }
                case 1: {
                    final_color += PointLight(u_lights[i]);
                    break;
                }
                case 2: {
                    final_color += SpotLight(u_lights[i]);
                    break;
                }

            }
        }
    }
    FragColor = vec4(final_color, 1.0);
    if(1 == u_use_texture){
      FragColor *= texture(u_texture,uv);
    }
}