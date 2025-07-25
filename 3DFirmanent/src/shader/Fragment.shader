#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float shininess;
};

struct DirLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

};


#define MAX_POINT_LIGHT 1
#define MAX_DIR_LIGHT 1
#define MAX_SPOT_LIGHT 1

uniform PointLight pointLights[MAX_POINT_LIGHT];
uniform DirLight dirLights[MAX_DIR_LIGHT];
uniform SpotLight spotLights[MAX_SPOT_LIGHT];
uniform vec3 viewPos;

vec3 getDiffuseColor() {
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    if (texColor.a > 0.0) { return vec3(texColor); }

    texColor = texture(texture_diffuse2, TexCoords);
    if (texColor.a > 0.0) return vec3(texColor);


    return vec3(1.0);
}

vec3 getSpecularColor() {
    vec4 texColor = texture(texture_specular1, TexCoords);
    if (texColor.a > 0.0) return vec3(texColor);

    texColor = texture(texture_specular2, TexCoords);
    if (texColor.a > 0.0) return vec3(texColor);

    return vec3(1.0);
}




//lighting(includes attenuation as well as soft edges)
vec3 CalculatePointLight(PointLight light,vec3 normal,vec3 fragPos) {
    vec3 ambient;
    ambient = light.ambient * getDiffuseColor();

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse*diff * getDiffuseColor();

    vec3 reflectDir = reflect(lightDir,normal);
    float spec = pow((max(dot(reflectDir, lightDir), 0.0)), light.shininess);
    vec3 specular = light.specular*spec * getSpecularColor();

    //attenaution
    float distance = length(lightDir);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return(ambient + diffuse + specular);
}


vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir) {

    vec3 ambient;
    ambient = light.ambient * getDiffuseColor();

    vec3 lightDir = normalize(light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse*diff * getDiffuseColor();

    vec3 reflectDir = reflect(lightDir,normal);
    float spec = pow((max(dot(reflectDir, viewDir), 0.0)), light.shininess);
    vec3 specular = light.specular*spec * getSpecularColor();

    

    return(ambient + diffuse + specular);
}

vec3 CalculateSpotlight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir) {

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    vec3 color;
    if (theta > light.cutOff) {
        vec3 ambient;
        ambient = light.ambient * getDiffuseColor();

        vec3 lightDir = normalize(light.direction);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * getDiffuseColor();

        vec3 reflectDir = reflect(lightDir,normal);
        float spec = pow((max(dot(reflectDir, viewDir), 0.0)), light.shininess);
        vec3 specular = spec * getSpecularColor();

        

        //softer edges
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;
        color = vec3(ambient + diffuse + specular);
    }
    else {
        color = light.ambient * getDiffuseColor();
    }

    return color;
}

void main()
{
    vec3 result;
    vec3 norm= normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    for (int i = 0; i < MAX_POINT_LIGHT; i++) {
        result += CalculatePointLight(pointLights[i],norm,FragPos);
    }

    for (int i = 0; i < MAX_DIR_LIGHT; i++) {
        result += CalculateDirLight(dirLights[i],norm,viewDir);
    }
    result += CalculateSpotlight(spotLights[0],norm,FragPos,viewDir);
    FragColor = vec4(result,1.0);
    
     
}