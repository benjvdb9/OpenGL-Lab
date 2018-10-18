#version 430
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
in vec3 vPos;
in vec2 vTex;
in vec3 vNorm;
out vec3 fPos;
out vec2 fTex;
out vec3 fNorm;
out vec3 fLightPosition;

void main()
{
    vec3 LightPosition = vec3(0, 0, 0.1);
    mat3 normalMatrix;
    vec4 cPos;

    fTex = vTex;
    
    normalMatrix = transpose(inverse(mat3(View*Model)));
    fNorm = normalize(normalMatrix * vNorm);

    fLightPosition = vec3(View * vec4(LightPosition, 1.0));

    cPos = View * Model * vec4(vPos, 1.0);
    fPos = vec3(cPos);

    gl_Position = Projection * cPos;
}