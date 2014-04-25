#include <jubatus/msgpack/rpc/server.h>
#include <jubatus/msgpack/rpc/client.h>

class huge_data_server : public msgpack::rpc::dispatcher {
 public:
  void dispatch(msgpack::rpc::request req) {
    std::string buf;
    for(size_t i = 0; i < 100000; ++i) {
      buf += "0123456789";
    }

    ::sleep(2);
    req.result(buf);
  }

  msgpack::rpc::server& listen(const std::string& host, uint16_t port) {
    m_svr.serve(this);
    m_svr.listen(host, port);
    return m_svr;
  }

 public:
  huge_data_server()
  : m_sp(m_svr.get_loop()) {}

 private:
  msgpack::rpc::server m_svr;
  msgpack::rpc::session_pool m_sp;
};

int main() {
  huge_data_server s;
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) { exit(1); }
  s.listen("0.0.0.0", 9199).run(4);
}
