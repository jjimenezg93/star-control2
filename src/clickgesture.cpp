#include "../include/array.h"
#include "../include/clickgesture.h"
#include "../include/event.h"

#include <stdio.h>

#define CLICK_THRESHOLD_TIME 0.3

CClickGesture::CClickGesture() {
	m_pressed = false;
}

void CClickGesture::ModifyArray(Array<CEvent *> &ev, const uint32 numEvents) {
	for (uint32 i = 0; i < numEvents; i++) {
		if (ev[i]->GetController() == EEC_MOUSE) {
			if (!m_pressed && ev[i]->GetId() == EME_LMB_PRESS) {
				m_pressTime = clock();
				m_pressed = true;
			} else if (m_pressed && ev[i]->GetId() == EME_LMB_RELEASE) {
				m_releaseTime = clock();
				m_pressed = false;

				float duration = (static_cast<float>(m_releaseTime - m_pressTime))
					/ CLOCKS_PER_SEC;

				if (duration < CLICK_THRESHOLD_TIME) {
					ev[i]->SetId(EME_LMB_CLICK);
				}
			}
		}
	}

}