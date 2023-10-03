#pragma once

#include <fwd.hpp>
#include "Transform.h"

namespace MyEngine
{
    class Maths
    {
    public:
        static Quaternion Euler(Vector3 euler);
        static float deg2Rad();
        static Vector3 Quat2Vec3(Quaternion Quat, Vector3 Vec);
    };
}
