#pragma once

#include <iostream>
using namespace std;

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
		std::string name;
		VirtualDirectory<T>* parentDirectory;

		VirtualFile();
		VirtualFile(const std::string& name);
		VirtualFile(const std::string& name, T data);
		VirtualFile(const std::string& name, T data, VirtualFile<T>* parentDirectory);
		VirtualFile(const VirtualFile& otherVirtualFile);
		void operator = (const VirtualFile& otherVirtualFile);
		~VirtualFile();
	public:
		T data;

		bool setName(const std::string& name);
		std::string getName();
		std::string getPath();

		bool setParentDirectory(VirtualDirectory<T>* parentDirectory);
		VirtualDirectory<T>* getParentDirectory();

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
bool VirtualFile<T>::setName(const std::string& name) {
	if (parentDirectory == nullptr) {
		this->name = name;
		return true;
	}
	for (unsigned int i = 0; i < parentDirectory->virtualFiles->getSize(); i++)
		if (name == parentDirectory->virtualFiles->get(i)->getName())
			return false;
	this->name = name;
	return true;
}

template <class T>
std::string VirtualFile<T>::getName() {
	return name;
}

template <class T>
std::string VirtualFile<T>::getPath() {
	std::string path = name;
	VirtualDirectory<T>* parentDirectory = this->parentDirectory;
	while (parentDirectory != nullptr) {
		name = parentDirectory->name + "\\" + name;
		parentDirectory = parentDirectory->parentDirectory;
	}
	return path;
}

template <class T>
bool VirtualFile<T>::setParentDirectory(VirtualDirectory<T>* parentDirectory) {
	if (parentDirectory == nullptr)
		return false;
	for (unsigned int i = 0; i < parentDirectory->virtualFiles->getSize(); i++)
		if (parentDirectory->virtualFiles->get(i)->getName() == name)
			return false;
	if (this->parentDirectory != nullptr)
		parentDirectory->virtualFiles->remove(this);
	this->parentDirectory = parentDirectory;
	return true;
}

template <class T>
VirtualDirectory<T>* VirtualFile<T>::getParentDirectory() {
	return parentDirectory;
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
		std::string name;

		VirtualDirectory();
		VirtualDirectory(const std::string& name);
		VirtualDirectory(const VirtualDirectory<U>& otherVirtualDirectory);
		void operator = (const VirtualDirectory<U>& otherVirtualDirectory);
		~VirtualDirectory();
	public:
		ArrayList<VirtualDirectory<U>*>* virtualDirectories;
		ArrayList<VirtualFile<U>*> virtualFiles;
		VirtualDirectory<U>* parentDirectory;

		bool setName(const std::string& name);
		std::string getName();
		std::string getPath();

		bool setParentDirectory(VirtualDirectory<U>* parentDirectory);
		VirtualDirectory<U>* getParentDirectory();

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
bool VirtualDirectory<U>::setName(const std::string& name) {
	if (parentDirectory == nullptr) {
		this->name = name;
		return true;
	}
	for (unsigned int i = 0; i < parentDirectory->virtualDirectory->getSize(); i++)
		if (name == parentDirectory->virtualDirectory->get(i)->getName())
			return false;
	this->name = name;
	return true;
}

template <class U>
std::string VirtualDirectory<U>::getName() {
	return name;
}

template <class U>
std::string VirtualDirectory<U>::getPath() {
	std::string path = name;
	VirtualDirectory<U>* parentDirectory = this->parentDirectory;
	while (parentDirectory != nullptr) {
		name = parentDirectory->name + "\\" + name;
		parentDirectory = parentDirectory->parentDirectory;
	}
	return path;
}

template <class U>
bool VirtualDirectory<U>::setParentDirectory(VirtualDirectory<U>* parentDirectory) {
	if (parentDirectory == nullptr)
		return false;
	for (unsigned int i = 0; i < parentDirectory->virtualDirectories->getSize(); i++)
		if (parentDirectory->virtualDirectories->get(i)->getName() == name)
			return false;
	if (this->parentDirectory != nullptr)
		parentDirectory->virtualDirectories->remove(this);
	this->parentDirectory = parentDirectory;
	return true;
}

template <class U>
VirtualDirectory<U>* VirtualDirectory<U>::getParentDirectory() {
	return parentDirectory;
}

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
	for (unsigned int i = 0; i < virtualFiles->getSize(); i++)
		if (virtualFiles->get(i)->name == virtualFile->name)
			return;
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
