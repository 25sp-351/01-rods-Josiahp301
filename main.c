#include <stdio.h>
#include <stdlib.h>

int rodcut(int n, int *p, int* cuts) {
    // Allocate memory for the maxprofit and solution arrays for later on when we want to store the maxprofit and the solution
    int *maxprofit = (int *)malloc((n + 1) * sizeof(int));
    int *solution = (int *)malloc((n + 1) * sizeof(int));
    //checking if memory allocation failed we return -1 for errors
    if (maxprofit == NULL || solution == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    maxprofit[0] = 0;

    //initialize the solution array with zeros to avoid any garbage values and reusing the array 
    for (int j = 1; j <= n; j++) {
        int max_val = -1;
        //looping through the prices array to find the max profit for the length we have
        for (int i = 1; i <= j; i++) {
            if (max_val < p[i] + maxprofit[j - i]) {
                max_val = p[i] + maxprofit[j - i];
                solution[j] = i;
            }
        }
        maxprofit[j] = max_val;
    }

    int length = n;
    //looping through the solution array from the begining to the end to find the cuts made
    while (length > 0) {
        cuts[solution[length]]++;
        length -= solution[length];
    }

    //freeing the allocated memory after the end of the function
    int result = maxprofit[n];
    free(maxprofit);
    free(solution);
    return result;
}

int main(int argc, char *argv[]) {
     if (argc != 2) {
        printf("Usage: %s <supplied rod length>\n", argv[0]);
        return 1;
    }

    // Get the rod length from the command line argument when running the code such as "./rodcut 45"
    int rodlength = atoi(argv[1]);
    int prices[100] = {0}; // Initialize prices array with zeros
    char line[256];

    // Get the prices from the user in pairs like stated in the homework assignment
    printf("Enter the prices in pairs (length price):\n");
    while (fgets(line, sizeof(line), stdin)) {
        int length, price;
        if (sscanf(line, "%d %d", &length, &price) != 2)
            break;
        prices[length] = price;
    }

    // Allocate memory for the cuts array
    int *cuts = (int *)calloc(rodlength + 1, sizeof(int));
    if (cuts == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Call the rodcut function and get the max profit
    int maxprofit = rodcut(rodlength, prices, cuts);

    // Print the results with max profit cuts, and remainder
    printf("Max profit: %d\n", maxprofit);
    printf("Cuts made:\n");
    // Print the cuts made
    for (int i = 1; i <= rodlength; i++) {
        // We are checking the cuts made are more than 0 to avoid using cuts that were not made
        if (cuts[i] > 0) {
            printf("%d pieces of length %d\n", cuts[i], i);
        }
    }

    int remainder = rodlength;
    // Calculate the remaining length which I seem to not be able to get the correct value for needs fixing
    for (int i = 1; i <= rodlength; i++) {
        remainder -= cuts[i] * i;
    }
    printf("Remaining length: %d\n", remainder);
    //freeing up memory used by cuts array
    free(cuts);
    return 0;
}

/* old test cases and old main function that would not work with the new implementation of users input by pairs

#include <stdio.h>
#include <stdlib.h>

int rodcut(int n, int *p) {
    int maxprofit = 0;
    int profit;
    //if given values less than or equal to 0 we need to return 
    if (n == 0)
        return 0;

    for (int i = 1; i <= n; i++) {
        // we are recursivesly calling the function to get the current profit to
        // test against maxprofit
        profit = p[i] + rodcut(n - i, p);

        // changing maxprofit if current profit is greater than maxprofit
        if (profit > maxprofit)
            maxprofit = profit;
    }

    return maxprofit;
}

int main() {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    int length = 8;

    printf("Max profit: %d\n", rodcut(length, prices));

    // 2nd test case
    int new_prices1[] = {1, 1, 2, 4, 7, 11, 13, 24};
    length = 6;

    printf("Max profit: %d\n", rodcut(length, new_prices1));

    // 3rd test case
    int new_prices2[] = {2, 3, 5, 11, 13, 15, 17, 23};
    length = 4;

    printf("Max profit: %d\n", rodcut(length, new_prices2));

    // 4th test case
    int new_prices3[] = {3, 5, 8, 9, 11, 14, 17, 25};
    length = 22;

    printf("Max profit: %d\n", rodcut(length, new_prices3));
}
*/