package homework;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i])) {
                return new int[] { map.get(target - nums[i]), i };
            }
            map.put(nums[i], i);
        }
        return new int[0];
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("in.txt"));
        String numsLine;
        String targetLine;

        while ((numsLine = br.readLine()) != null) {
            targetLine = br.readLine();
            if (targetLine == null) break;

            numsLine = numsLine.trim();
            targetLine = targetLine.trim();

            int[] nums;

            // 第一行为空，表示空数组
            if (numsLine.length() == 0) {
                nums = new int[0];
            } else {
                String[] s = numsLine.split("\\s+");
                nums = new int[s.length];
                for (int i = 0; i < s.length; i++) {
                    nums[i] = Integer.parseInt(s[i]);
                }
            }

            int target = Integer.parseInt(targetLine);

            int[] ans = twoSum(nums, target);
            System.out.println(ans[0] + " " + ans[1]);
        }

        br.close();
    }
}
