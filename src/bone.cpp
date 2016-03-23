#pragma warning(push, 0)
#include "../include/bone.h"
#include "../include/glinclude.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"

Bone::Bone() {
    m_id = "m_id";
    m_image = NULL;
    m_pivotX = 0;
    m_pivotY = 0;
    m_handleX = 0;
    m_handleY = 0;
    m_currentX = m_currentY = m_currentRotation = 0;
    m_currentScaleX = m_currentScaleY = 1;
}

Bone::Bone(const String& id, Image* image, double pivotX, double pivotY, double handleX, double handleY) {
	m_id = id;
	m_image = image;
	m_pivotX = pivotX;
	m_pivotY = pivotY;
	m_handleX = handleX;
	m_handleY = handleY;
	m_currentX = m_currentY = m_currentRotation = 0;
    m_currentScaleX = m_currentScaleY = 1;
}

const Bone* Bone::FindChild(const String &id) const {
    // Buscamos en los hijos del hueso
    for ( uint32 i = 0; i < m_children.Size(); i++ )
        if ( m_children[i].GetID() == id )
            return &m_children[i];

	// Si no, en toda su descendencia
    for ( uint32 i = 0; i < m_children.Size(); i++ ) {
        const Bone* bone = m_children[i].FindChild(id);
		if ( bone != NULL )
			return bone;
	}

	// No se ha encontrado
    return NULL;
}

Bone* Bone::FindChild(const String &id) {
    // Buscamos en los hijos del hueso
    for ( uint32 i = 0; i < m_children.Size(); i++ )
        if ( m_children[i].GetID() == id )
            return &m_children[i];

    // Si no, en toda su descendencia
    for ( uint32 i = 0; i < m_children.Size(); i++ ) {
        Bone* bone = m_children[i].FindChild(id);
        if ( bone != NULL )
            return bone;
    }

    // No se ha encontrado
    return NULL;
}

const Frame* Bone::FindFrame(uint32 id) const {
    for ( uint32 i = 0; i < m_frames.Size(); i++ )
        if ( m_frames[i].GetId() == id )
            return &m_frames[i];
	return NULL;
}

void Bone::TranslationForFrame(int32 f, double* x, double* y) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL ) {
		*x = frame->GetTranslationX();
		*y = frame->GetTranslationY();
	} else if ( prevFrame != NULL  &&  nextFrame != NULL ) {
		*x = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetTranslationX(), nextFrame->GetTranslationX());
		*y = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetTranslationY(), nextFrame->GetTranslationY());
	} else {
		*x = *y = 0;
	}
}

double Bone::RotationForFrame(int32 f) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL )
		return frame->GetRotation();
	else if ( prevFrame != NULL  &&  nextFrame != NULL )
		return WrapValue(Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetRotation(), nextFrame->GetRotation()), 360);
	else
		return 0;
}

void Bone::ScaleForFrame(int32 f, double* x, double* y) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL ) {
		*x = frame->GetScaleX();
		*y = frame->GetScaleY();
	} else if ( prevFrame != NULL  &&  nextFrame != NULL ) {
		*x = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetScaleX(), nextFrame->GetScaleX());
		*y = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetScaleY(), nextFrame->GetScaleY());
	} else {
		*x = *y = 0;
	}
}

void Bone::Update(int32 currentFrame) {
	TranslationForFrame(currentFrame, &m_currentX, &m_currentY);
	m_currentRotation = RotationForFrame(currentFrame);
	ScaleForFrame(currentFrame, &m_currentScaleX, &m_currentScaleY);

	for (unsigned short int i = 0; i < m_children.Size(); i++) {
		m_children[i].Update(currentFrame);
	}
}

void Bone::Render() {
	Renderer::Instance().PushMatrix();
	Renderer::Instance().TranslateMatrix(m_currentX, m_currentY, 0);
	Renderer::Instance().RotateMatrix(m_currentRotation, 0, 0, -1);

	if (m_image) {
		m_image->SetHandle(m_handleX * m_image->GetWidth(), m_handleY * m_image->GetHeight());
		Renderer::Instance().DrawImage(m_image, 0, 0, 0U, m_image->GetWidth() * m_currentScaleX, m_image->GetHeight() * m_currentScaleY, 0);	//angle must be 0 because rotation is done before in matrix
		Renderer::Instance().TranslateMatrix(m_pivotX * m_image->GetWidth(), m_pivotY * m_image->GetHeight(), 0);
	}

	for (unsigned short int i = 0; i < m_children.Size(); i++) {
		m_children[i].Render();
	}

	Renderer::Instance().PopMatrix();
}

void Bone::GetFrame(int32 f, const Frame** frame, const Frame** prevFrame, const Frame** nextFrame) const {
	*frame = NULL;
	*prevFrame = NULL;
	*nextFrame = NULL;
    for ( uint32 i = 0; i < m_frames.Size(); i++ ) {
        if ( m_frames[i].GetId() == f )
            *frame = &m_frames[i];
        if ( m_frames[i].GetId() < f  &&  (*prevFrame == NULL  ||  (*prevFrame)->GetId() < m_frames[i].GetId()) )
            *prevFrame = &m_frames[i];
        if ( m_frames[i].GetId() > f  &&  (*nextFrame == NULL  ||  (*nextFrame)->GetId() > m_frames[i].GetId()) )
            *nextFrame = &m_frames[i];
	}
}

double Bone::Interpolate(int32 id, int32 prevId, int32 nextId, double prevVal, double nextVal) const {
	return prevVal + (nextVal - prevVal) * static_cast<double>(id - prevId) / static_cast<double>(nextId - prevId);
}
#pragma warning(pop)
