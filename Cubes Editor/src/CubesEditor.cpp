#include <Cubes.h>
#include "EditorLayer.h"

#include "Cubes/Core/Entrypoint.h"

namespace Cubes {

	class CubesEditor : public Application
	{
	public:
		CubesEditor()
		{
			PushLayer(new EditorLayer());
		}

		~CubesEditor()
		{
		}
	};


	Application* CreateApplication() {
		return new CubesEditor();
	}

}
