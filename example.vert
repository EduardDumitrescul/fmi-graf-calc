// Shader-ul de varfuri / Vertex shader
#version 330 core

layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec4 in_Color;

// Urmatoarea linie trebuie decomentata pentru ca programul sa functioneze pe unele placi grafice
// out vec4 gl_Position; 
out vec4 ex_Color;

void main ()
{
   gl_Position = in_Position;
   ex_Color = in_Color;
}