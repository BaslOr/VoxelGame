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

		Cubes::Ref<Cubes::Shader> _shader;
		Cubes::Ref<Cubes::VertexArray> _vertexArray;
		Cubes::Ref<Cubes::VertexBuffer> _vertexBuffer;
		Cubes::Ref<Cubes::IndexBuffer> _indexBuffer;
		Cubes::Ref<Cubes::Texture> _texture;
	};

}

Cubes::Application* Cubes::CreateApplication() {
	return new GameNamespace::VoxelGame();
}
