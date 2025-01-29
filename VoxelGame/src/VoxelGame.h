#include <Cubes.h>


class VoxelGame : public Cubes::Application
{
public:
	VoxelGame();
	~VoxelGame();

	void run() override;

private:

};

Cubes::Application* Cubes::CreateApplication() {
	return new VoxelGame();
}
