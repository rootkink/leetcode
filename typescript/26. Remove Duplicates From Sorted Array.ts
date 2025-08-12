function removeDuplicates(nums: number[]): number {
  let k = Array.from(new Set(nums));
  for (let i = 0; i < nums.length; i++) {
    nums[i] = k[i];
  }
  return k;
}

/*
 * How do we check for duplicates using hashmap?
 * 1.we get array and loop each element
 * 2. we check if it exist in hash map return true yes  not
 * 3. if not, insert it into hashmap
 *
 * what different here,
 * we need return no. of duplicate element (k) that are there in array.
 * what we can do same logic we will just insert unique no. in hashmap it already exist we will increment k
 *
 *
 *
 * another messed up idea can be
 * i insert all element into set and just subtract set size from array length
 * it will also return
 *
 *
 * 1. attempt one (failed)
 * leetcode mf, also check for end state of array so it failed i need remoce Duplicates from nums
 *
 * 2. attempt two(passed)
 * create sallow copy set of nums then insert nums it nums since question does care about other position it doesnt matter
 * return k;
 *
 * could have been better like i could have used two pointers * */
