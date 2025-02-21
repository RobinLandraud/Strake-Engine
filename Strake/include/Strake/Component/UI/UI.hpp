#include <Strake/Component/Component.hpp>

namespace Strake {
    class UI : public Component {
    public:
        UI(GameObject &parent);
        ~UI();
    };
}