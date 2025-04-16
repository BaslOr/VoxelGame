#pragma once
#include <string>

namespace Cubes {

    class Panel {
    public:
        Panel(const std::string& name = "Panel")
        : _name(name) {}
        virtual ~Panel() {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}

        virtual void PushStyleVars() {}
        virtual void OnImGuiRender() {}
        virtual void PopStyleVars() {}

        inline std::string GetName() const { return _name; }

    private:
        std::string _name;
    };

}
