//
// test.cpp
// Revl
//
// Created by Oliver Dain on 02/15/2018
// Copyright © 2018 Revl. All rights reserved.
//

#define CATCH_CONFIG_MAIN 1
#include <cassert>
#include <vector>

#include "catch.h"
#include "code.h"

using std::vector;

// Create num_moments unique moments for the video with the given id.
vector<Moment> CreateMoments(int video, int num_moments) {
  assert(video >=0 && video < 2);
  assert(num_moments > 0);
  vector<Moment> result;
  result.reserve(num_moments);
  for (int i = 0; i < num_moments; ++i) {
    result.emplace_back(video, i);
  }
  return result;
}

// Checks a single permutation/edit for validity. Specifically, there must be no duplicate moments and the moments must
// alternate camera views.
void CheckPermuationIsValid(const vector<Moment>& permutation) {
  int last_camera = -1;
  // Put the moments in a set so we'll know how many **unique** moments there are.
  std::set<Moment> unique_moments;

  for (const auto& moment : permutation) {
    if (last_camera >= 0) {
      // We must alternate cameras.
      REQUIRE(moment.video() != last_camera);
    }
    last_camera = moment.video();

    unique_moments.insert(moment);
  }

  // All the moments should be unique so our set of moments should have the same size as the permutation
  REQUIRE(unique_moments.size() == permutation.size());
}

// Checks the full set of permutations for validity. Specifically this checks each individual permutation via calls to
// CheckPermutationIsValid. It also checks that each permutation is unique by putting them in a set (sets don't contain
// duplicate elements).
void CheckAllPermutations(const VectorOfPermutation& permutations) {
  std::set<vector<Moment>> unique_permutations;

  for (const auto permutation : permutations) {
    CheckPermuationIsValid(permutation);
    unique_permutations.insert(permutation);
  }

  REQUIRE(unique_permutations.size() == permutations.size());
}

TEST_CASE("AllPossibleEdits 2 at a time works") {
  auto v1 = CreateMoments(0, 3);
  auto v2 = CreateMoments(1, 2);

  auto permutations = AllPossibleEdits(v1, v2, 2);

  CheckAllPermutations(*permutations);

  // There should be 3 * 2 ways to create an edit with moments from v1 coming first and 2 * 3 ways to make an
  // edit with moments from v2 coming first.
  REQUIRE(permutations->size() == 12);
}

TEST_CASE("AllPossibleEdits 3 at a time works") {
  auto v1 = CreateMoments(0, 5);
  auto v2 = CreateMoments(1, 4);

  auto permutations = AllPossibleEdits(v1, v2, 3);

  CheckAllPermutations(*permutations);

  // There should be 5 * 4 * 4 ways to create an edit with moments from v1 coming first and 4 * 3 * 5 ways to make an
  // edit with moments from v2 coming first.
  REQUIRE(permutations->size() == 140);
}

TEST_CASE("AllPossibleEdits with too few moments works") {
  auto v1 = CreateMoments(0, 7);
  auto v2 = CreateMoments(1, 1);

  auto permutations = AllPossibleEdits(v1, v2, 3);

  CheckAllPermutations(*permutations);

  // With v1's moments coming first there's 7 * 6 * 1 different possible edits. Since there's only one moment in v2 and
  // we'd need two moments from v2 if it came first there aren't any possible edits with v2 first.
  REQUIRE(permutations->size() == 42);
}
