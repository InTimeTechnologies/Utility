#pragma once

// Dependencies | std
#include <vector>
#include <functional>

// Dependencies | utility
#include <utility/DoublyLinkedList.h>

// Forward declarations | PrivateEvent
class PrivateEvent;
class EventListener;
class EventDispatcher;

class PrivateEvent {
	
};

class EventListener {
	// Object
	private:
		// Properties
		void* receiver;
		EventDispatcher* eventDispatcher;

	public:
		// Constructor / Destructor
		EventListener();
		~EventListener();

		// Function
		void disconnect();
		
		// Virtual functions
		virtual void respondToEvent(const PrivateEvent& privateEvent);
};

class EventDispatcher {
	// Friends
	friend class EventListener;

	// Object
	private:
		// Properties
		void* sender;
		std::vector<EventListener*> eventListeners;

	public:
		// Constructor / Destructor
		EventDispatcher();
		~EventDispatcher();

		// Functions
		void connect(EventListener& eventListener);
		void connect(EventListener* eventListener);
		
		// Virtual functions
		virtual void dispatch();
};
