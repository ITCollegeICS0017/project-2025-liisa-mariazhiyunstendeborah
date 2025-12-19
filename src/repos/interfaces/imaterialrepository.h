#ifndef IMaterialRepository_H
#define IMaterialRepository_H

#include <vector>
#include <memory>

//interface for MaterialRepository, CRUD operations and constructor/destructor
class Material;
class IMaterialRepository {
    public:
        IMaterialRepository() = default;

        virtual ~IMaterialRepository() = default;

        virtual void addMaterial(std::shared_ptr<Material> material) = 0;

        virtual void editMaterial(const std::shared_ptr<Material>& updated_mat) = 0;

        virtual void deleteMaterial(std::string mat_type) = 0;
};

#endif