#version 330

out vec4 FragColor;
in vec2 uv;
in vec3 normal;
in vec3 position;

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


vec3 DirectionalLight(Light conf){
  float directionalIncidence = max(dot(normal, conf.dir), 0.0);
  //Specular
  vec3 viewDirection = normalize(conf.camera_pos - position);
  vec3 reflectDirection = reflect(-conf.dir, normal);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.shininess);

  vec3 diffuse = directionalIncidence * conf.diff_color;
  vec3 specular = conf.strength * specularValue * conf.spec_color;
  return diffuse + specular;
}

vec3 PointLight(LightConf conf){
    /*
  conf.lightDirection = normalize(conf.lightPosition - position.xyz);
  float directionalIncidence = max(dot(normal.xyz, conf.lightDirection), 0.0);
  //Specular
  vec3 viewDirection = normalize(u_camera_position - position.xyz);
  vec3 reflectDirection = reflect(-conf.lightDirection, normal.xyz);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.specularShininess);

  vec3 diffuse = directionalIncidence * conf.lightColor;
  vec3 specular = conf.specularStrength * specularValue * conf.lightColor;
  //Attenuation
  float distance = length(conf.lightPosition - position.xyz);
  float attenuation = 1.0 / (conf.attenuation.constant + conf.attenuation.linear * distance + conf.attenuation.quadratic * distance * distance);
  return diffuse * attenuation + specular * attenuation;
  */
  return vec3(0.0, 0.0, 0.0);
}

vec3 SpotLight(LightConf conf){
    /*
  conf.lightDirection = normalize(conf.lightPosition - position.xyz);
  float theta = dot(conf.lightDirection,normalize(-conf.spotDirection));
  vec3 result = vec3(0.0,0.0,0.0);
  // if(theta > conf.cutOff){
    // conf.lightDirection = normalize(conf.lightPosition - position.xyz);
    float directionalIncidence = max(dot(normal.xyz, conf.lightDirection), 0.0);
    //Specular
    vec3 viewDirection = normalize(u_camera_position - position.xyz);
    vec3 reflectDirection = reflect(-conf.lightDirection, normal.xyz);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.specularShininess);

    vec3 diffuse = directionalIncidence * conf.lightColor;
    vec3 specular = conf.specularStrength * specularValue * conf.lightColor;
    //Attenuation
    float distance = length(conf.lightPosition - position.xyz);
    float attenuation = 1.0 / (conf.attenuation.constant + conf.attenuation.linear * distance + conf.attenuation.quadratic * distance * distance);
    
    //Intensity
    // theta = dot(conf.lightDirection,normalize(-conf.spotDirection));
    float epsilon   = conf.cutOff - conf.outerCutOff;
    float intensity = clamp((theta - conf.outerCutOff) / epsilon, 0.0, 1.0);   
    
    result = (diffuse * intensity  * attenuation) + (specular * intensity * attenuation);
    // result = diffuse  + specular;
  // }

  return result;
  */
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