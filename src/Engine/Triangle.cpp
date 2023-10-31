#include "Triangle.h"

MyEngine::Triangle::Triangle(Vector3 position, Vector3 scale, Color color): Shape({
    position, scale, {0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, color
})
{
    setVertex();
}

MyEngine::Triangle::Triangle(Transform transform): Shape(transform)
{
    setVertex();
}

MyEngine::Triangle::~Triangle()
{
    vertex.clear();
}

void MyEngine::Triangle::setVertex()
{
    transform.color.normalize();
    vertex.push_back({-1, -1, 0});
    vertex.push_back({1.0f, -1.0f, 0});
    vertex.push_back({0.0f, 1.0f, 0});
    alignVertex();
}


void MyEngine::Triangle::draw()
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(glm::mat4(1.0f),
                                 glm::vec3(transform.position.x, transform.position.y, transform.position.z));

    if (transform.scale.x != 0 || transform.scale.y != 0 || transform.scale.z != 0)
        modelMatrix = glm::scale(modelMatrix, glm::vec3(transform.scale.x, transform.scale.y, 0.0f));

    if (transform.rotationQuat.x != 0 || transform.rotationQuat.y != 0 || transform.rotationQuat.z != 0)
    {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.x), glm::vec3(1.0, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    Renderer::setModelMatrix(modelMatrix);
    Renderer::drawTriangle(vertex[0].x,vertex[0].y, vertex[1].x,vertex[1].y, vertex[2].x, vertex[2].y, transform.color.r,transform.color.g, transform.color.b);
}
