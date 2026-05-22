#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    long long A, B, Q, X0;
    if (scanf("%d %d %lld %lld %lld %lld", &n, &m, &A, &B, &Q, &X0) != 6)
    {
        return 0;
    }

    int rows = n - 1;          // state count per column
    int hRows = n - 2;         // horizontal rows
    int hCols = m - 1;         // horizontal boundaries between columns

    vector<uint32_t> vert((size_t)rows * (size_t)m);
    vector<uint32_t> hori((size_t)hRows * (size_t)hCols);

    long long cur = X0;
    auto nextX = [&]() -> uint32_t
    {
        cur = (A * cur + B) % Q;    // Xi+1
        return (uint32_t)cur;       // use X1, X2, ...
    };

    // Vertical capacities: X1 .. X((n-1)*m)
    // X((s-1)*m + t) => edge (s,t) -> (s+1,t)
    for (int s = 1; s <= n - 1; s++)
    {
        for (int t = 1; t <= m; t++)
        {
            vert[(size_t)(t - 1) * rows + (s - 1)] = nextX();
        }
    }

    // Horizontal capacities in rows 2..n-1:
    // X((n-1)*m + (s-2)*(m-1) + t) => edge (s,t) <-> (s,t+1)
    for (int s = 2; s <= n - 1; s++)
    {
        for (int t = 1; t <= m - 1; t++)
        {
            hori[(size_t)(s - 2) * hCols + (t - 1)] = nextX();
        }
    }

    const long long INF = (1LL << 62);

    // dp[r]: minimum cut value up to current column, with boundary at row r (1..n-1)
    vector<long long> dp(rows + 1, INF), ndp(rows + 1, INF);

    // Column 1 unary cost
    for (int r = 1; r <= rows; r++)
    {
        dp[r] = vert[(size_t)0 * rows + (r - 1)];
    }

    vector<long long> pref(rows + 1, 0), leftVal(rows + 1, INF), rightVal(rows + 1, INF);

    // Transition across boundaries col = 1..m-1
    for (int col = 1; col <= m - 1; col++)
    {
        // pref[r] = sum of horizontal capacities at this boundary from row 2..r
        // pref[1] = 0
        pref[1] = 0;
        for (int r = 2; r <= rows; r++)
        {
            pref[r] = pref[r - 1] + hori[(size_t)(r - 2) * hCols + (col - 1)];
        }

        // g[b] = min_a (dp[a] + |pref[a] - pref[b]|)
        long long best = INF;
        for (int r = 1; r <= rows; r++)
        {
            best = min(best, dp[r] - pref[r]);
            leftVal[r] = best + pref[r];
        }

        best = INF;
        for (int r = rows; r >= 1; r--)
        {
            best = min(best, dp[r] + pref[r]);
            rightVal[r] = best - pref[r];
        }

        // Add unary cost of next column (col+1)
        for (int r = 1; r <= rows; r++)
        {
            long long trans = min(leftVal[r], rightVal[r]);
            ndp[r] = trans + vert[(size_t)col * rows + (r - 1)];
        }

        dp.swap(ndp);
    }

    long long ans = dp[1];
    for (int r = 2; r <= rows; r++)
    {
        ans = min(ans, dp[r]);
    }

    printf("%lld\n", ans);
    return 0;
}
