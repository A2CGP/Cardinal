#include <glog/logging.h>

#include "platform/platform.h"

int main() {
  FLAGS_logtostdout = true;
  FLAGS_colorlogtostdout = true;
  google::InitGoogleLogging("Cardinal");

  Cardinal::Application app;
  Cardinal::Platform platform;

  platform.Run(&app);

  return 0;
}