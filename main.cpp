#include <iostream>
#include <regex>
#include <memory>
#include "scanner.h"

void usage() {
  std::cerr << "usage: ./whatisopen <ip address>" << std::endl;
}

int main(int argc, char *argv[]) {
  
  //check if the programs has the right amount of arguments
  if(argc < 2) {
    usage();
    return 1;
  }
  
  //regex to check if the ip is valid
  if(!std::regex_match(argv[1],
      std::regex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
    ))
  {  
    usage();
    return 2;
  }
  std::unique_ptr<Scanner> snc(new Scanner);
  snc->set_target_ip(argv[1]);
  snc->init();

  return 0;
}
