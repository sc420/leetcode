static const int BUCKET_SIZE = 1000;

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    char bits[(250000000 + 1) / BUCKET_SIZE + 1] = {0};
    for (size_t i = 0; i < nums.size(); i++) {
      const int num = nums[i];
      const int nonnegNum = (num + 1000000000) / BUCKET_SIZE;
      // Check if the number exists
      const int bucketIndex = nonnegNum / 8;
      const int offset = nonnegNum % 8;
      if (bits[bucketIndex] & (1 << offset)) {
        // Only knows the bit is set, but we don't know the index
        // So we need to find where the other number is
        const int other = target - num;
        for (size_t otherIndex = 0; otherIndex < nums.size(); otherIndex++) {
          if (nums[otherIndex] == other && i != otherIndex) {
            return {(int)i, (int)otherIndex};
          }
        }
      }

      // Either the bit is not set, or it fails to find the other number
      // We calculate target - num and set the bit for future lookup
      const int other = target - num;
      // Check if the other number is possible
      if (other < (-1000000000) || other > 1000000000) continue;

      const int nonnegOther = (other + 1000000000) / BUCKET_SIZE;
      const int otherBucketIndex = nonnegOther / 8;
      const int otherOffset = nonnegOther % 8;
      bits[otherBucketIndex] |= (1 << otherOffset);
    }
    return {};  // Should not happen
  }
};
