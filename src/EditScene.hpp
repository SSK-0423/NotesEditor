#pragma once
#include "BaseScene.hpp"
#include "GameObject.hpp"
#include "EditorCanvas.hpp"
#include "BarManager.hpp"
#include "NotesManager.hpp"
#include "Camera2D.hpp"

class EditScene : public BaseScene{
private:
	// EditorCamera editorCamera
	EditorCanvas editorCanvas;
	Camera2D camera;
	BarManager barManager;
	NotesManager notesManager;
	std::vector<std::vector<GameObject*>*> objList;

public:
	EditScene(ISceneChanger* changer);
	void Initialize() noexcept override;
	void Finalize() noexcept override;
	void Update() noexcept override;
	void Draw() noexcept override;
};