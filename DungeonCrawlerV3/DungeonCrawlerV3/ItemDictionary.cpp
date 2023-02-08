#include "ItemDictionary.h"

ItemDictionary* ItemDictionary::_instance;

ItemDictionary ItemDictionary::Instance() {
	if (_instance != nullptr) return *_instance;

	_instance = new ItemDictionary();
	return *_instance;
}