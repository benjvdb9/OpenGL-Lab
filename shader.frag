#version 430
out vec3 Fragment;
in vec3 fPos;
in vec2 fTex;
in vec3 fNorm;
in vec3 fLightPosition;
uniform sampler2D Tex;
void main()
{
    vec3 lightDir;
    vec3 normal;
    vec3 diffuse;

    lightDir = normalize(fLightPosition - fPos);
    normal = normalize(fNorm);
    diffuse = vec3(texture(Tex, fTex));

    Fragment = diffuse * max(dot(normal, lightDir), 0.4);
}