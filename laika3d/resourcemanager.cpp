#include "resourcemanager.hpp"

using namespace laika3d;

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

template<typename T>
std::optional<std::shared_ptr<T>> ResourceManager::load(const std::string& path) {
  std::shared_ptr<T> res;

  if (resources.find(path) != res.end()) {
    res = std::dynamic_pointer_cast<T>(res[path]);
    
    // res will be a null pointer if the path does not refer to the resource type requested
    if (!res) {
      return {};
    }

    cleanup();
  }
  else {
    cleanup();
    try {
      res = std::make_shared<T>(path);
    }
    catch (std::exception e) {
      return {};
    }

    resources[path] = std::static_pointer_cast<Resource>(res);
  }

  return res;
}
