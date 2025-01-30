#pragma once

#include <iostream>

struct Event
{
	enum class Type
	{
		KEY_PRESS,
		WINDOW_RESIZE
	};

	Type type;
protected:
	Event(Type type) : type(type) {}
};

struct KeyPressEvent : public Event
{
	KeyPressEvent(int key, int scancode, int mods) 
		: Event(Event::Type::KEY_PRESS), key(key), scancode(scancode), mods(mods) {}
	~KeyPressEvent()
	{
		std::cout << "KeyPressEvent destructor was called!" << std::endl;
	}
	int key;
	int scancode;
	int mods;
};

struct WindowResizeEvent : public Event
{
	WindowResizeEvent(int width, int height)
		: Event(Event::Type::WINDOW_RESIZE), width(width), height(height) {}
	int width;
	int height;
};