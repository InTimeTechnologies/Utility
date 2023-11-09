#include "PrivateEvent.h"

// Test
#include <iostream>

// class EventListener

// Object | public

// Constructor / Destructor
EventListener::EventListener() : receiver(nullptr), eventDispatcher(nullptr) {

}
EventListener::~EventListener() {
	disconnect();
}

// Functions
void EventListener::disconnect() {
	// If event listener is not connected to an event dispatcher, return
	if (eventDispatcher == nullptr)
		return;

	// Search for the index where this event listener is in the event listener list of the event dispatcher
	for (int i = 0; i < eventDispatcher->eventListeners.size(); i++)
		if (eventDispatcher->eventListeners[i] == this) {
			// Element found. Remove the event listener from the event listener list of the event dispatcher
			eventDispatcher->eventListeners.erase(eventDispatcher->eventListeners.begin() + i);
			break;
		}

	// Dereference from event dispatcher
	eventDispatcher = nullptr;
}

// Virtual functions
void EventListener::respondToEvent(const PrivateEvent& privateEvent) {
	// To be implemented in child classes
	std::cout << "Response" << std::endl;
}

// class EventDispatcher

// Object | public

// Constructor / Destructor
EventDispatcher::EventDispatcher() : sender(nullptr), eventListeners(std::vector<EventListener*>()) {

}
EventDispatcher::~EventDispatcher() {

}

// Function
void EventDispatcher::connect(EventListener& eventListener) {
	// Disconnect from any connection their might be with other event dispatchers
	eventListener.disconnect();

	// Ass event listener to the list of event listeners
	eventListeners.push_back(&eventListener);
}
void EventDispatcher::connect(EventListener* eventListener) {
	// If eventListener is nullptr, return
	if (eventListener == nullptr)
		return;

	// Disconnect from any connection their might be with other event dispatchers
	eventListener->disconnect();

	// Ass event listener to the list of event listeners
	eventListeners.push_back(eventListener);
}

// Virtual functions
void EventDispatcher::dispatch() {
	// To be implemented by child classes
	const PrivateEvent privateEvent;
	for (EventListener* eventListener : eventListeners)
		eventListener->respondToEvent(privateEvent);
}
