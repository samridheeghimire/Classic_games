#include <stdio.h>
#include <string.h>

int pacman_data_sorter()
{
    FILE *fptr, *temp;
    fptr = fopen("userdata_pacman.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (fptr == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    int points, temp_points;
    char temp_username[30], username[30], password[30], temp_pass[30];

    while (fscanf(fptr, "%s %s %d", username, password, &points) != EOF)
    {
        // Reset the copied flag
        int copied = 0; // false

        // Reset the file pointer to the beginning of the temporary file
        fseek(temp, 0, SEEK_SET);

        while (fscanf(temp, "%s %s %d", temp_username, temp_pass, &temp_points) != EOF)
        {
            if (strcmp(temp_username, username) == 0)
            {
                // Update points if higher
                if (points > temp_points)
                {
                    // Write the updated data to the temporary file
                    fprintf(temp, "%s %s %d\n", username, password, points);
                }
                else
                {
                    // Write the existing data back to the temporary file
                    fprintf(temp, "%s %s %d\n", temp_username, temp_pass, temp_points);
                }

                // Set the copied flag
                copied = 1;

                break;
            }
        }

        // If the username was not found in the temporary file, write the data from the original file
        if (!copied)
        {
            fprintf(temp, "%s %s %d\n", username, password, points);
        }
    }

    fclose(fptr);
    fclose(temp);

    // Replace the original file with the temporary file
    remove("userdata_pacman.txt");
    rename("temp.txt", "userdata_pacman.txt");

    return 0;
}
