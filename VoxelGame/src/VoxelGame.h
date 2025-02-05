#include <Cubes.h>


class VoxelGame : public Cubes::Application
{
public:
	VoxelGame();
	~VoxelGame();

private:

};

Cubes::Application* Cubes::CreateApplication() {
	return new VoxelGame();
}
