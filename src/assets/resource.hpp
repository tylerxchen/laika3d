#pragma once

namespace laika3d {
  // this is just a dummy polymorphic base to allow for dynamic casts
  class Resource {
    public:
      virtual ~Resource() = 0;
  };
}

inline laika3d::Resource::~Resource() {}
