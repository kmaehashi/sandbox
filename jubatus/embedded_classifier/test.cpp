/* Copyright (C) 2013 Kenichi Maehashi */

#include <iostream>

#include <pficommon/lang/cast.h>
#include <pficommon/text/json.h>

#include <jubatus/classifier/classifier_base.hpp>
#include <jubatus/classifier/classifier_factory.hpp>
#include <jubatus/classifier/classifier_config.hpp>
#include <jubatus/classifier/classifier_type.hpp>
#include <jubatus/common/type.hpp>
#include <jubatus/common/jsonconfig/config.hpp>
#include <jubatus/storage/storage_factory.hpp>

using std::cout;
using std::endl;

using jubatus::classifier::classifier_base;
using jubatus::classifier::classifier_factory;
using jubatus::classifier::classifier_config;
using jubatus::classify_result;
using jubatus::classify_result_elem;
using jubatus::sfv_t;
using jubatus::jsonconfig::config;
using jubatus::storage::storage_base;
using jubatus::storage::storage_factory;

using pfi::lang::lexical_cast;
using pfi::text::json::json;

int main() {
  // param
  config param(lexical_cast<json>("{\"regularization_weight\": 1.0}"));

  // storage
  storage_base* storage = storage_factory::create_storage("local");

  // classifier
  classifier_base* c =
      classifier_factory::create_classifier("AROW", param, storage);

  // fv
  sfv_t d;

  // train
  d.clear();
  d.push_back(std::make_pair("A", 1));
  d.push_back(std::make_pair("B", 1));
  c->train(d, "tokugawa");
  d.clear();
  d.push_back(std::make_pair("B", 1));
  d.push_back(std::make_pair("D", 1));
  c->train(d, "ashikaga");
  d.clear();
  d.push_back(std::make_pair("A", 1));
  d.push_back(std::make_pair("C", 1));
  c->train(d, "hojo");

  // classify
  classify_result scores;
  d.clear();
  d.push_back(std::make_pair("A", 1));
  d.push_back(std::make_pair("D", 1));
  c->classify_with_scores(d, scores);

  for (classify_result::iterator it = scores.begin();
      it != scores.end(); ++it) {
    cout << "[" << it->label << " : " << it->score << "]" << endl;
  }
}
