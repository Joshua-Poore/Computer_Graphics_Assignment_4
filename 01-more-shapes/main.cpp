
#include "GLM/gtc/type_ptr.hpp"
#include <glad/gl.h>
#include "learnopengl/shader_4722.h"
#include "cs4722/artifact.h"
#include "cs4722/window.h"
#include "cs4722/buffer_utilities.h"

static std::vector<cs4722::artifact*> artifact_list;
static Shader *shader;

void init(void)
{
    shader = new Shader("01-more-shapes/vertex_shader.glsl" ,"01-more-shapes/fragment_shader.glsl" );
    shader->use();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    cs4722::shape* b = new cs4722::block();
    cs4722::shape* c = new cs4722::block();
    cs4722::shape* d = new cs4722::block();
    cs4722::shape* e = new cs4722::block();
    auto* artf = new cs4722::artifact();
    auto* artfc = new cs4722::artifact();
    auto* artfd = new cs4722::artifact();
    auto* artfe = new cs4722::artifact();
    artf->the_shape = b;
    artfc->the_shape = c;
    artfd->the_shape = d;
    artfe->the_shape = e;
    artf->world_transform.scale = glm::vec3(.25, .75, .3);
    artf->world_transform.translate = glm::vec3(-.5, -.5, .0);
    artfc->world_transform.scale = glm::vec3(.25, .75, .3);
    artfc->world_transform.translate = glm::vec3(-.5, .5, .0);
    artfd->world_transform.scale = glm::vec3(.25, .75, .3);
    artfd->world_transform.translate = glm::vec3(.5, -.5, .0);
    artfe->world_transform.scale = glm::vec3(.25, .75, .3);
    artfe->world_transform.translate = glm::vec3(.5,.5, .0);
    artf->world_transform.rotation_axis = glm::vec3(0, 0, 1);
    artf->world_transform.rotation_angle = M_PI/6;
    artfc->world_transform.rotation_axis = glm::vec3(0, 0, 1);
    artfc->world_transform.rotation_angle = M_PI/3;
    artfd->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artfd->world_transform.rotation_angle = M_PI/6;
    artfe->world_transform.rotation_axis = glm::vec3(1, 0, 0);
    artfe->world_transform.rotation_angle = M_PI/3;

    artifact_list.push_back(artf);
    artifact_list.push_back(artfc);
    artifact_list.push_back(artfd);
    artifact_list.push_back(artfe);

    cs4722::init_buffers(shader->ID, artifact_list, "b_position", "b_color");
}


void render()
{
    for (auto artf : artifact_list) {
        auto model_matrix = artf->animation_transform.matrix()
                            * artf->world_transform.matrix();
        shader->setMat4("u_transform", model_matrix);
        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
    }
}

int
main(int argc, char** argv)
{
    glfwInit();

    // set the OpenGL version to use: 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    int xpos, ypos, width, height;
    glfwGetMonitorWorkarea(primary, &xpos, &ypos, &width, &height);
//std::cout << xpos << " " << ypos << " " << width << " " << height << std::endl;
    int size = glm::min(width, height);
    float ratio = .9f;
    int w_width = int(ratio * size);
    int w_height = w_width;
    int w_x = int(size * (1 - ratio) / 2);
    int w_y = w_x;
    GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Animation", NULL, NULL);
    glfwSetWindowPos(window, w_x, w_y);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

    init();

    while (!glfwWindowShouldClose(window))
    {

        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float_array());
        glClear(GL_DEPTH_BUFFER_BIT);

        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
