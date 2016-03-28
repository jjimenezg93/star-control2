#include "../include/draggesture.h"
#include "../include/array.h"
#include "../include/event.h"
#include <iostream>

CDragGesture::CDragGesture() {
	m_pressed = false;
}

void CDragGesture::ModifyArray(Array<CEvent *> &ev, const uint32 numEvents) {
	for (uint32 i = 0; i < numEvents; i++) {
		if (ev[i]->GetController() == EEC_MOUSE) {
			if (ev[i]->GetId() == EME_LMB_PRESS) {
				m_pressed = true;
			} else if (ev[i]->GetId() == EME_LMB_RELEASE) {
				m_pressed = false;
			}
			if (m_pressed && (m_x != ev[i]->GetX() || m_y != ev[i]->GetY())) {
				ev[i]->SetId(EME_LMB_DRAG);
			}
		}
	}
	m_x = ev[0]->GetX();
	m_y = ev[0]->GetY();
	m_pressed = false;
}