#pragma once

// Dependencies | std
#include <vector>
#include <functional>

// Dependencies | utility
#include <utility/DoublyLinkedList.h>

// Forward declarations | PrivateEvent
class EventListener;
class EventDispatcher;

class EventListener {
	// Friends
	friend class EventDispatcher;
	
	// Object
	private:
		// Properties
		void* receiver;
		EventDispatcher* eventDispatcher;

	public:
		// Properties
		std::function<void(EventListener* eventListener, void* eventData)> function;

		// Constructor / Destructor
		EventListener();
		~EventListener();

		// Getters
		void* getReceiver();
		EventDispatcher* getEventDispatcher();

		// Function
		void disconnect();
		
		// Virtual functions
		virtual void respondToEvent(void* eventData);
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
		EventDispatcher(void* sender);
		~EventDispatcher();

		// Getters
		void* getSender();
		std::vector<EventListener*> getEventListeners();

		// Functions
		void clearEventListeners();
		void connect(EventListener& eventListener);
		void connect(EventListener* eventListener);
		void dispatch(void* eventData);
};
