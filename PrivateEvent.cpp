#include "PrivateEvent.h"

// class EventListener

// Object | public

// Constructor / Destructor
EventListener::EventListener() : EventListener(nullptr) {

}
EventListener::EventListener(void* owner) : owner(owner), eventDispatcher(nullptr) {

}
EventListener::~EventListener() {
	disconnect();
}

// Getters
void* EventListener::getOwner() {
	return owner;
}
EventDispatcher* EventListener::getEventDispatcher() {
	return eventDispatcher;
}

// Functions
void EventListener::connect(EventDispatcher& eventDispatcher) {
	disconnect();
	this->eventDispatcher = &eventDispatcher;
	eventDispatcher.eventListeners.push_back(this);
}
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
void EventListener::respondToEvent(void* eventData) {
	function(this, eventData);
}

// class EventDispatcher

// Object | public

// Constructor / Destructor
EventDispatcher::EventDispatcher() : EventDispatcher(nullptr) {

}
EventDispatcher::EventDispatcher(void* sender) : sender(sender), eventListeners(std::vector<EventListener*>()) {

}
EventDispatcher::~EventDispatcher() {

}

// Getters
void* EventDispatcher::getSender() {
	return sender;
}
std::vector<EventListener*> EventDispatcher::getEventListeners() {
	return eventListeners;
}

// Function
void EventDispatcher::clearEventListeners() {
	for (EventListener* eventListener : eventListeners)
		eventListener->eventDispatcher;
	eventListeners.clear();
}
void EventDispatcher::connect(EventListener& eventListener) {
	// Disconnect from any connection their might be with other event dispatchers
	eventListener.disconnect();

	// Ass event listener to the list of event listeners
	eventListeners.push_back(&eventListener);
	eventListener.eventDispatcher = this;
}
void EventDispatcher::disconnectAll() {
	// Remove every event listener listening to this event dispatcher
	for (EventListener* eventListener : eventListeners)
		eventListener->eventDispatcher = nullptr;
	eventListeners.clear();
}
void EventDispatcher::dispatch(void* eventData) {
	// Dispatch event to each event listener in list of event listeners
	for (EventListener* eventListener : eventListeners)
		eventListener->respondToEvent(eventData);
}
