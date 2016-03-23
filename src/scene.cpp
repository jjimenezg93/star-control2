#pragma warning(push, 0)
#include "../include/scene.h"
#include "../include/emitter.h"
#include "../include/image.h"
#include "../include/screen.h"
#include "../include/sprite.h"

Scene::Scene(Image* backgroundImg) {
	SetBackgroundImage(backgroundImg);
	SetBackgroundColor(0, 0, 0);
}

Scene::~Scene() {
	for ( int i = 0; i < LAYER_COUNT; i++ ) {
        for ( uint32 j = 0; j < sprites[i].Size(); j++ ) delete sprites[i][j];
        for ( uint32 j = 0; j < emitters[i].Size(); j++ ) delete emitters[i][j];
	}
}

Sprite* Scene::CreateSprite(Image* image, Layer layer) {
	Sprite* spr = new Sprite(image);
	AddSprite(spr, layer);
	return spr;
}

void Scene::DeleteSprite(Sprite* sprite) {
    for ( int i = 0; i < LAYER_COUNT; i++ ) {
        sprites[i].Remove(sprite);
    }
	delete sprite;
}

Emitter* Scene::CreateEmitter(Image* image, bool autofade, Layer layer) {
    emitters[layer].Add(new Emitter(image, autofade));
    return emitters[layer].Last();
}

void Scene::DeleteEmitter(Emitter* emitter) {
    for ( int i = 0; i < LAYER_COUNT; i++ ) {
        emitters[i].Remove(emitter);
    }
	delete emitter;
}

void Scene::Update(double elapsed, Map* map) {
	// Actualizamos sprites m_y emitters
	for ( int i = 0; i < LAYER_COUNT; i++ ) {
        for ( uint32 j = 0; j < sprites[i].Size(); j++ ) sprites[i][j]->Update(elapsed, map);
        for ( uint32 j = 0; j < emitters[i].Size(); j++ ) emitters[i][j]->Update(elapsed);
	}

	// Actualizamos colisiones
    for ( int i = 0; i < LAYER_COUNT; i++ ) {
        for ( int j = 0; j < (int)sprites[i].Size()-1; j++ ) {
            for ( int k = j+1; k < (int)sprites[i].Size(); k++ ) {
                sprites[i][j]->CheckCollision(sprites[i][k]);
            }
        }
    }

	// Actualizamos camara
	camera.Update();
}

void Scene::Render() const {
	Renderer::Instance().Clear(backr, backg, backb);
    Renderer::Instance().SetOrigin(GetCamera().GetX(), GetCamera().GetY());
	if ( backgroundImg ) Renderer::Instance().DrawImage(backgroundImg, 0, 0);
	Renderer::Instance().SetOrigin(0, 0);
	RenderBackground();
    Renderer::Instance().SetOrigin(GetCamera().GetX(), GetCamera().GetY());
	RenderAfterBackground();
	for ( int i = 0; i < LAYER_COUNT; i++ ) {
		RenderSprites((Layer)i);
		RenderEmitters((Layer)i);
	}
}

void Scene::RenderSprites(Layer layer) const {
    for ( uint32 i = 0; i < sprites[layer].Size(); i++ ) sprites[layer][i]->Render();
}

void Scene::RenderEmitters(Layer layer) const {
    for ( uint32 i = 0; i < emitters[layer].Size(); i++ ) emitters[layer][i]->Render();
}
#pragma warning(pop)