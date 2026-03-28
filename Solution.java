import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.net.ssl.SSLContext;
import javax.swing.LayoutStyle;

class Solution {

    public int[] twoSum(int[] nums, int target) {// 两数之和
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i])) {
                return new int[] { map.get(target - nums[i]), i };
            }
            map.put(nums[i], i);
        }
        return new int[0];
    }

    public List<List<String>> groupAnagrms(String[] strs) {// 字母异位词分组
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

    public int longestConsecutive(int[] nums) {// 最长连续序列
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

    public void moveZeroes(int[] nums) {// 移动零
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

    public int maxArea(int[] height) {// 可以盛最多水的容器
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

    public List<List<Integer>> threeSum(int[] nums) {// 三数之和
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

    public int trap(int[] height) {// 接雨水
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
            } else {
                ans += rightMax - height[right--];
            }
        }
        return ans;
    }

    public int lenthOfLongestSubsting(String s) {// 无重复字符的最长子串
        char[] chars = s.toCharArray();
        Set<Character> set = new HashSet<>();
        int left = 0;
        int ans = 0;
        for (int right = 0; right < chars.length; right++) {
            while (set.contains(chars[right])) {
                set.remove(chars[left]);
                left++;
            }
            set.add(chars[right]);
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }

    // 下面的better，因为left直接跳转了
    public int lengthOfLongestSubstring(String s) {
        Map<Character, Integer> map = new HashMap<>();// 记录字母最后出现的位置
        int left = 0, ans = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            if (map.containsKey(c)) {
                left = Math.max(left, map.get(c) + 1);
            }
            map.put(c, right);
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }

    public List<Integer> findAnagrams(String s, String p) {// 找到字符串中所有字母异位词
        int n = s.length();
        int m = p.length();
        List<Integer> ans = new ArrayList<>();
        if (n < m)
            return ans;
        int[] pCnt = new int[26];
        int[] sCnt = new int[26];
        for (int i = 0; i < m; i++) {// 初始化，异位词比较本质可以看作字母出现的次数
            pCnt[p.charAt(i) - 'a']++;// 统计p中字母次数

            sCnt[s.charAt(i) - 'a']++;// 初始化第一个窗格
        }
        if (Arrays.equals(sCnt, pCnt)) {
            ans.add(0);
        }
        for (int i = 0; i < n - m; i++) {// 这里开始移动窗格
            sCnt[s.charAt(i) - 'a']--;
            sCnt[s.charAt(i + m) - 'a']++;
            if (Arrays.equals(sCnt, pCnt)) {
                ans.add(i + 1);
            }
        }
        return ans;
    }

    public int subarraySum(int[] nums, int k) {// 和为k的子数组
        Map<Integer, Integer> map = new HashMap<>();// 用来存储前缀和
        map.put(0, 1);
        int preSum = 0;
        int ans = 0;
        for (int i = 0; i < nums.length; i++) {
            preSum += nums[i];
            if (map.containsKey(preSum - k))// 我们要找到前缀和为preSum - k的子数组;
                // 得到子数组后，获取这个子数组的值，在hashmap中获取获取子数组的个数.
                ans += map.get(preSum - k);
            map.put(preSum, map.getOrDefault(preSum, 0) + 1);// 对这个子数组的个数加一.
        }
        return ans;
    }

    public int[] maxSlidingWindow(int[] nums, int k) {
        int len = nums.length;
        int[] ans = new int[len - k + 1];
        Deque<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < len; i++) {

            // -----------------维护队列-----------------
            while (!q.isEmpty() && nums[q.getLast()] <= nums[i]) {
                q.removeLast();
            } // 队列中元素小于当前元素的都会被弹出
            q.addLast(i);// 当前元素加入队列
            if (i - q.getFirst() >= k) {// 最大元素已经不在窗口内了，就弹出
                q.removeFirst();
            }
            // -----------------维护队列-----------------

            // -----------------取值-----------------
            if (i >= k - 1) {// 窗口稳定后取值
                ans[i - k + 1] = nums[q.getFirst()];
            }
            // -----------------取值-----------------
        }
        return new int[6];
    }

    public String minWindow(String S, String T) {
        char[] s = S.toCharArray();
        char[] t = T.toCharArray();
        int len = s.length;
        int[] sCnt = new int[123];
        int[] tCnt = new int[123];
        int ansl = -1;
        int ansr = len;
        int l = 0;
        int exNum = 0;// 统计不同字符种类数
        for (char a : t) {
            if (tCnt[a] == 0) {
                exNum++;
            }
            tCnt[a]++;
        }
        for (int r = 0; r < len; r++) {
            char ch = s[r];
            sCnt[ch]++;
            if (sCnt[ch] == tCnt[ch]) {
                exNum--;
            }
            while (exNum == 0) {//使用不同字符种类数就可以不用遍历对比是否满足了。
                if (r - l < ansr - ansl) {  
                    ansr = r;
                    ansl = l;
                }
                char b = s[l++];
                if (sCnt[b]-- == tCnt[b] ) {//移动左指针，如果移出的字母属于tCnt的字母，则exNum++，并减少对应的字符数。
                    exNum++;
                }
            }
        }
        return ansl >= 0 ? "" : S.substring(ansl, ansr + 1);
    }

}
