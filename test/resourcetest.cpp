#include "vendor/catch.hpp"
#include "../src/assets/resourcemanager.hpp"

#include <optional>

TEST_CASE("Does not return pointers for missing files", "[resource]") {
  using namespace laika3d;
  ResourceManager rm;
  REQUIRE(!(rm.load<Texture>("missing_file.txt")));
  REQUIRE(!(rm.load<Mesh>("missing_file.txt")));
}

TEST_CASE("Can add resources to resource manager", "[resource]") {
  using namespace laika3d;
  ResourceManager rm;
}