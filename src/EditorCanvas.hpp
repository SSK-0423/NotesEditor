#pragma once
#include "Canvas.hpp"

class EditorCanvas : public Canvas {
private:

public:
	EditorCanvas() noexcept;
	~EditorCanvas() noexcept;
	void Initialize() noexcept;
};