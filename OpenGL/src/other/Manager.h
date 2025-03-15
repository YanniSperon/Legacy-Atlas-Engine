#pragma once

#include "UUID.h"

#include <string>
#include <unordered_map>

namespace Atlas {
	template <class T>
	class Singleton {
	public:
		static T& GetInstance() {
			static T instance;
			return instance;
		}
	};

	template <class T>
	class Manager : public Singleton<Manager<T>> {
	protected:
		std::unordered_map<UUID, T> stored;

	public:
		bool DoesValueExist(const UUID& uuid) const {
			return stored.find(uuid) != stored.end();
		}

		typename std::unordered_map<UUID, T>::iterator Find(const UUID& uuid) {
			return stored.find(uuid);
		}

		typename std::unordered_map<UUID, T>::const_iterator Find(const UUID& uuid) const {
			return stored.find(uuid);
		}

		UUID& Create() {
			auto result = stored.emplace(UUID(), T());
			auto& it = result.first;
			return it->first;
		}

		T& CreateOrFetch(const UUID& uuid) {
			auto result = stored.emplace(uuid, T());
			auto& it = result.first;
			auto& inserted = result.second;
			return it->second;
		}

		bool Insert(const UUID& uuid, T& data) {
			auto result = stored.emplace(uuid, data);
			auto& it = result.first;
			auto& inserted = result.second;
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
}