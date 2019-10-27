#include "shader.hpp"
#include "config.hpp"
#include "utils.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <dirent.h>

const char* shadersDir = "/../shaders/";
std::map<std::string, unsigned int> vertexShaders = {};
std::map<std::string, unsigned int> fragmentShaders = {};

bool _loadShaders(std::string path, GLenum shaderType, shadersList &shaders);
bool _loadShader(std::string shaderName, const char* shaderSrc, GLenum shaderType, GLuint &shader);

bool shader_loadShaders() {
	std::string baseDir = config_getBinPath() + shadersDir;
	return shadersLoaded = _loadShaders(baseDir + "/vertex/", GL_VERTEX_SHADER, _vertexShaders)
		&& _loadShaders(baseDir + "/fragment/", GL_FRAGMENT_SHADER, _fragmentShaders);
}

bool _loadShaders(std::string path, GLenum shaderType, shadersList &shaders) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cerr << "Could not open shaders directory: " << path << std::endl;
		return false;
	}

	bool res = true;
	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name,
		            fullPath = path + fname,
					shaderSrc;
		if (!utils_isRegularFile(fullPath.c_str())) {
			continue;
		}
		shaderSrc = utils_readFile(fullPath.c_str());
		GLuint shader;
		if (_loadShader(fname, shaderSrc.c_str(), shaderType, shader)) {
			shaders[fname] = shader;
		}
		else {
			res = false;
		}
	}
	closedir(dir);
	return res;
}

bool _loadShader(std::string shaderName, const char* shaderSrc, GLenum shaderType, GLuint &shader) {
	shader = glCreateShader(shaderType);

	// Compile shader
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	// Check shader
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader " << shaderName << " failed compiling:\n" << infoLog << std::endl;
		return false;
	}
	else {
		std::cout << "Shader " << shaderName << " loaded\n";
		return true;
	}
}
