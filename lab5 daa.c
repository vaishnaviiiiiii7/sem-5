#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct person
struct person {
int id;
char *name;
int age;
int height;
int weight;
};

// Function to swap two person structures
void swap(struct person *a, struct person *b) {
struct person temp = *a;
*a = *b;
*b = temp;
}

// Function to create a Min-Heap based on age
void min_heapify_age(struct person arr[], int n, int i) {
int smallest = i;
int left = 2 * i + 1;
int right = 2 * i + 2;

if (left < n && arr[left].age < arr[smallest].age)
smallest = left;

if (right < n && arr[right].age < arr[smallest].age)
smallest = right;

if (smallest != i) {
swap(&arr[i], &arr[smallest]);
min_heapify_age(arr, n, smallest);
}
}

// Function to create a Max-Heap based on weight
void max_heapify_weight(struct person arr[], int n, int i) {
int largest = i;
int left = 2 * i + 1;
int right = 2 * i + 2;

if (left < n && arr[left].weight > arr[largest].weight)
largest = left;

if (right < n && arr[right].weight > arr[largest].weight)
largest = right;

if (largest != i) {
swap(&arr[i], &arr[largest]);
max_heapify_weight(arr, n, largest);
}
}

// Function to display the weight of the youngest person
void display_youngest_weight(struct person arr[], int n) {
if (n == 0) {
printf("Heap is empty.\n");
return;
}
printf("Weight of youngest student: %.2f kg\n", arr[0].weight / 2.20462);
}

int main() {
struct person *students = NULL;
int n = 0; // Number of students

while (1) {
printf("MAIN MENU (HEAP)\n");
printf("1. Read Data\n");
printf("2. Create a Min-heap based on the age\n");
printf("3. Create a Max-heap based on the weight\n");
printf("4. Display weight of the youngest person\n");
printf("5. Insert a new person into the Min-heap\n");
printf("6. Delete the oldest person\n");
printf("7. Exit\n");

int option;
printf("Enter option: ");
scanf("%d", &option);

switch (option) {
case 1:
// Read Data
{
char filename[100];
printf("Enter the filename to read data: ");
scanf("%s", filename);

FILE *file = fopen(filename, "r");
if (!file) {
printf("Error opening file.\n");
continue;
}

fscanf(file, "Id Name Age Height Weight(pound)\n");
while (fscanf(file, "%d %s %d %*d %d", &students[n].id, students[n].name, &students[n].age, &students[n].weight) != EOF) {
// Allocate memory for the name and copy it
students[n].name = strdup(students[n].name);
n++;
}

fclose(file);
printf("Data read successfully.\n");
}
break;
case 2:
// Create a Min-heap based on age
if (n > 0) {
for (int i = n / 2 - 1; i >= 0; i--) {
min_heapify_age(students, n, i);
}
printf("Min-heap based on age created.\n");
} else {
printf("No data to create a heap.\n");
}
break;
case 3:
// Create a Max-heap based on weight
if (n > 0) {
for (int i = n / 2 - 1; i >= 0; i--) {
max_heapify_weight(students, n, i);
}
printf("Max-heap based on weight created.\n");
} else {
printf("No data to create a heap.\n");
}
break;
case 4:
// Display weight of the youngest person
display_youngest_weight(students, n);
break;
case 5:
// Insert a new person into the Min-heap
if (n < 500) { // Assuming a maximum of 500 students
struct person new_person;
new_person.name = (char *)malloc(100);
printf("Enter new person's details (Name Age Weight): ");
scanf("%s %d %d", new_person.name, &new_person.age, &new_person.weight);

students[n] = new_person;
n++;
printf("New person inserted into the Min-heap.\n");

// Re-heapify
for (int i = n / 2 - 1; i >= 0; i--) {
min_heapify_age(students, n, i);
}
} else {
printf("Heap is full. Cannot insert more students.\n");
}
break;
case 6:
// Delete the oldest person (root of Min-heap)
if (n > 0) {
free(students[0].name);
students[0] = students[n - 1];
n--;

// Re-heapify
for (int i = n / 2 - 1; i >= 0; i--) {
min_heapify_age(students, n, i);
}
printf("Oldest person deleted from the Min-heap.\n");
} else {
printf("Heap is empty. Cannot delete.\n");
}
break;
case 7:
// Exit
return 0;
default:
printf("Invalid option. Please choose a valid option.\n");
}
}

// Free dynamically allocated memory
for (int i = 0; i < n; i++) {
free(students[i].name);
}
free(students);

return 0;
}


