#include "scanner.h"

Scanner::Scanner(){
  for(unsigned short i = 1; i <= 3010 ; ++i)
    ports.push_back(i);
}

Scanner::~Scanner() {
  for(auto& pt: open_ports_vector) {
    std::cout << "-------------------------" << std::endl
              << "Port " << pt << " is open!"<< std::endl;
  }

  std::cout << "-------------------------" << std::endl
            << "Scan statistics:" << std::endl
            << "\tClosed ports: " << closed_ports << std::endl 
            << "\tOpen   ports: " << open_ports << std::endl;
}

void Scanner::set_target_ip(const char * ip_str) {
  target = std::string(ip_str);
}

void Scanner::init() {
  for(int idx = 0; idx < 5; ++idx) {
    threads[idx] = std::thread(&Scanner::scan,this,idx);
  }

  ready = true;
  cv.notify_all();

  for (auto& th: threads) {
    th.join();
  }
}

unsigned short Scanner::get_port() {
  std::unique_lock<std::mutex> lck(mtx);

  if(ports.empty())
    return 0;

  unsigned short ret = ports.back();
  ports.pop_back();

  return ret;
}

void Scanner::scan(int thread_idx){
  unsigned short port{};

  while((port = get_port())){
    tcp::endpoint ep(address::from_string(target), port);
    tcp::socket socket(io_service);
    boost::system::error_code ec;

    socket.connect(ep,ec);
   
    if(ec) {
      std::unique_lock<std::mutex> out_lck(out_mtx);
      closed_ports++;
    } else {
      std::unique_lock<std::mutex> out_lck(out_mtx);
      open_ports++;
      open_ports_vector.push_back(port);
    }

    socket.close();
  }
}
