#pragma once

#include <string>
#include "ArrayList.h"

template <class T> class VirtualFile;
template <class U> class VirtualDirectory;
template <class V> class VirtualDirectoryTree;

// VirtualFile
template <class T>
class VirtualFile {
	// Static
	public:
		static VirtualFile<T>* create();
		static VirtualFile<T>* create(const std::string& name);
		static VirtualFile<T>* create(const std::string& name, T data);
		static VirtualFile<T>* create(const std::string& name, T data, VirtualFile<T>* parentDirectory);
	// Object
	private:
		VirtualFile();
		VirtualFile(const std::string& name);
		VirtualFile(const std::string& name, T data);
		VirtualFile(const std::string& name, T data, VirtualFile<T>* parentDirectory);
		VirtualFile(const VirtualFile& otherVirtualFile);
		void operator = (const VirtualFile& otherVirtualFile);
		~VirtualFile();
	public:
		std::string name;
		T data;
		VirtualDirectory<T>* parentDirectory;

		std::string getPath();

		void destroy();
};

// Static | public
template <class T>
VirtualFile<T>* VirtualFile<T>::create() {
	return new VirtualFile<T>();
}

template <class T>
VirtualFile<T>* VirtualFile<T>::create(const std::string& name) {
	return new VirtualFile<T>(name);
}

template <class T>
VirtualFile<T>* VirtualFile<T>::create(const std::string& name, T data) {
	return new VirtualFile<T>(name, data);
}

template <class T>
VirtualFile<T>* VirtualFile<T>::create(const std::string& name, T data, VirtualFile<T>* parentDirectory) {
	return new VirtualFile<T>(name, data, parentDirectory);
}

// Object | private
template <class T>
VirtualFile<T>::VirtualFile() {
	name = "";
	parentDirectory = nullptr;
}

template <class T>
VirtualFile<T>::VirtualFile(const std::string& name) {
	this->name = name;
	parentDirectory = nullptr;
}

template <class T>
VirtualFile<T>::VirtualFile(const std::string& name, T data) {
	this->name = name;
	this->data = data;
	this->parentDirectory = nullptr;
}

template <class T>
VirtualFile<T>::VirtualFile(const std::string& name, T data, VirtualFile<T>* parentDirectory) {
	this->name = name;
	this->data = data;
	this->parentDirectory = parentDirectory;
}

template <class T>
VirtualFile<T>::VirtualFile(const VirtualFile& otherVirtualFile) {
	name = otherVirtualFile.name;
	data = otherVirtualFile.data;
	parentDirectory = nullptr;
}

template <class T>
void VirtualFile<T>::operator = (const VirtualFile<T>& otherVirtualFile) {
	name = otherVirtualFile.name;
	data = otherVirtualFile.data;
}

template <class T>
VirtualFile<T>::~VirtualFile() {

}

// Object | public
template <class T>
std::string VirtualFile<T>::getPath() {
	std::string path = name;
	VirtualDirectory<T>* parentDirectory = this->parentDirectory;
	while (parentDirectory != nullptr) {
		name = parentDirectory->name + name;
		parentDirectory = parentDirectory->parentDirectory;
	}
	return path;
}

template <class T>
void VirtualFile<T>::destroy() {
	delete this;
}

// VirtualDirectory
template <class U>
class VirtualDirectory {
	// Static
	public:
		static VirtualDirectory<U>* create();
		static VirtualDirectory<U>* create(const std::string& name);
		static VirtualDirectory<U>* create(const VirtualDirectory<U>& otherVirtualDirectory);
	// Object
	private:
		VirtualDirectory();
		VirtualDirectory(const std::string& name);
		VirtualDirectory(const VirtualDirectory<U>& otherVirtualDirectory);
		void operator = (const VirtualDirectory<U>& otherVirtualDirectory);
		~VirtualDirectory();
	public:
		std::string name;
		ArrayList<VirtualDirectory<U>*>* virtualDirectories;
		ArrayList<VirtualFile<U>*> virtualFiles;
		VirtualDirectory<U>* parentDirectory;

		void addDirectory(VirtualDirectory<U>* virtualDirectory);
		VirtualDirectory<U>* getDirectories();
		unsigned int getDirectoryCount();

		void addFile(VirtualFile<U>* virtualFile);
		VirtualFile<U>* getFiles();
		unsigned int getFileCount();

		void destroy();
};

// Static | public
template <class U>
VirtualDirectory<U>* VirtualDirectory<U>::create() {
	return new VirtualDirectory<U>();
}

template <class U>
VirtualDirectory<U>* VirtualDirectory<U>::create(const std::string& name) {
	return new VirtualDirectory<U>(name);
}

template <class U>
VirtualDirectory<U>* VirtualDirectory<U>::create(const VirtualDirectory<U>& otherVirtualDirectory) {
	return new VirtualDirectory<U>(otherVirtualDirectory);
}

// Object | private
template <class U>
VirtualDirectory<U>::VirtualDirectory() {
	name = "";
	virtualDirectories = nullptr;
	parentDirectory = nullptr;
}

template <class U>
VirtualDirectory<U>::VirtualDirectory(const std::string& name) {
	this->name = name;
	virtualDirectories = nullptr;
	parentDirectory = nullptr;
}

template <class U>
VirtualDirectory<U>::VirtualDirectory(const VirtualDirectory<U>& otherVirtualDirectory) {
	name = otherVirtualDirectory.name;
	virtualDirectories = otherVirtualDirectory.virtualDirectories;
	virtualFiles = otherVirtualDirectory.virtualFiles;
}

template <class U>
void VirtualDirectory<U>::operator = (const VirtualDirectory<U>& otherVirtualDirectory) {
	name = otherVirtualDirectory.name;
	virtualDirectories = otherVirtualDirectory.virtualDirectories;
	virtualFiles = otherVirtualDirectory.virtualFiles;
}

template <class U>
VirtualDirectory<U>::~VirtualDirectory() {
	if (parentDirectory != nullptr)
		parentDirectory->virtualDirectories->remove(this);
	if (virtualDirectories != nullptr) {
		while (virtualDirectories->getSize() > 0) {
			virtualDirectories->get(0)->destroy();
		}
	}
	cout << "VirtualDirectory deleted" << endl;
}

// Object | public
template <class U>
void VirtualDirectory<U>::addDirectory(VirtualDirectory<U>* virtualDirectory) {
	if (virtualDirectories == nullptr) {
		virtualDirectories = new ArrayList<VirtualDirectory<U>*>();
	}
	virtualDirectory->parentDirectory = this;
	virtualDirectories->add(virtualDirectory);
}

template <class U>
VirtualDirectory<U>* VirtualDirectory<U>::getDirectories() {
	return virtualDirectories->getArray();
}

template <class U>
unsigned int VirtualDirectory<U>::getDirectoryCount() {
	return virtualDirectories->getSize();
}

template <class U>
void VirtualDirectory<U>::addFile(VirtualFile<U>* virtualFile) {
	virtualFiles.add(virtualFile);
}

template <class U>
VirtualFile<U>* VirtualDirectory<U>::getFiles() {
	return virtualFiles.getArray();
}

template <class U>
unsigned int VirtualDirectory<U>::getFileCount() {
	return virtualFiles.getSize();
}

template <class U>
void VirtualDirectory<U>::destroy() {
	delete this;
}
