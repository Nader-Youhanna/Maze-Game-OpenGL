#include "camera.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace our {
    // Reads camera parameters from the given json object
    void CameraComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        std::string cameraTypeStr = data.value("cameraType", "perspective");
        if(cameraTypeStr == "orthographic"){
            cameraType = CameraType::ORTHOGRAPHIC;
        } else {
            cameraType = CameraType::PERSPECTIVE;
        }
        near = data.value("near", 0.01f);
        far = data.value("far", 600.0f);
        fovY = data.value("fovY", 90.0f) * (glm::pi<float>() / 180);
        orthoHeight = data.value("orthoHeight", 30.0f);
    }

    // Creates and returns the camera view matrix
    glm::mat4 CameraComponent::getViewMatrix() const {
        auto owner = getOwner();
        auto M = owner->getLocalToWorldMatrix();
        //TODO: (Req 8) Complete this function
        //HINT:
        // In the camera space:
        // - eye is the origin (0,0,0)
        // - center is any point on the line of sight. So center can be any point (0,0,z) where z < 0. For simplicity, we let center be (0,0,-1)
        // - up is the direction (0,1,0)
        // but to use glm::lookAt, we need eye, center and up in the world state.
        // Since M (see above) transforms from the camera to thw world space, you can use M to compute:
        // - the eye position which is the point (0,0,0) but after being transformed by M
        // - the center position which is the point (0,0,-1) but after being transformed by M
        // - the up direction which is the vector (0,1,0) but after being transformed by M
        // then you can use glm::lookAt to compute the view matrix
        // NOTE: glm::lookAt takes the eye position, the center position and the up direction
        glm::vec3 eye = glm::vec3(0.0f);
        glm::vec3 center = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        eye = glm::vec3(M * glm::vec4(eye, 1.0f));
        center = glm::vec3(M * glm::vec4(center, 1.0f));
        up = glm::vec3(M * glm::vec4(up, 0.0f));

        return glm::lookAt(eye, center, up);
        // return glm::mat4(1.0f);
    }

    // Creates and returns the camera projection matrix
    // "viewportSize" is used to compute the aspect ratio
    glm::mat4 CameraComponent::getProjectionMatrix(glm::ivec2 viewportSize) const {
        //TODO: (Req 8) Wrtie this function
        // NOTE: The function glm::ortho can be used to create the orthographic projection matrix
        // It takes left, right, bottom, top. Bottom is -orthoHeight/2 and Top is orthoHeight/2.
        // Left and Right are the same but after being multiplied by the aspect ratio
        // For the perspective camera, you can use glm::perspective
        // It takes the field of view, the aspect ratio and the near and far planes

        if(cameraType == CameraType::ORTHOGRAPHIC){
            float aspectRatio = viewportSize.x / (float)viewportSize.y;
            float left = -orthoHeight * aspectRatio / 2.0f;
            float right = orthoHeight * aspectRatio / 2.0f;
            float bottom = -orthoHeight / 2.0f;
            float top = orthoHeight / 2.0f;
            return glm::ortho(left, right, bottom, top, near, far);
        } else {
            float aspectRatio = viewportSize.x / (float)viewportSize.y;
            return glm::perspective(fovY, aspectRatio, near, far);
        }
    }
}