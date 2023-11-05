/**
Let there be N workers and N jobs. Any worker can be assigned to perform
any job with some cost that may vary depending on the work-job assignment.
it is required to perform all jobs by assigning exactly one job to each worker
in such a way that the total cost of the assignment is minimized. 

Input: 
Number of workers and job: N
Cost matrix C with dimension N*N where c(i,j) is the cost incurred on assigning
ith person to jth job. 

Sample input: 
4 
[ 
9 2 7 8
6 4 3 7
5 8 1 8
7 6 9 4
]

Sample Output 13 through worker 1: J2, worker2: J1, worker3:J3, worker4: J4 = 13 
Constraint N <=20 
*/


/**
Find solution 
{j1, j2, ..., jn}
{w1, w2, ..., wn}

1st choice: N options
2nd Choice: N-1 options 
...
Nth Choice: 1 option 

Brute Force: O(N!)
*/

/**
DP 
DP Description: "the cost of every job is the cost of assigning
that job to any of the available workers plus the already calculated cost

"

j1 given {w1, w2, ..., wn} 
    j2 given {w2, w3, ..., wn} + c11
    j2 given {w1, w3, ..., wn} + c21
    .
    .
    .
    j2 given {w1, w2, ..., w n-1} + cn1

dp (i, mask) = min cost job:i->N s.t. people represented by mask

final answer = dp (1, (111111)): first job with all people available

dp (i, mask) = cost ji + dp (i+1, mask | turn jth bit off)
try dp (i, mask) for all valid j and take minimum

valid j: jth bit is on

time (N^2* 2^N) > O(N!)
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 21; // As N<=20, define a constant for array sizes
int cost[MAXN][MAXN]; // Cost matrix
int dp[MAXN][1 << MAXN]; // DP memoization table

// Function to calculate the minimum cost of assigning jobs to workers
int minimum_cost(int i, int mask, int n) {
    if (i == n) return 0; // All workers are assigned a job

    // Return already computed value
    if (dp[i][mask] != -1) return dp[i][mask];

    int answer = INT_MAX;
    // Iterate through all jobs to find the one not assigned
    for (int j = 0; j < n; ++j) {
        if ((mask & (1 << j)) != 0) { // Job j has not been assigned
            // Assign job j to worker i
            answer = min(answer, cost[i][j] + minimum_cost(i + 1, mask & ~(1 << j), n));
        }
    }

    // Store and return the minimum cost for assigning the remaining jobs
    dp[i][mask] = answer;
    return answer;
}

// Function to initialize DP table and start the DP process
int assign_jobs(int n) {
    // Initialize DP table with -1
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            dp[i][j] = -1;
        }
    }

    // Start DP with all jobs available (all bits on)
    return minimum_cost(0, (1 << n) - 1, n);
}

// Function to read the cost matrix and call the assignment function
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cost[i][j];
        }
    }
    int min_cost = assign_jobs(n);
    cout << "The minimum cost is: " << min_cost << endl;
    return 0;
}
