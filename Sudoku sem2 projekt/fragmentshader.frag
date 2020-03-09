uniform sampler2D texture;
uniform vec2 mousePos;

void main()
{
	float dist = distance(mousePos, gl_FragCoord.xy);
	float mixAmount = clamp(50.0 / dist, 0.05, 0.3);
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor = pixel + vec4(0.2*mixAmount,0.2*mixAmount,-0.25*mixAmount,1.0);
}