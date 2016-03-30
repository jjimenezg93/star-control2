#include "../include/inputmanager.h"
#include "../include/nsinputmanagerentity.h"
#include "../include/event.h"

namespace IInputManagerEntity {
	void Register(IRegistrable * const obj, const EEventController controller, const uint32 id) {
		CInputManager::Instance().Register(obj, controller, id);
	}

	uint8 Unregister(IRegistrable * const obj, const EEventController controller,
			const uint32 id) {
		return CInputManager::Instance().Unregister(obj, controller, id);
	}
}