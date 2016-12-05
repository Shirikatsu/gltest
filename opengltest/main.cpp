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
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
		-0.5f, -0.5f, 0.0f, 2.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 2.0f, 1.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 2.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	GLfloat cube_vertices[] = {
		-0.5f, -0.5f, -0.5f, 3.0f, 2.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 3.0f, 2.0f,
		0.5f,  0.5f, -0.5f, 2.0f, 1.0f, 3.0f,
		0.5f,  0.5f, -0.5f, 2.0f, 1.0f, 3.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 3.0f, 2.0f, 1.0f,
		
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 2.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 2.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 2.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 2.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 2.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 2.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		
		-0.5f, -0.5f, -0.5f, 2.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 2.0f,
		-0.5f, -0.5f, -0.5f, 2.0f, 1.0f, 0.0f,
		
		-0.5f,  0.5f, -0.5f, 0.0f, 2.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 2.0f,
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 2.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 2.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 2.0f, 1.0f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STREAM_DRAW);

	GLint cube_vertex_shader = create_vertex_shader("cube_vertex.glsl");
	GLint cube_fragment_shader = create_fragment_shader("cube_fragment.glsl");
	GLuint cube_shader_program;
	cube_shader_program = glCreateProgram();
	glAttachShader(cube_shader_program, cube_vertex_shader);
	glAttachShader(cube_shader_program, cube_fragment_shader);
	glLinkProgram(cube_shader_program);
	glDeleteShader(cube_vertex_shader);
	glDeleteShader(cube_fragment_shader);
	

	//Elements Buffer
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

	//Vertices Buffer
	/*GLuint VBO;
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
	glDeleteShader(fragment_shader2);*/

	//Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	int time_diff = time(0);
	int shader1 = 0;

	//model = glm::rotate(model, -35.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float q_phase = (2*M_PI) / 4;
		GLfloat timeValue = glfwGetTime();

		glUseProgram(cube_shader_program);

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

		glm::mat4 projection;
		projection = glm::perspective(90.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		/*glm::mat4 model;
		model = glm::rotate(model, timeValue, glm::vec3(0.5f, 1.0f, 0.0f));*/

		GLint viewLoc = glGetUniformLocation(cube_shader_program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		GLint projLoc = glGetUniformLocation(cube_shader_program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint modelLoc = glGetUniformLocation(cube_shader_program, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		GLint phase = glGetUniformLocation(cube_shader_program, "phase");
		glUniform1f(phase, q_phase);
		GLint time_val = glGetUniformLocation(cube_shader_program, "time_value");
		glUniform1f(time_val, timeValue);

		/*glUseProgram(shader_program);
		glm::mat4 trans;
		trans = glm::rotate(trans, timeValue, glm::vec3(0.0, 0.0, 1.0));
		GLint matrix = glGetUniformLocation(shader_program, "transform");
		glUniformMatrix4fv(matrix, 1, GL_FALSE, glm::value_ptr(trans));
		GLint phase = glGetUniformLocation(shader_program, "third_phase");
		glUniform1f(phase, third_phase);
		GLint time_val = glGetUniformLocation(shader_program, "time_value");
		glUniform1f(time_val, timeValue);

		GLint modelLoc = glGetUniformLocation(shader_program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GLint viewLoc = glGetUniformLocation(shader_program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		GLint projLoc = glGetUniformLocation(shader_program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));*/

		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, timeValue, glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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