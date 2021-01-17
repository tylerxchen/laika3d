#include "resourcemanager.hpp"

using namespace laika3d;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

void ResourceManager::cleanup() {
  std::vector<std::string> unused;

  for (const auto& res : resources) {
    if (res.second.use_count() == 1) {
      unused.emplace_back(res.first);
    }
  }

  for (const auto& file : unused) {
    resources.erase(file);
  }
}
