#include <stdio.h>

struct Subarray {
    int start;
    int end;
    int sum;
};

struct Subarray maxSubarray(struct Subarray a, struct Subarray b) {
    if (a.sum > b.sum) return a;
    if (b.sum > a.sum) return b;
    return a;
}

struct Subarray maxCrossingSubarray(int arr[], int low, int mid, int high, int constraint) {
    int left_sum = 0, right_sum = 0;
    int sum = 0, i;
    int best_left = -1, best_right = -1;

    sum = 0;
    for (i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum <= constraint && sum > left_sum) {
            left_sum = sum;
            best_left = i;
        }
    }

    sum = 0;
    for (i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum <= constraint && sum > right_sum) {
            right_sum = sum;
            best_right = i;
        }
    }

    struct Subarray result;
    if (best_left != -1 && best_right != -1 && left_sum + right_sum <= constraint) {
        result.start = best_left;
        result.end = best_right;
        result.sum = left_sum + right_sum;
    } else {
        result.start = -1;
        result.end = -1;
        result.sum = 0;
    }
    return result;
}

struct Subarray maxSubarrayDC(int arr[], int low, int high, int constraint) {
    if (low == high) {
        struct Subarray base;
        if (arr[low] <= constraint) {
            base.start = low;
            base.end = low;
            base.sum = arr[low];
        } else {
            base.start = -1;
            base.end = -1;
            base.sum = 0;
        }
        return base;
    }

    int mid = (low + high) / 2;
    struct Subarray left = maxSubarrayDC(arr, low, mid, constraint);
    struct Subarray right = maxSubarrayDC(arr, mid + 1, high, constraint);
    struct Subarray cross = maxCrossingSubarray(arr, low, mid, high, constraint);

    struct Subarray best = maxSubarray(left, right);
    best = maxSubarray(best, cross);

    return best;
}

int main() {
    int n, constraint;
    printf("Enter the size of array:\n");
    scanf("%d", &n);

    int resources[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the %d index element of the array:\n", i);
        scanf("%d", &resources[i]);
    }

    printf("The arrays is {");
    for (int i = 0; i < n; i++) {
        printf("%d",resources[i]);
    }
    printf("}.\n");

    

    printf("Enter the size of constraint:\n");
    scanf("%d", &constraint);

    if (n == 0 || constraint <= 0) {
        printf("No feasible subarray.\n");
        return 0;
    }

    struct Subarray result = maxSubarrayDC(resources, 0, n - 1, constraint);

    if (result.start == -1) {
        printf("No feasible subarray.\n");
    } else {
        printf("Best subarray (indices %d to %d): ", result.start, result.end);
        for (int i = result.start; i <= result.end; i++) {
            printf("%d ", resources[i]);
        }
        printf("\nMaximum sum = %d\n", result.sum);
    }

    return 0;
}
