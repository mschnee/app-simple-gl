#pragma once
#include <EventEmitter/Emitter.h>

namespace Events {
	static EventEmitter::EventId FileLoaded = 1;
	static EventEmitter::EventId SettingsReady = 2;
	static EventEmitter::EventId SettingsReloaded = 3;
}