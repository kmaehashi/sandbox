#include <stdint.h>

typedef void* classifier_handle;

struct pair_sv {
  const char* key;
  const char* value;
};

struct pair_nv {
  const char* key;
  float value;
};

struct datum {
  uint64_t string_values_size;
  struct pair_sv* string_values;

  uint64_t num_values_size;
  struct pair_nv* num_values;
};

struct classify_result_elem {
  const char* label;
  float score;
};

struct classify_result {
  uint64_t size;
  struct classify_result_elem* results;
};

classifier_handle new_classifier(const char* config);
void free_classifier(classifier_handle classifier);
void train(
    classifier_handle classifier,
    const char* label,
    const struct datum d);
struct classify_result classify(
    classifier_handle classifier,
    const struct datum d);
void free_classify_result(struct classify_result result);
