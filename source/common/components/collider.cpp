#include "collider.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
#include <iostream>

namespace our {
    // Reads collider center & radius from the given json object
    void ColliderComponent::deserialize(const nlohmann::json& data)
    {
        if (!data.is_object()) return;

        size = data.value("size", size);
        
    }
}