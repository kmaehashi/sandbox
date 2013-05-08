#include "classifier.hpp"

#include <jubatus/classifier/classifier_type.hpp>

extern "C" {

#include "classifier.h"

jubatus::fv_converter::datum unpack_datum(const struct datum d) {
  jubatus::fv_converter::datum d2;
  for (int i = 0; i < d.string_values_size; ++i) {
    pair_sv p = d.string_values[i];
    d2.string_values_.push_back(std::make_pair(p.key, p.value));
  }
  for (int i = 0; i < d.num_values_size; ++i) {
    pair_nv p = d.num_values[i];
    d2.num_values_.push_back(std::make_pair(p.key, p.value));
  }
  return d2;
}

const struct classify_result pack_classify_result(jubatus::classify_result r) {
  struct classify_result r2;
  int count = r.size();

  r2.size = count;
  r2.results = (classify_result_elem*) malloc(sizeof(classify_result_elem) * count);
  for (int i = 0; i < count; ++i) {
    r2.results[i].label = r[i].label.c_str();
    r2.results[i].score = r[i].score;
  }
  return r2;
}

/* Public APIs */

classifier_handle new_classifier(const char* config) {
  return new jubatus::embedded::classifier(config);
}

void free_classifier(classifier_handle classifier) {
  delete static_cast<jubatus::embedded::classifier*>(classifier);
}

void train(classifier_handle classifier, const char* label, const struct datum d) {
  (static_cast<jubatus::embedded::classifier*>(classifier))->train(
      std::make_pair(label, unpack_datum(d)));
}

struct classify_result classify(classifier_handle classifier, const struct datum d) {
  return pack_classify_result(
      (static_cast<jubatus::embedded::classifier*>(classifier))->classify(
          unpack_datum(d)));
}

void free_classify_result(struct classify_result result) {
  free(result.results);
}

}  // extern "C"
