#include <cstddef>
#include <cstdint>
#include <string>

#include "testing/fuzzing/fuzztest.h"
#include "third_party/absl/strings/str_cat.h"
#include "third_party/diff/diff.h"

void DiffFuzzerTest(size_t n, const std::string& data) {
  const size_t size = data.size();
  std::string tokens1, tokens2;
  if (size == 0) {
    // Leave tokens1 and tokens2 empty
  } else if (size == 1) {
    tokens1 = data;
  } else if (size == 2) {
    tokens2 = data;
  } else if (size < 9) {
    // Create two token strings that overlap at least once every 3rd character.
    // and otherwise only 1/256 of the time.
    auto iter = data.begin();
    for (int k = 0;; ++k, k %= 3) {
      const char s = *iter++;
      if (iter == data.end()) break;
      if (k != 0) tokens1.push_back(s);
      if (k != 1) tokens2.push_back(s);
    }
  } else {
    n %= data.size();
    tokens1 = data.substr(0, n);
    tokens2 = data.substr(n);
  }

  // Avoid test timeouts by limiting token sizes.
  // The run time is O(N * D) where N = tokens1.size() + tokens2.size() and
  // D = size of the vector returned by ::third_party::diff::GetTokenDiffs.
  // We don't know D in advance, but the worst-case case is O(N log N + D^2)
  // where D ~ sqrt(tokens1.size() * tokens2.size()) for random inputs.
  // See https://neil.fraser.name/writing/diff/myers.pdf for details.
  constexpr size_t kMax = 100000000ULL;
  if (tokens1.size() > kMax || tokens2.size() > kMax) return;
  if (tokens1.size() * tokens2.size() > kMax) return;

  ::third_party::diff::GetTokenDiffs(&tokens1[0], &tokens1[tokens1.size()],
                                     &tokens2[0], &tokens2[tokens2.size()]);
}
FUZZ_TEST(DiffFuzzerTestSuite, DiffFuzzerTest)
    .WithSeeds({{0, ""},
                {1, "x"},
                {2, "xx"},
                {3, "xxx"},
                {5, "ab"},
                {12, "abcdefghijkl"},
                {10, "abcdefghijklmnopqrstuvwxyz"}});
