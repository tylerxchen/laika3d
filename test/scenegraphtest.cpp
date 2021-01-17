#include "vendor/catch.hpp"
#include "../src/scene/scene.hpp"
#include "../src/scene/transformationnode.hpp"

TEST_CASE("Can add nodes to root", "[scene_graph]") {
  using namespace laika3d;
  Scene test_scene;
  test_scene.add_node("root", std::make_shared<TransformationNode>("test_node1"));
  test_scene.add_node("root", std::make_shared<TransformationNode>("test_node2"));

  REQUIRE(test_scene.find_node("root"));
  REQUIRE(test_scene.find_node("root")->get_child_count() == 2);
  REQUIRE(test_scene.find_node("test_node1"));
  REQUIRE(test_scene.find_node("test_node2"));
}

TEST_CASE("Can add nodes in a list", "[scene_graph]") {
  using namespace laika3d;
  Scene test_scene;
  test_scene.add_node("root", std::make_shared<TransformationNode>("test_node1"));
  test_scene.add_node("test_node1", std::make_shared<TransformationNode>("test_node2"));

  REQUIRE(test_scene.find_node("root"));
  REQUIRE(test_scene.find_node("test_node1"));
  REQUIRE(test_scene.find_node("test_node2"));
}

TEST_CASE("Can delete nodes", "[scene_graph]") {
  using namespace laika3d;
  Scene test_scene;
  test_scene.add_node("root", std::make_shared<TransformationNode>("test_node1"));
  test_scene.add_node("test_node1", std::make_shared<TransformationNode>("test_node2"));
  test_scene.delete_subtree("test_node1");

  REQUIRE(test_scene.find_node("root"));
  REQUIRE(test_scene.find_node("root")->get_child_count() == 0);
}
