#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    //ColliderComponent
    class ColliderComponent: public Component {
    public:

        glm::vec3 size = { 0, 0, 0 };
  

        // The ID of this component type is "Collider"
        static std::string getID() { return "Collider"; }

        // Reads collider center & radius from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}