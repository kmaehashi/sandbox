/*
 Jubatus In-Process Classifier Wrapper
 Copyright (C) 2013 Kenichi Maehashi
*/

#include <jubatus/driver/classifier.hpp>
#include <jubatus/classifier/classifier_type.hpp>

#include <jubatus/fv_converter/datum.hpp>
#include <jubatus/fv_converter/datum_to_fv_converter.hpp>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/text/json.h>

namespace jubatus {
namespace embedded {

struct server_config {
  std::string method;
  pfi::data::optional<pfi::text::json::json> parameter;
  pfi::text::json::json converter;

  template<typename Ar>
  void serialize(Ar& ar) {
    ar & MEMBER(method) & MEMBER(parameter) & MEMBER(converter);
  }
};

class classifier {
 public:
  classifier(const std::string& config);
  void train(const std::pair<std::string, jubatus::fv_converter::datum>& data);
  classify_result classify(const jubatus::fv_converter::datum& d);

 private:
  pfi::lang::shared_ptr<jubatus::driver::classifier> driver_;
  pfi::lang::shared_ptr<jubatus::framework::mixer::mixer> mixer_;
};

}  // namespace embedded
}  // namespace jubatus
