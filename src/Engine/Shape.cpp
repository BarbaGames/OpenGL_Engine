#include "Shape.h"

namespace MyEngine {

	Shape::Shape(Vector3 position, Vector3 scale, Color color) :
		Entity({ position, scale, {0,0,0}, {0, 0, 0, 0}, {1,0,0}, {0,1,0}, {0,0,1}, color }) {
		
	}

	Shape::Shape(Transform transform) :
		Entity(transform) {

	}

	Shape::~Shape() {

	}

	void Shape::alignVertex() {
        // Step 1: Calculate the center of the shape
        float centerX = 0.0;
        float centerY = 0.0;

        // Step 2: Find the sum of all vertex positions
        for (const Vector3& vert : vertex) {
            centerX += vert.x;
            centerY += vert.y;
        }

        // Step 3: Calculate the average position
        int numVertices = vertex.size();
        if (numVertices > 0) {
            centerX /= numVertices;
            centerY /= numVertices;
        }

        // Step 4: Calculate the translation values
        float translateX = -centerX;
        float translateY = -centerY;

        // Step 5: Update the vertex positions
        for (Vector3& vert : vertex) {
            vert.x += translateX;
            vert.y += translateY;
        }
	}

}