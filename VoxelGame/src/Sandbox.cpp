#include <Cubes.h>
#include "Camera.h"
#include "SandboxLayer.h"

#include "Cubes/Core/Entrypoint.h"

class Sandbox : public Cubes::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{
	}
};

namespace Cubes {

    Application* Cubes::CreateApplication() {
        return new Sandbox();
    }

}
