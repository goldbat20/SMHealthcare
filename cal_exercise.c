//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) {
    	exercise_list_size++;
        if (exercise_list_size >= MAX_EXERCISES){
        	break; // if the maximum number of exercises is exceeded, loop termination
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    //Check whether exercise history is full
    if(health_data->exercise_count >= MAX_EXERCISES){
    	printf("Exercise history is full.\n");
    	return;
	}
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    for(i=0;i<exercise_list_size;i++){
    	printf("%d. %s - Calories burned per minute : %d kcal\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}
	printf("Enter the number of the exercise you want : \n"); //
	scanf("%d", &choice);


    // ToCode: to enter the exercise to be chosen with exit option
    if(choice < 1 || choice > exercise_list_size){
    	printf("Invalid choice.\n");
    	return;
	}

 
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice-1].exercise_name);  //copy the name of the selected exercise from the exercise_list to the user's exercise record
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice-1].calories_burned_per_minute*duration;  // calculate the total calories burned for the selected exercise and store it in the user's exercise record
    
    health_data->total_calories_burned += health_data->exercises[health_data->exercise_count].calories_burned_per_minute; //update the total calories burned
    
	health_data->exercise_count++;
    printf("You selected %s.\n", health_data->exercises[choice-1].exercise_name);
    printf("Total calories burned : %d kcal.\n", health_data->total_calories_burned);
    

}
