#define _CRT_SECURE_NO_DEPRECATE
// GLEW
#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <glew.h>
// GLFW
#include <glfw3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <math.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
std::string readFile(const char *filePath);
GLint create_fragment_shader(const char *path);
GLint create_vertex_shader(const char *path);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);

	struct vertex {
		float x;
		float y;
		float z;

		float r;
		float g;
		float b;
	};

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	/*
	GLfloat cube_vertices[] = {
		-0.25f, 0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, 0.25f ,0.25f,
		0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, -0.25f
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDisableVertexAttribArray(0);

	float currentTime = time(0);
	float f = (float)currentTime * (float)M_PI * 0.1f;
	vmath::mat4 mv_matrix =
		vmath::translate(0.0f, 0.0f, -4.0f) *
		vmath::translate(sinf(2.1f * f) * 0.5f,
			cosf(1.7f * f) * 0.5f,
			sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
		vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
		vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);

	*/

	

	//Elements Buffer
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

	//Vertices Buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	GLint vertex_shader = create_vertex_shader("vertex.glsl");
	GLint fragment_shader = create_fragment_shader("fragment.glsl");
	GLint fragment_shader2 = create_fragment_shader("fragment2.glsl");

	GLuint shader_program;
	shader_program = glCreateProgram();

	GLuint shader_program2;
	shader_program2 = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glAttachShader(shader_program2, vertex_shader);
	glAttachShader(shader_program2, fragment_shader2);
	glLinkProgram(shader_program2);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(fragment_shader2);

	//Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	int time_diff = time(0);
	int shader1 = 0;

	while (!glfwWindowShouldClose(window))
	{
		/*if (time(0) - time_diff > 1) {
			if (shader1) {
				glUseProgram(shader_program);
				std::cout << "Using shader 1" << std::endl;
				shader1 = 0;
			}
			else {
				glUseProgram(shader_program2);
				std::cout << "Using shader 2" << std::endl;
				shader1++;
			}
			time_diff = time(0);
		}*/
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float third_phase = (2*M_PI) / 3;
		GLfloat timeValue = glfwGetTime();

		GLfloat corner1_colour[] = { (sin(timeValue) / 2.0) + 0.5 , (sin(timeValue + third_phase) / 2) + 0.5 , (sin(timeValue + 2 * third_phase) / 2) + 0.5, 1.0f};
		GLfloat corner2_colour[] = { (sin(timeValue + 2.0 * third_phase) / 2) + 0.5 , (sin(timeValue) / 2) + 0.5 , (sin(timeValue + third_phase) / 2) + 0.5 };
		GLfloat corner3_colour[] = { (sin(timeValue + third_phase) / 2) + 0.5 , (sin(timeValue + 2 * third_phase) / 2) + 0.5 , (sin(timeValue) / 2) + 0.5 };

		GLfloat red_value = (sin(timeValue) / 2) + 0.5;
		GLfloat blue_value = (sin(timeValue + third_phase) / 2) + 0.5;
		GLfloat green_value = (sin(timeValue + 2 * third_phase) / 2) + 0.5;

		vertices[3] = (sin(timeValue) / 2.0) + 0.5;
		vertices[4] = (sin(timeValue + third_phase) / 2) + 0.5;
		vertices[5] = (sin(timeValue + 2 * third_phase) / 2) + 0.5;
		vertices[9] = (sin(timeValue + 2.0 * third_phase) / 2) + 0.5;
		vertices[10] = (sin(timeValue) / 2) + 0.5;
		vertices[11] = (sin(timeValue + third_phase) / 2) + 0.5;
		vertices[15] = (sin(timeValue + third_phase) / 2) + 0.5;
		vertices[16] = (sin(timeValue + 2 * third_phase) / 2) + 0.5;
		vertices[17] = (sin(timeValue) / 2) + 0.5;

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

		//glDisableVertexAttribArray(1);
		//GLint vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
		glUseProgram(shader_program);
		glVertexAttrib3fv(1, corner1_colour);
		//glVertexAttrib3fv(1, corner2_colour);
		//glUniform4f(vertexColorLocation, red_value, green_value, blue_value, 1.0f);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	printf("Key pressed = %d", key);
}

std::string readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLint create_vertex_shader(const char *path) {
	GLuint vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertex_source_string = readFile(path);
	const char *vertex_source = vertex_source_string.c_str();
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	return vertex_shader;
}

GLint create_fragment_shader(const char *path) {
	GLuint fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragment_source_string = readFile(path);
	std::cout << fragment_source_string << std::endl;
	const char *fragment_source = fragment_source_string.c_str();
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);

	return fragment_shader;
}