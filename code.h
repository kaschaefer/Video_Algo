//
// code.h
// Revl
//
// Created by Oliver Dain on 02/15/2018
// Copyright © 2018 Revl. All rights reserved.
//

#ifndef _USERS_OLIVERDAIN_DOCUMENTS_CODE_CPP_CHALLENGE_CODE_H_
#define _USERS_OLIVERDAIN_DOCUMENTS_CODE_CPP_CHALLENGE_CODE_H_

#include <cassert>
#include <memory>
#include <ostream>
#include <vector>

// This is a single moment that one of our machine learning algorithms found. A real moment would indicate the video
// that it comes from, a start time and end time, the type of moment, etc. For simplicity here we instead give each
// moment a unique id.
//
// The moments implement operator== and operator< so we can put them in a std::set, compare them, etc. in tests.
class Moment {
 public:
  // Construct a moment.
  //
  // Arguments:
  //   video: the index of the video from which the moment comes. 0 for the 1st video and 1 for the 2nd.
  //   moment_id: a unique identifier for the moment.
  Moment(int video, int moment_id) : video_(video), moment_id_(moment_id) {
    assert(video >= 0 && video < 2);
    assert(moment_id >= 0);
  }

  int video() const {
    return video_;
  }

  int moment_id() const {
    return moment_id_;
  }

  // Moments are equal if they have the same id and are from the same video.
  bool operator==(const Moment& other) const {
    return video() == other.video() && moment_id() == other.moment_id();
  }

  // This is implemented so we can store the moments in a std::set to easily find out how many unique moments were in a
  // permutation. It just sorts lexicographically by (video, moment_id).
  bool operator<(const Moment& other) const {
    if (video() < other.video()) {
      return true;
    } else if (other.video() < video()) {
      return false;
    } else {
      return moment_id() < other.moment_id();
    }
  }

 private:
  int video_;
  int moment_id_;
};


using VectorOfPermutation = std::vector<std::vector<Moment>>;
using PtrToVectorOfPermutation = std::unique_ptr<VectorOfPermutation>;

// Convenience implementation of operator<< so you can log these for debugging.
inline std::ostream& operator<<(std::ostream& out, const Moment& moment) {
  out << "Moment(" << moment.video() << ", " << moment.moment_id() << ")";
  return out;
}

// Convenience implementation of operator<< so you can log these for debugging.
inline std::ostream& operator<<(std::ostream& out, const std::vector<Moment>& permuation) {
  out << "Permuation: [ ";
  bool need_space = false;
  for (const auto& m : permuation) {
    if (need_space) {
      out << " ";
    }
    need_space = true;
    out << m;
  }
  out << " ]";
  return out;
}

// This is the method you need to implement.
//
// Arguments:
//   camera_one_moments: the list of moments our algorithms found in the first video.
//   camera_two_moments: the list of moments our algorithms found in the second video.
//   k: the number of moments we want in the final video edit. You can assume this will only be called with k >= 2.
PtrToVectorOfPermutation AllPossibleEdits(
    const std::vector<Moment>& camera_one_moments,
    const std::vector<Moment>& camera_two_moments,
    int k);

#endif  // _USERS_OLIVERDAIN_DOCUMENTS_CODE_CPP_CHALLENGE_CODE_H_
