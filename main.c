#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


int main() {
	//INITIALISING THE DIRECTORY
	DIR *dir;
	dir = opendir("./songs/hindi");

	struct dirent *entry;
	
	
	if(dir == NULL) {
		printf("Error opening directory\n");
		return 1;
	}

	int count = 0;

	char **songs = NULL;

	//MAIN LOOP TO WORK WITH DIRECTORY
	while((entry = readdir(dir)) != NULL){

		

		// GPT TOLD ME
		if (strcmp(entry->d_name, ".") == 0 ||
		strcmp(entry->d_name, "..") == 0) {
			continue;
		}


		count++;
		songs = realloc(songs, count * sizeof(char *));
		songs[count - 1] = strdup(entry->d_name); 
		// AI TOLD ME TO DO THIS I NEED TO SEE WHAT THIS DOES
	}


	//PRINTS ALL THE SONGS IN THE DIRECTORY
	// for (int i = 2; i < count; i++){		
	// 	printf("%s \n", songs[i]);
	// }


	//PLAYS THE PLAYLIST
	for(int i=3;i<count; i++){
		//AGAIN AI TOLD ME and temporary code beacause bad practice to use system()
		char cmd[512];
		snprintf(cmd, sizeof(cmd),"mpv --no-video \"./songs/hindi/%s\"",songs[i]);	
		
		system(cmd);
	}

}

// LEARN POINTERS PROPERLY PLEASE 