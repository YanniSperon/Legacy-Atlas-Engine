#pragma once

#include "Associations.h"
#include "UUID.h"

#include <string>

template <class T>
class Singleton {
public:
	static T& GetInstance() {
		static T instance;
		if (!instance) {
			instance = T();
		}
		return instance;
	}
};

template <class T>
class Manager : public Singleton<Manager<T>> {
protected:
	UnorderedMap<UUID, T> stored;

public:
	bool DoesValueExist(const UUID& uuid) const {
		return stored.find(uuid) != stored.end();
	}

	UnorderedMap<UUID, T>::iterator Find(const UUID& uuid) {
		return stored.find(uuid);
	}

	UnorderedMap<UUID, T>::const_iterator Find(const UUID& uuid) const {
		return stored.find(uuid);
	}

	UUID& Create() {
		auto [it, inserted] = stored.emplace(UUID(), T());
		return it->first;
	}

	T& CreateOrFetch(const UUID& uuid) {
		auto [it, inserted] = stored.emplace(uuid, T());
		return it->second;
	}

	bool Insert(const UUID& uuid, T& data) {
		auto [it, inserted] = stored.emplace(uuid, data);
		return inserted;
	}

	T& Pop(const UUID& uuid) {
		auto it = stored.find(uuid);
		if (it == stored.end()) {
			throw std::invalid_argument("UUID does not exist in the data stored in the Manager");
		}
		return it->second;
	}
};