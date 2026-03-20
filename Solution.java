import java.util.ArrayList;
import java.util.Arrays;
import java.util.Currency;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Solution {

    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i])) {
                return new int[] { map.get(target - nums[i]), i };
            }
            map.put(nums[i], i);
        }
        return new int[0];
    }

    public List<List<String>> groupAnagrms(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            char[] charArray = str.toCharArray();
            Arrays.sort(charArray);
            String key = new String(charArray);
            List<String> list = map.getOrDefault(key, new ArrayList<String>());
            list.add(str);
            map.put(key, list);
        }
        return new ArrayList<List<String>>(map.values());
    }

    public int longestConsecutive(int[] nums) {
        Set<Integer> set = new HashSet<Integer>();
        for (int num : nums) {
            set.add(num);
        }
        int longest = 0;
        for (int num : nums) {
            if (set.contains(num - 1)) {
                continue;
            }
            int count = 1;
            while (set.contains(num + 1)) {
                count++;
                num++;
            }
            longest = Math.max(longest, count);
        }
        return longest;
    }

    public void moveZeroes(int[] nums) {
        int j = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                j++;
            }
        }

    }

    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int maxTank = 0;
        if (height.length < 3) {
            return 0;
        }
        while (left < right) {
            int currentTank = Math.min(height[left], height[right]) * (right - left);
            maxTank = Math.max(maxTank, currentTank);
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxTank;
    }

    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        Arrays.sort(nums);
        if (nums.length < 3) {
            return ans;
        }
        for (int first = 0; first < nums.length; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {// 为什么要first > 0?
                continue;
            }
            int target = -nums[first];
            int third = nums.length - 1;
            for (int second = first + 1; second < nums.length; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                while (second < third && nums[second] + nums[third] > target) {
                    third--;
                }
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.add(Arrays.asList(nums[first], nums[second], nums[third]));
                }
            }
        }
        return ans;
    }

    public int trap(int[] height){
        int ans = 0;
        int left = 0;
        int right = height.length - 1;
        int leftMax = height[left];
        int rightMax = height[right];
        while (left < right) {
            leftMax = Math.max(leftMax, height[left]);
            rightMax = Math.max(rightMax, height[right]);
            if (leftMax < rightMax) {
                ans += leftMax - height[left++];
            }else{
                ans += rightMax - height[right--];
            }
        }
        return ans;
    }

}
