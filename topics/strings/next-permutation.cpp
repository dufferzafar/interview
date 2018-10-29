/**
 * Microsoft
 *
 * https://www.interviewbit.com/problems/next-permutation/
 */

void Solution::nextPermutation(vector<int> &arr) {

    int n = arr.size();

    // Find the first number that is smaller than the one on its right
    int pvt = -1;
    for(int i = n-2; i >= 0; --i) {
        if (arr[i] < arr[i+1]) {
            pvt = i;
            break;
        }
    }

    // If there is no such number, the array is sorted in decreasing order
    if (pvt == -1)
    {
        sort(begin(arr), end(arr));
        return;
    }

    else
    {
        // Smallest number to right of pivot greater than pivto!
        int ci = pvt + 1;
        for(int i = ci; i < n; ++i) {
            if (arr[i] < arr[ci] && arr[pvt] < arr[i]) {
                ci = i;
            }
        }

        swap(arr[ci], arr[pvt]);
        sort(begin(arr)+pvt+1, end(arr));
    }

}
