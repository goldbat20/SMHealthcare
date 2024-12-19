//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2) {
    	diet_list_size++;
        if (diet_list_size >= MAX_DIETS){
        	break;  // if the maximun number of diets is exceed, loop termination
		}
			
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    //Check whether diet history is full
    if(health_data->diet_count >= MAX_DIETS){
    	printf("Diet history is full.\n");
    	return;
	}
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    FILE *file = fopen("diet.txt", "r");
    if (file == NULL){
    	printf("There is no file for diets!\n");
    	return;
	}
	for(i=0;i<health_data->diet_count;i++){
		printf("%d. %s - %d kcal\n", i+1, health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}
    
	// ToCode: to enter the diet to be chosen with exit option
	printf("Choose the diet you want to eat : \n");
	scanf("%d", &choice);
	
	if (choice<1 || choice>diet_list_size){
		printf("Invalid choice.\n");
		return;
	}

    // ToCode: to enter the selected diet in the health data
    printf("You selected %s.\n", health_data->diet[choice-1].food_name);
    
    // ToCode: to enter the total calories intake in the health data
	strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice-1].food_name);  // copy the name of the selected diet from the diet_list to the user's exercise record
	health_data->diet_count++;
	printf("Total calories intake : %d kcal.\n", health_data->total_calories_intake);

}

