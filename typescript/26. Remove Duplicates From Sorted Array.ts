function removeDuplicates(nums: number[]): number {
  let k: number = 0;
  for (let i = 0; i < nums.length; i++) {
    if (nums[i] == nums[i + 1]) {
      k++;
    }
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
 * */
