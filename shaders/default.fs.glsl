varying vec2 fUV;
void main()
{
	float border_1 = 0.06;
	float border_2 = 0.03;
	float border_3 = 0.03;

	float circle_radius = 0.3;
	vec4 circle_color = vec4(0.0, 2.0, 0.0, 1.0);
	vec2 circle_center = vec2(0.5, 0.5);

	vec2 uv = fUV;
	uv -= circle_center;
	uv.x /= 0.75;

	float dist =  sqrt(dot(uv, uv));

	float t1 = 1.0 + smoothstep(circle_radius, circle_radius+border_1, dist)
                - smoothstep(circle_radius-border_1, circle_radius, dist);

	float t2 = 1.0 + smoothstep(circle_radius, circle_radius+border_2, dist) 
                - smoothstep(circle_radius-border_2, circle_radius, dist);

    float t3 = 1.0 + smoothstep(circle_radius, circle_radius+border_3, dist) 
                - smoothstep(circle_radius-border_3, circle_radius, dist);

    vec4 step = vec4(0.0, 0.3, 0.3, 1.0);
	

    vec4 bg_color = vec4(0.0);
    bg_color = mix(circle_color+step, bg_color, t1);
    bg_color = mix(vec4(1.0), bg_color, t2);


    gl_FragColor = mix(circle_color, bg_color, t3);
    gl_FragColor = bg_color;
}