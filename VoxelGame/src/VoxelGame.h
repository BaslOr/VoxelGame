#include <Cubes.h>
#include "Camera.h"

namespace GameNamespace {

	class VoxelGame : public Cubes::Application
	{
	public:
		VoxelGame();
		~VoxelGame() = default;

		void OnUpdate() override;

	private:
		Camera _camera;

		std::shared_ptr<Cubes::Shader> _shader;
		std::shared_ptr<Cubes::VertexArray> _vertexArray;
		std::shared_ptr<Cubes::VertexBuffer> _vertexBuffer;
		std::shared_ptr<Cubes::IndexBuffer> _indexBuffer;
	};

}

Cubes::Application* Cubes::CreateApplication() {
	return new GameNamespace::VoxelGame();
}
