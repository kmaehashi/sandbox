#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

int main() {
  log4cxx::BasicConfigurator::configure();
  log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("test");

  for(int i = 0; i < 1000000; ++i) {
    LOG4CXX_INFO(logger, "Test");
  }
}

