#include "fragment_shader.h"
#include "math/math_lib.h"

namespace softrd {

FragmentShader::FragmentShader() {
}

void FragmentShader::Program() {
	out_->color = vec4(1.0, 1.0, 1.0, 1.0);
}

void FragmentShader::Run(const Fragment &in, FragmentOut *out) {
	in_ = in;
	out_ = out;
	out->window_position = in.window_position;
	Program();
}

FragmentShaderFlatColor::FragmentShaderFlatColor(const vec3 &color) : flat_color(color) {
}

void FragmentShaderFlatColor::Program() {
	out_->color = vec4(flat_color, 1.0);

}

void FragmentShaderLight::Program() {
	// ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * light_color;

	// diffuse
	vec3 norm = in_.world_normal.normalize();
	vec3 light_dir = (light_position - in_.world_position).normalize();

	float diff = Max(norm * light_dir, 0.0);
	vec3 diffuse = diff * light_color;

	// specular
	float specular_strength = 0.5;
	vec3 view_dir = (view_position - in_.world_position).normalize();
	vec3 reflect_dir = Reflect(-light_dir, norm);
	//vec3 reflect_dir = (2.0 * (light_dir * norm) * norm) - light_dir;
	float spec = pow(Max(view_dir * reflect_dir, 0.0), 32);
	vec3 specular = specular_strength * spec * light_color;


	vec3 result = (ambient + diffuse + specular).multiply(object_color);
	out_->color = vec4(result, 1.0);
}





FragmentShaderLightFull::FragmentShaderLightFull(vec3 & view_position, Material &material, Light &light) :
	view_position(view_position), 
	material(material),
	light(light) {
}

void FragmentShaderLightFull::Program() {
	// ambient
	vec3 ambient = light.ambient.multiply(material.ambient);

	// diffuse
	vec3 norm = in_.world_normal.normalize();
	vec3 light_dir = (light.position - in_.world_position).normalize();

	float diff = Max(norm * light_dir, 0.0);
	vec3 diffuse = light.diffuse.multiply(diff * material.diffuse);

	// specular
	vec3 view_dir = (view_position - in_.world_position).normalize();
	vec3 reflect_dir = Reflect(-light_dir, norm);
	float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);
	vec3 specular = light.specular.multiply(spec * material.specular);


	vec3 result = ambient + diffuse + specular;
	out_->color = vec4(result, 1.0);
}

FragmentShaderLightTexture::FragmentShaderLightTexture(vec3 &view_position, TextureMaterial &material, Light &light) :
	view_position(view_position), 
	material(material),
	light(light) {
}

void FragmentShaderLightTexture::Program() {

	vec3 diffuse_tex = material.diffuse->GetColor(in_.uv);

	// ambient
	vec3 ambient = light.ambient.multiply(diffuse_tex);

	// diffuse
	vec3 norm = in_.world_normal.normalize();
	vec3 light_dir = (light.position - in_.world_position).normalize();

	float diff = Max(norm * light_dir, 0.0);
	vec3 diffuse = light.diffuse.multiply(diff * diffuse_tex);

	// specular
	vec3 view_dir = (view_position - in_.world_position).normalize();
	vec3 reflect_dir = Reflect(-light_dir, norm);
	float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);
	vec3 specular = light.specular.multiply(spec * material.specular);


	vec3 result = ambient + diffuse + specular;
	out_->color = vec4(result, 1.0);
}

} // namespace softrd