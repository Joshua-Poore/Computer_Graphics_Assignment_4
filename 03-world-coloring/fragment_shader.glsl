#version 430 core

out vec4 fColor;

in vec4 s_color;
in vec4 position;

void main()
{
    if(position.x < 0)
        fColor.r = .25;
    else
        fColor.r = 1.0;
    if(position.y < 0)
        fColor.g = .25;
    else
        fColor.g = 1.0;
    if(position.z < 0)
        fColor.b = .25;
    else
        fColor.b = 1.0;
    fColor.a = 1.0;
    fColor = fColor * s_color;
//    fColor = vec4(0,1,0,1);
}
