#version 330 core//นโิด
out vec4 FragColor;

uniform vec3 lightcolor;
void main()
{
    FragColor = vec4(lightcolor, 1.0); // set all 4 vector values to 1.0
}