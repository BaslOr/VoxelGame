#include <Cubes.h>
#include "Camera.h"

namespace GameNamespace {

    class VoxelGame : public Cubes::Application
    {
    public:
        VoxelGame();
        ~VoxelGame() = default;

        void OnUpdate(Cubes::TimeStep deltaTime) override;

    private:
        Camera _camera;

        Cubes::Ref<Cubes::Texture> _texture;
    };

}

Cubes::Application* Cubes::CreateApplication() {
    return new GameNamespace::VoxelGame();
}
