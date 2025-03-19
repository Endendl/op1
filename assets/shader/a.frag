#version 330 core//shader
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
struct Material {//材质
    sampler2D texture_diffuse[1];//材质贴图
    vec3 ambient;//表面反射颜色
    vec3 diffuse;//漫反射颜色
    vec3 specular;
    sampler2D texture_specular[1];//镜面高光颜色
    float shininess;//反光度
}; 
struct Light {
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct LightDirectional{
    vec3 position;
    vec3 color;
    vec3 dirToLight;
};

struct LightPoit{
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};
struct LightSpot{
    vec3 position;
    vec3 color;
    vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
    float CosPhyInner;
    float CosPhyOutter;
};


uniform LightDirectional lightD[5];
uniform LightPoit lightP[100];
uniform LightSpot lightS[100];
uniform int LightDirectionalNumber;
uniform int LightPoitNumber;
uniform int LightSpotNumber;
uniform Material material;//材质
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 

vec3 CalcLightDirectional(LightDirectional l1ght, vec3 uNormal, vec3 viewDir){
    vec3 lightDir = normalize(l1ght.dirToLight);
    // diffuse shading
    float diff = max(dot(uNormal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, uNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
   
    vec3 diffuse = l1ght.color * diff * vec3(texture(material.texture_diffuse[0], TexCoords));
    vec3 specular = l1ght.color * spec * vec3(texture(material.texture_specular[0], TexCoords));
    //return  diffuse + specular;
    //return  vec3(0,0,1.0f);

    //float diff = max(dot(l1ght.dirToLight, uNormal), 0.0);
    //vec3 diffuse  = l1ght.color * diff * vec3(texture(material.texture_diffuse[0], TexCoords));
    //
    //vec3 R = normalize(reflect(-l1ght.dirToLight, uNormal));
    //float spec = pow(max(dot(R , viewDir), 0.0), material.shininess);
    //vec3 specular = l1ght.color * spec * vec3(texture(material.texture_specular[0], TexCoords));;//计算镜面分量
    //
    ////vec3 result = vec3 (1, 1, 1);
    vec3 result =  diffuse + specular;
    return result;

}

vec3 CalcLightPoint(LightPoit l1ght, vec3 uNormal, vec3 viewDir){

    vec3 lightDir = normalize(l1ght.position - FragPos);//光照向片段的向量//
    float dist = length(l1ght.position - FragPos);
    float attenuation = 1 / (l1ght.constant + l1ght.linear * dist + l1ght.quadratic * (dist * dist));
    
    vec3 reflectDir = reflect(-lightDir, uNormal);
    
    float diff = max(dot(uNormal, lightDir), 0.0);
    vec3 diffuse  = l1ght.color * diff * vec3(texture(material.texture_diffuse[0], TexCoords));
    //vec3 diffuse  = light.color * diff * vec3(texture(material.texdiffuse, TexCoords));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = l1ght.color * spec * vec3(texture(material.texture_specular[0], TexCoords));;//计算镜面分量
    //vec3 result = vec3 (1, 1, 1);
    vec3 result = (diffuse + specular) * attenuation;
    return result;
}

vec3 CalcLightSpot(LightSpot l1ght, vec3 uNormal, vec3 viewDir){

    vec3 lightDir = normalize(l1ght.position - FragPos);//光照向片段的向量//
    float dist = length(l1ght.position - FragPos);
    float attenuation = 1 / (l1ght.constant + l1ght.linear * dist + l1ght.quadratic * (dist * dist));//衰减
    
    vec3 reflectDir = reflect(-lightDir, uNormal);
    
    float diff = max(dot(uNormal, lightDir), 0.0);//漫反射
    vec3 diffuse  = l1ght.color * diff * vec3(texture(material.texture_diffuse[0], TexCoords));
    //vec3 diffuse  = light.color * diff * vec3(texture(material.texdiffuse, TexCoords));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = l1ght.color * spec * vec3(texture(material.texture_specular[0], TexCoords));;//镜面光分量

    float CosTheta = dot(normalize(FragPos - l1ght.position), -l1ght.dirToLight);
    float spotRatio = 0.0f;

    if(CosTheta > l1ght.CosPhyInner)//内
    {
        spotRatio = 1.0f;
        
    }else if(CosTheta >l1ght.CosPhyOutter){//中
        spotRatio = 1.0f - (CosTheta - l1ght.CosPhyOutter) / (l1ght.CosPhyInner - l1ght.CosPhyOutter);
    }else{//外
        spotRatio = 0;
    }
    //vec3 result = vec3 (1, 1, 1);
    vec3  result = ((diffuse + specular) * attenuation * spotRatio);
    return result;
}

vec3 sumDirectional(vec3 uNormal, vec3 viewDir){
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < LightDirectionalNumber; i++){
        result += CalcLightDirectional(lightD[i], uNormal, viewDir);
    }
    return result;
}
vec3 sumPoint(vec3 uNormal, vec3 viewDir){
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < LightPoitNumber; i++){
        result += CalcLightPoint(lightP[i], uNormal, viewDir);
    }
    return result;
}
vec3 sumSpot(vec3 uNormal, vec3 viewDir){
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < LightSpotNumber; i++){
        result += CalcLightSpot(lightS[i], uNormal, viewDir);
    }
    return result;
}

void main()
{
    vec3 uNormal = normalize(Normal);//法向单位向量化//
    vec3 viewDir = normalize(viewPos - FragPos);//视角到点的向量
    vec3 finalResult = vec3(0.0f, 0.0f, 0.0f);
    if(LightDirectionalNumber > 0)
        finalResult += sumDirectional(uNormal, viewDir);
    if(LightPoitNumber > 0)
        finalResult += sumPoint(uNormal, viewDir);
    //if(LightSpotNumber > 0)
        //finalResult += sumSpot(uNormal, viewDir);
    //finalResult += CalcLightSpot(lightS[0], uNormal, viewDir);

    FragColor = vec4(finalResult, 1.0);

}
