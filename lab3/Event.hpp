#pragma once
//class Event
//{
//public:
//	enum class EventType {
//		KEY_PRESS
//	};
//	Event(EventType type) : type(type) {}
//
//	EventType getType() { return type; }
//private:
//	EventType type;
//};
//
//class KeyPressEvent : public Event
//{
//public:
//	KeyPressEvent(int key, int scancode, int mods) : Event(EventType::KEY_PRESS), key(key), scancode(scancode), mods(mods) {}
//	int getKey() { return key; }
//	int getScancode() { return scancode; }
//	int getMods() { return mods; }
//private:
//	int key;
//	int scancode;
//	int mods;
//};

struct Event 
{
	enum class EventType {
		KEY_PRESS,
	};
	EventType type;

	Event(EventType type) : type(type) {}
};