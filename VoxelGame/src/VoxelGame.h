#include <Cubes.h>

class TestLayer : public Cubes::Layer {
public:
	TestLayer()
		: Layer("TestLayer")
	{ }

	void OnUpdate() override {
		CB_INFO("Test Layer::Update");
	}

	void OnEvent(Cubes::Event& e) override {
		CB_TRACE("{0}", e.ToString());
	}
};

class VoxelGame : public Cubes::Application
{
public:
	VoxelGame() {
		PushLayer(new TestLayer());
	}
	~VoxelGame() {}

private:

};

Cubes::Application* Cubes::CreateApplication() {
	return new VoxelGame();
}
