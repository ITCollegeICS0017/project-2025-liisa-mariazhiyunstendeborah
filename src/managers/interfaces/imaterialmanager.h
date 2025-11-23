#ifndef IMaterialManager_H
#define IMaterialManager_H

#include <vector>
#include <memory>

class Material;
class IMaterialManager {
    public:
        IMaterialManager() = default;

        virtual ~IMaterialManager() = default;

        virtual void addMaterial(std::shared_ptr<Material> material) = 0;

        virtual void editMaterial(const std::shared_ptr<Material>& updated_mat) = 0;

        virtual void deleteMaterial(std::string mat_type) = 0;
};

#endif