// LayerStack.h

// LayerStack class
// - control how the layer push
// - provide layer iterator to traverse layers

#ifndef Aphrodite_ENGINE_LAYERSTACK_H
#define Aphrodite_ENGINE_LAYERSTACK_H

#include <vector>

#include "Base.h"
#include "Layer.h"

namespace Aph {
    class LayerStack final {
    public:
        LayerStack() = default;

        ~LayerStack();

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *overlay);

        void PopLayer(Layer *layer);

        void PopOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer *>::iterator end() { return m_Layers.end(); }
        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}// namespace Aph

#endif// Aphrodite_ENGINE_LAYERSTACK_H
