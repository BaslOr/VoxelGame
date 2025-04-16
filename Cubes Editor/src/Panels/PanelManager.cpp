#include "PanelManager.h"

namespace Cubes {

	static constexpr uint32_t DEFAULT_PANEL_COUNT = 15;

	PanelManager::PanelManager()
	{
		_panels.reserve(DEFAULT_PANEL_COUNT);
	}

	PanelManager::~PanelManager()
	{
		for (auto* panel : _panels) {
			delete panel;
		}
	}

	void PanelManager::OpenPanel(Panel* panel)
	{
		_panels.push_back(panel);
	}

	void PanelManager::ClosePanel(Panel* panel)
	{
		auto it = std::remove(_panels.begin(), _panels.end(), panel);
		if (it != _panels.end()) {
			delete panel;
			_panels.erase(it, _panels.end());
		}
	}

}
