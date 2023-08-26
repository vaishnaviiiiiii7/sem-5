#include <stdio.h>
#include <stdlib.h>

// Define the maximum roll number value
#define MAX_ROLL_NO 1000

// Function to count selected students
int countSelectedStudents(int** panelRecommendations, int numPanels, int numStudents) {
    int* studentCounts = (int*)calloc(MAX_ROLL_NO + 1, sizeof(int));
    
    for (int i = 0; i < numPanels; ++i) {
        for (int j = 0; j < numStudents; ++j) {
            studentCounts[panelRecommendations[i][j]]++;
        }
    }
    
    int selectedCount = 0;
    for (int i = 1; i <= MAX_ROLL_NO; ++i) {
        if (studentCounts[i] >= 3) {
            selectedCount++;
        }
    }

    free(studentCounts);
    return selectedCount;
}

int main() {
    // Number of panels and students
    int numPanels = 4;
    int numStudents = 6;

    // Recommended students by each panel
    int* panelRecommendations[] = {
        (int[]){40, 38, 15, 162, 5},
        (int[]){14, 162, 92, 38, 7, 748},
        (int[]){14, 5, 40, 38},
        (int[]){17, 952, 40, 92, 14, 38}
    };

    int selectedCount = countSelectedStudents(panelRecommendations, numPanels, numStudents);

    printf("Number of selected students: %d\n", selectedCount);

    return 0;
}

