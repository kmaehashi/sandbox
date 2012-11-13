#include <jubatus/classifier/classifier_base.hpp>

namespace jubatus {

class my_classifier : public classifier_base {
 public:
  my_classifier();
  ~my_classifier();
  void train(const sfv_t&, const std::string&);
  std::string name() const;
};

}
