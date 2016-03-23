#pragma warning(push, 0)
#include "../include/skeletonsprite.h"
#include "../include/bone.h"
#include "../include/bonedata.h"
#include "../include/glinclude.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/skeletondata.h"
#include "../include/string.h"

SkeletonSprite::SkeletonSprite(const String& filename) : Sprite(NULL) {
	// Cargamos los datos del XML
	SkeletonData* data = new SkeletonData(filename);

    root = new Bone("world", NULL, 0, 0, 0, 0);

	// Generamos huesos
    for ( uint32 i = 0; i < data->GetBoneDatas().Size(); i++ ) {
		// Obtenemos hueso
        const BoneData& boneData = data->GetBoneDatas()[i];
		
		// Obtenemos padre del hueso
        Bone* parent = root;
        if ( boneData.GetParentName() != "world" )
            parent = root->FindChild(boneData.GetParentName());

		// Obtenemos imagen
        Image* image = ResourceManager::Instance().LoadImage(filename.ExtractDir() + "/" + boneData.GetImageFilename());

		// Creamos hueso
        Bone bone(boneData.GetId(), image, boneData.GetPivotX(), boneData.GetPivotY(), boneData.GetHandleX(), boneData.GetHandleY());

		// Aniadimos frames
        for ( uint32 i = 0; i < boneData.GetFrames().Size(); i++ )
            bone.AddFrame(boneData.GetFrames()[i]);

		// Aniadimos hueso
		parent->AddChild(bone);	
	}

	// Establecemos el rango de la animacion
    const Bone* bone = root->GetChild(0);
	int32 lastframe = 0;
	for ( uint32 index = 0; index < bone->CountFrames(); index++ ) {
        lastframe = max(lastframe, bone->GetFrame(index)->GetId());
	}
	SetFrameRange(0, lastframe);

	// Eliminamos los datos cargados del XML
	delete data;
}

SkeletonSprite::~SkeletonSprite() {
	delete root;
}

void SkeletonSprite::Update(double elapsed, Map* map) {
	// TAREA: Implementar la especificacion del enunciado
	Sprite::Update(elapsed, map);
	this->root->Update(this->GetCurrentFrame());
}

void SkeletonSprite::Render() const {
	// TAREA: Implementar la especificacion del enunciado
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	Renderer::Instance().SetColor(255, 255, 255, 255);

	Renderer::Instance().PushMatrix();
	Renderer::Instance().TranslateMatrix(this->GetX(), this->GetY(), this->GetZ());
	this->root->Render();
	Renderer::Instance().PopMatrix();
}
#pragma warning(pop)