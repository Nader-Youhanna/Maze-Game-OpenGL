#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our {

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR    1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL   3

    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be drawn by glDrawElements 
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each triangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            //Get number of elements
            elementCount = GLsizei(elements.size());

            //Same as phase1, Generating Vertex Array, and Binding Vertex Array
            //Generate 1 Vertex Array and 2 Buffers (1 Vertex buffer + 1 Element Buffer)
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            //Bind Vertex Array
            //The VAO will store all the "glVertexAttribPointer" and "glEnableVertexAttribArray" till it is unbound
            //It will also store all the "glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ...)"
            glBindVertexArray(VAO);

            //Bind and fill vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);


            ///////////Define how the buffer should be read and sent to the shader
            //Arguments:
            //  index: which attribute location should receive this data
            //  size: number of elements to send
            //  type: type of elements to send
            //  normalized: should data be normalized (e.g. bytes will be normalized from [-128,127] to [-1,1])
            //  stride: how much to increment the pointer after reading a value
            //  offset: the initial value of the pointer before reading any value

            //For position data
            //Attribute location 0 will read data as 3 floats without normalization
            //The pointer will increment 28 bytes (sizeof(Vertex)) and will start at offset of position in Vertex
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);

            //For color data
            //Attribute location 1 will read data as 4 floats without normalization
            //The pointer will increment 28 bytes (sizeof(Vertex)) and will start at offset of color in Vertex
            glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(1);

            //For he texture coordinates data
            //Attribute location 2 will read data as 2 floats without normalization
            //The pointer will increment 28 bytes (sizeof(Vertex)) and will start at offset of texture coordinates in Vertex
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(2);

            //For normal data
            //Attribute location 3 will read data as 3 floats -without normalization-
            //The pointer will increment 28 bytes (sizeof(Vertex)) and will start at offset of color in Vertex
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(3);

            //Bind and fill element buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
            //Unbind Vertex Array so that it doesn't store any other operation
            glBindVertexArray(0);
        }

        // this function should render the mesh
        void draw()
        {
            //TODO: Write this function
            if (VAO == 0) return; //Check if VAO is created
            //Bind Vertex Array
            glBindVertexArray(VAO);
            //DrawElements uses the element buffer to create triangles to be drawn
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)0);
            //Unbind Vertex Array
            glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            //TODO: Write this function
            //Delete Objects if created
            if (VAO != 0) glDeleteVertexArrays(1, &VAO);
            if (VBO != 0) glDeleteBuffers(1, &VBO);
            if (EBO != 0) glDeleteBuffers(1, &EBO);
        }

        Mesh(Mesh const&) = delete;
        Mesh& operator=(Mesh const&) = delete;
    };

}