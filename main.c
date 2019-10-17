#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100 //THIS DEFINES READ LENGTH. MAXIMUM POSSIBLE NUMBER OF MARKS IS (LINE_SIZE - NAME_SIZE)/2 ~~ 45 MARKS

struct participant{
    char *name;     // Name of participant
    int sum;        // Sum of his marks
    int *marks;     // Marks array
    int mark_c;     // Number of marks (size of *marks array)
};

char *getName(const char *input, int *size_out);
int *strToInts(const char *input, int startpoint, int *size_out);
int sumOfInts(const int *input, int size);
void showMarks(struct participant temp);

int main(int argc, char * argv[]) {

    if(argc!=2){
        printf("ERROR: INCORRECT NUMBER OF PARAMETRES!\nUSE README.TXT\n");
        return 1;
    }

    int name_size = 0, marks_counter = 0;
    int *marks = NULL;
    char *current_name = NULL;
    char *buffer = malloc(LINE_SIZE*sizeof(char));

    struct participant first, second, third;
    first.sum = 0; second.sum = 0; third.sum = 0;    // Better to declare some structs then to make more loops

    FILE *inp = NULL;

    inp = fopen(argv[1], "r");

    while(fgets(buffer, LINE_SIZE*sizeof(char),inp)) {
        if (buffer[0] == '/')continue; // Strings starting with '/' will be ignored (exactly first symbol needs to be '/' NOT second or third one)

        // Getting all data

        current_name = getName(buffer, &name_size);
        marks = strToInts(buffer, name_size, &marks_counter);
        int sum = sumOfInts(marks, marks_counter); // Currents participants sum of marks

        // Time to find winners

        if(sum > first.sum){ // We have new first place
            third = second; // Good bye third one
            second = first; // Downgrading first to second

            first.name = malloc(sizeof(current_name));
            strncpy(first.name, current_name, name_size * sizeof(char));    // Adding data of new first

            first.marks = malloc(marks_counter * sizeof(int));
            memcpy(first.marks, marks, marks_counter * sizeof(int));

            first.sum = sum;
            first.mark_c = marks_counter;
        }
        else if(sum > second.sum){ // Second place
            third = second; // Making second third

            second.name = malloc(sizeof(current_name));
            strncpy(second.name, current_name, name_size * sizeof(char));

            second.marks = malloc(marks_counter * sizeof(int));
            memcpy(second.marks, marks, marks_counter * sizeof(int));

            second.sum = sum;
            second.mark_c = marks_counter;
        }
        else if (sum > third.sum){ // Third one

            third.name = malloc(name_size * sizeof(char)); // Just replacing him
            strncpy(third.name, current_name, name_size * sizeof(char));

            third.marks = malloc(marks_counter * sizeof(int));
            memcpy(third.marks, marks, marks_counter * sizeof(int));

            third.sum = sum;
            third.mark_c = marks_counter;
        }
        free(marks); free(current_name);
    }

    // Congratz!!!
    printf("-----------------------------------------------------------------------\n");
    printf("Congratulating %s with first place!\nPoints: %d\nCongratulating %s with second place!\nPoints: %d\n"
                  "Congratulating %s with third place!\nPoints: %d\n",
                  first.name, first.sum, second.name, second.sum,third.name,third.sum);
    printf("-----------------------------------------------------------------------\n");
    char k_switch = 0;
    printf("Do you want to see list of winner's marks? (Y/N)");
    scanf("%c", &k_switch);
    if(k_switch == 'Y'||k_switch == 'y'){
        printf("%s: ", first.name); showMarks(first);
        printf("%s: ", second.name); showMarks(second);
        printf("%s: ", third.name); showMarks(third);
        printf("-----------------------------------------------------------------------\n");
    }

    free(first.name);   free(second.name);   free(third.name);
    free(buffer);
    return 0;

}

//------------------------------------------------------------------------------

char *getName(const char *input, int *size_out){  // Starting from 0 we copy each element until we hit ' ' (space)
    char *temp = malloc(sizeof(char));
    int size = 0;
    for(int i = 0; input[i]!=' '&&input[i]!='\0';i++){
        size++;
        temp = realloc(temp, size * sizeof(char));
        temp[size-1] = input[i];
    }
    *size_out = size;
    return temp;
}

//------------------------------------------------------------------------------

int *strToInts(const char *input, int startpoint, int *size_out){   // Starting from int startpoint we check every element if it is digit or spliting element
    startpoint++;
    int counter = 1;
    int *output = malloc(sizeof(int)); output[0] = 0;
    for(int i = startpoint; input[i]!='\0'; i++){
        if(input[i]==','||input[i]==' '){  // ',' and ' ' are spliting elements. We can add some new right here <-
            counter++;
            output = realloc(output, counter * sizeof(int));
            output[counter-1]=0;
        }
        else if(input[i]>='0'&&input[i]<='9')output[counter-1] = output[counter-1] * 10 + (input[i] - 48);
    }
    *size_out = counter;
    return output;
}

//------------------------------------------------------------------------------

int sumOfInts(const int *input, int size){ // Just sum of integers in array, nothing interesting
    int sum_t = 0;
    for(int i = 0; i < size; i++){
        sum_t+=input[i];
    }
    return sum_t;
}

//------------------------------------------------------------------------------

void showMarks(struct participant temp){ // Just show marks of a struct
    for(int i = 0; i < temp.mark_c; i++){
        printf("%d ", temp.marks[i]);
    }
    printf("\n");
}

//------------------------------------------------------------------------------

