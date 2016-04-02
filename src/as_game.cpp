#include "../include/as_game.h"
#include "../include/buttonui.h"
#include "../include/controlui.h"
#include "../include/component_render.h"
#include "../include/defs.h"
#include "../include/entity.h"
#include "../include/font.h"
#include "../include/image.h"
#include "../include/inputmanager.h"
#include "../include/menu_defs.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/screen.h"
#include "../include/sprite.h"

ASGame::~ASGame() {
	if (g_wantedState == ESC_EXIT_APP) {
		ResourceManager::Instance().FreeResources();
	}
}

void ASGame::Init() {
	m_world.Init();
	m_hud.Init();
}

void ASGame::ProcessInput() {
	CInputManager::Instance().Update();
}

void ASGame::Update() {
	m_hud.Update();
	m_world.Update();
}

void ASGame::Render() {
	Renderer::Instance().Clear();
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	//render World
	//m_world.Update();
	m_hud.Render();
	Screen::Instance().Refresh();
}

void ASGame::ManageControlEvent(CControlUI * const sender) {
	m_hud.ManageControlEvent(sender);
}
