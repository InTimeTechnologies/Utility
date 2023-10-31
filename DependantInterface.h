#pragma once

class DependantInterface {
	public:
		// Constructor / Destructor
		DependantInterface();
		virtual ~DependantInterface();

		// Functions
		virtual void onProviderSet();
		virtual void onProviderUnset();
};
