#pragma once
#include "Shape.h"

namespace MyEngine
{
    class DLLExport Triangle : public Shape
    {
    private:
        void setVertex();
    public:
        Triangle(Vector3 position, Vector3 scale, Color color);
        Triangle(Transform transform);
        ~Triangle();
        void draw() override;
    };
}
