#ifndef DIALOG_COLUMN_H_
#define DIALOG_COLUMN_H_

#include <string>
#include <cstdint>

#include "value.h"
#include "field.h"
#include "index_state.h"
#include "string_utils.h"

namespace dialog {

struct column_t {
 public:
  column_t()
      : idx_(UINT16_MAX),
        type_(),
        offset_(UINT16_MAX) {
  }

  column_t(uint16_t idx, uint16_t offset, const data_type& type,
           const std::string& name, const numeric_t& min, const numeric_t& max)
      : idx_(idx),
        type_(type),
        offset_(offset),
        name_(string_utils::to_upper(name)),
        min_(min),
        max_(max) {
  }

  column_t(const column_t& other)
      : idx_(other.idx_),
        type_(other.type_),
        offset_(other.offset_),
        name_(other.name_),
        min_(other.min_),
        max_(other.max_),
        idx_state_(other.idx_state_) {
  }

  std::string name() const {
    return name_;
  }

  const data_type& type() const {
    return type_;
  }

  uint16_t offset() const {
    return offset_;
  }

  uint16_t idx() const {
    return idx_;
  }

  numeric_t min() const {
    return min_;
  }

  numeric_t max() const {
    return max_;
  }

  uint16_t index_id() const {
    return idx_state_.id();
  }

  double index_bucket_size() const {
    return idx_state_.bucket_size();
  }

  bool is_indexed() const {
    return idx_state_.is_indexed();
  }

  bool set_indexing() {
    return idx_state_.set_indexing();
  }

  void set_indexed(uint16_t index_id, double bucket_size) {
    idx_state_.set_indexed(index_id, bucket_size);
  }

  void set_unindexed() {
    idx_state_.set_unindexed();
  }

  bool disable_indexing() {
    return idx_state_.disable_indexing();
  }

  field_t apply(const void* data) const {
    return field_t(idx_, type_,
                   reinterpret_cast<const unsigned char*>(data) + offset_,
                   is_indexed(), idx_state_.id(), idx_state_.bucket_size());
  }

 private:
  uint16_t idx_;
  data_type type_;
  uint16_t offset_;
  std::string name_;
  numeric_t min_;
  numeric_t max_;
  index_state_t idx_state_;
};

}

#endif /* DIALOG_COLUMN_H_ */