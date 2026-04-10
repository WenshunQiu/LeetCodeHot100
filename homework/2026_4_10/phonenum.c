#include <stdio.h>
#include <string.h>

int main() {
    char digits[5]; // 最多4个数字 + '\0'
    if (scanf("%s", digits) != 1) return 0;

    // 1. 定义映射表 (索引 0-9)
    const char *map[] = {
        "", "", "abc", "def", "ghi", "jkl", 
        "mno", "pqrs", "tuv", "wxyz"
    };

    int len = strlen(digits);
    
    const char *s0 = map[digits[0] - '0'];
    const char *s1 = (len > 1) ? map[digits[1] - '0'] : "";
    const char *s2 = (len > 2) ? map[digits[2] - '0'] : "";
    const char *s3 = (len > 3) ? map[digits[3] - '0'] : "";

    // 2. 根据长度进行嵌套循环
    for (int i = 0; s0[i] != '\0'; i++) {
        if (len == 1) {
            printf("%c\n", s0[i]);
            continue;
        }
        for (int j = 0; s1[j] != '\0'; j++) {
            if (len == 2) {
                printf("%c%c\n", s0[i], s1[j]);
                continue;
            }
            for (int k = 0; s2[k] != '\0'; k++) {
                if (len == 3) {
                    printf("%c%c%c\n", s0[i], s1[j], s2[k]);
                    continue;
                }
                for (int l = 0; s3[l] != '\0'; l++) {
                    if (len == 4) {
                        printf("%c%c%c%c\n", s0[i], s1[j], s2[k], s3[l]);
                    }
                }
            }
        }
    }

    return 0;
}