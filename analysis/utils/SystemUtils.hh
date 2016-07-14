#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <algorithm>

class SystemUtils {

public:

  SystemUtils();
  ~SystemUtils();
  
  static std::string exec(const std::string& cmd);

};
