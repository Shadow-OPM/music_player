#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>


int main() {

	//GETS THE PLAYLIST NAME FROM THE USER
	printf("Enter the name of the playlist: ");
	char playlist_name[256];
	char dir_path[512];
	scanf("%s", playlist_name);
	snprintf(dir_path, sizeof(dir_path), "./songs/%s", playlist_name);

	// printf("%s",dir_path);

	
	//INITIALISING THE DIRECTORY
	DIR *dir;
	dir = opendir(dir_path);

	struct dirent *entry;
	
	
	if(dir == NULL) {
		printf("Error opening directory\n");
		return 1;
	}

	int count = 0;

	char **songs = NULL;

	//ITERATING THROUGH THE ELEMENTS IN THE DIRECTORY
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


	// char cmd[512];
	// snprintf(cmd, sizeof(cmd),"mpv --no-video \"./songs/idk/%s\"",songs[3]);	
	// printf("%s",cmd);

	// PLAYS THE PLAYLIST
	for(int i=0;i<count; i++){
		//AGAIN AI TOLD ME and temporary code beacause bad practice to use system()
		char cmd[512];
		snprintf(cmd, sizeof(cmd),"mpv --no-video \"./songs/%s/%s\"",playlist_name,songs[i]);	
		
		system(cmd);
	


	printf("Waiting 5 seconds...\n");
    sleep(5);
	}         // Pause for 5 seconds before the next song
}
// LEARN POINTERS PROPERLY PLEASE 
