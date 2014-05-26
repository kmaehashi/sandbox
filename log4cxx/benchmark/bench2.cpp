#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

int main() {
  log4cxx::BasicConfigurator::configure();

  for(int i = 0; i < 1000000; ++i) {
    LOG4CXX_INFO(log4cxx::Logger::getLogger("test"), "Test");
  }
}

