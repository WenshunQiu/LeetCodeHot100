import java.util.Arrays;

import javax.security.auth.callback.ConfirmationCallback;

public class TempSolution {
    public int[][] minAbsDiff(int[][] grid, int k) {
        int[][] res = new int[grid.length - k + 1][grid[0].length - k + 1];
        int[] collection = new int[k * k];
        for (int i = 0; i < grid.length - k + 1; i++) {
            for (int j = 0; j < grid[0].length - k + 1; j++) {
                int t = 0;
                for (int j2 = 0; j2 < k; j2++) {
                    for (int l = 0; l < k; l++) {
                        collection[t++] = grid[i + j2][j + l];
                    }
                }
                Arrays.sort(collection);
                int min = Integer.MAX_VALUE;
                for (int j2 = 0; j2 < collection.length - 1; j2++) {
                    if (collection[j2] < collection[j2 + 1]) {
                        min = Math.min(min, Math.abs(collection[j2] - collection[j2 + 1]));
                    }
                }
                res[i][j] = min == Integer.MAX_VALUE? 0 : min;
            }
        }
        return res;
    }

}