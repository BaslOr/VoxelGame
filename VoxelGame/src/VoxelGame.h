#include <Cubes.h>

class VoxelGame : public Cubes::Application
{
public:
	VoxelGame() 
	{
		PushOverlay(new Cubes::ImGUILayer());
	}
	~VoxelGame() {}

private:

};

Cubes::Application* Cubes::CreateApplication() {
	return new VoxelGame();
}
