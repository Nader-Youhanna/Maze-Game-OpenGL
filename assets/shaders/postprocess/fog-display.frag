#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

//iTime is a uniform variable that holds the time in seconds since the program started
uniform float iTime;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;
out vec4 frag_color;

//write main function that can simulate fog effect
//document the main function
void main()
{		
	vec2 uv = tex_coord;
	//resolution of the screen
	vec2 resolution = vec2(1280,720);
	//intensity of the fog effect
	float intensity = 0.5;
	//threshold of the fog effect
	float threshold = 0.5;
	//radius of the fog effect
	float radius = 1.0;
	//strength of the fog effect
	float strength = 0.5;

	//texel is the size of a pixel
	vec2 texel = vec2(1.0) / resolution;

	//coord is the position of the pixel
	vec2 coord = uv;

	//color is the color of the pixel
	vec4 color = vec4(0.0);

	//weight is the weight of the pixel
	float weight = 0.0;

	//loop through the pixels around the pixel
	for(int x = -30; x <= 30; x++)
	{
		
		for(int y = -30; y <= 30; y++)
		{
			//sample is the position of the pixel
			vec2 sample = vec2(x, y) * texel;
			//sampleColor is the color of the pixel
			vec4 sampleColor = texture(tex, coord + sample);
			//dist is the distance between the pixel and the center of the fog effect
			float dist = distance(vec2(0.0), sample);
			//add the weight of the pixel to the weight of the fog effect
			weight += (1.0 - smoothstep(0.0, 1.0, dist / radius)) * (1.0 - threshold) + threshold;
			//add the color of the pixel to the color of the fog effect
			color += sampleColor * (1.0 - smoothstep(0.0, 1.0, dist / radius)) * (1.0 - threshold) + threshold;
		}
	}

	//calculate the average color of the fog effect
	color /= weight;

	//calculate the final color of the fog effect
	//mix is a function that blends two colors together
	//blend the color of the fog effect with the color of the pixel
	color = mix(color, texture(tex, uv), intensity);

	color = mix(color, vec4(1.0) - exp(-color * strength), intensity);

	frag_color = color;
}