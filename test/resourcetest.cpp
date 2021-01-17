#include "vendor/catch.hpp"
#include "../src/assets/resourcemanager.hpp"

#include <optional>

class MockResource : public laika3d::Resource {
  public:
    MockResource(const std::string& file_path) {}
};

TEST_CASE("Does not return pointers for missing files", "[resource]") {
  using namespace laika3d;
  ResourceManager rm;
  REQUIRE(!(rm.load<Texture>("missing_file.txt")));
  REQUIRE(!(rm.load<Mesh>("missing_file.txt")));
}

TEST_CASE("Can add resources to resource manager", "[resource]") {
  using namespace laika3d;
  ResourceManager rm;
  auto foo = rm.load<MockResource>("foo");
  auto bar = rm.load<MockResource>("bar");
  REQUIRE(rm.get_resource_count() == 2);
}

TEST_CASE("Does not duplicate the same resources", "[resource]") {
  using namespace laika3d;
  ResourceManager rm;
  auto foo1 = rm.load<MockResource>("foo");
  auto foo2 = rm.load<MockResource>("foo");
  REQUIRE(rm.get_resource_count() == 1);
  REQUIRE(foo1->use_count() == 3); // two for these two references, one for the manager itself
}
