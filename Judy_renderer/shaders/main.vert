#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float transform;
out vec3 ourColor;


vec3 var = aPos;

	void main()
	{
		var = aPos*transform;
		gl_Position = vec4(var.x, var.y, var.z, 1.0);
		ourColor = aColor;
	}	