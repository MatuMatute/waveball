shader_type canvas_item;

uniform sampler2D screenTexture : hint_screen_texture, filter_linear_mipmap;

void fragment() {
	vec4 colorToInvert = texture(screenTexture, SCREEN_UV);
	COLOR.rgb = 1.0 - colorToInvert.rgb;
}