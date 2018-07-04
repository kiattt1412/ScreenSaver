#include <iostream>

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>

class Vec3f {
public:
	float x, y, z;
	Vec3f() {}
	Vec3f(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {};
};

class Transform {
public:
	Vec3f t, r, s, c;
	float spd;
	Transform() {}
	Transform(Vec3f _t, Vec3f _r, Vec3f _s, Vec3f _c, float _spd) :t(_t), r(_r), s(_s), c(_c), spd(_spd) {};
};

class Triangle {
public:
	Vec3f trans;
	Vec3f rot;
	Vec3f scale;
	Transform transform;
	float t = 0;


	Triangle() {};
	void draw() {
		t = t + transform.spd;
		glPushMatrix();
		//	glTranslatef(trans.x, trans.y, trans.z);
		//	glRotatef(t, rot.x, rot.y, rot.z);
		//	glScalef(scale.x, scale.y, scale.z);
		glRotatef(t, transform.r.x, transform.r.y, transform.r.z);
		glTranslatef(transform.t.x, transform.t.y, transform.t.z);
		glScalef(transform.s.x, transform.s.y, transform.s.z);
		glBegin(GL_TRIANGLES);
		glColor3f(transform.c.x, transform.c.y, transform.c.z);
		glVertex3f(0.0f, 0.0f, 0.0f);

		//glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		std::cout << "I pressed E" << std::endl;
}

int main() {
	GLFWwindow *window = nullptr;
	/*initialize the glfw system*/
	if (!glfwInit()) {
		glfwTerminate();
		return -1;
	}
	window = glfwCreateWindow(1920, 1080, "My Game", glfwGetPrimaryMonitor() /*nullptr*/, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	std::vector<std::shared_ptr<Triangle>> triStore;
	std::vector<std::shared_ptr<Triangle>> triStore2;

	for (int i = 0; i < 60; i++)
	{
		auto tri1 = std::make_shared<Triangle>();
		tri1->transform = Transform(Vec3f(0.0f, 0.1f + (0.01f*i), 0.0f), Vec3f(0, 1, 1), Vec3f(0.05f, 0.2f, 0.05f), Vec3f(0, 1.0f, 0), (0.001f*i));
		triStore.push_back(tri1);
	}

	for (int i = 0; i < 60; i++)
	{
		auto tri2 = std::make_shared<Triangle>();
		tri2->transform = Transform(Vec3f(0.0f, -0.1f - (0.01f*i), 0.0f), Vec3f(0, 1, 1), Vec3f(0.05f, 0.2f, 0.05f), Vec3f(1.0f, 0.0f, 0), (0.001f*i));
		triStore2.push_back(tri2);
	}



	/*game loop*/
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT); // Render color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // change color

		for (int i = 0; i < 60; i++)
		{
			triStore[i]->draw();
			triStore2[i]->draw();
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}