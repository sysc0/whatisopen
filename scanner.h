#ifndef _SCANNER_H
#define _SCANNER_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

class Scanner {
 public:
  Scanner();
  ~Scanner();
  void init();
  void set_target_ip(const char *ip_str); 
  void scan(int thread_idx);
  unsigned short get_port();

 private:
  boost::asio::io_service io_service;

  bool ready = false;
  std::mutex mtx;
  std::mutex out_mtx;
  std::condition_variable cv;
  std::thread threads[5];

  std::string target;

  int closed_ports{};
  int open_ports{};

  std::vector<unsigned short> open_ports_vector;
  std::vector<unsigned short> ports;
};

#endif // !_SCANNER_H
