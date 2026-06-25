#include <stdio.h>
#include <dirent.h>

int main() {
	DIR *dir;
	dir = opendir("./songs/hindi");

	struct dirent *entry;
	
	if(dir == NULL) {
		printf("Error opening directory\n");
		return 1;
	}

	char songs[][256] = {"song1.mp3", "song2.mp3", "song3.mp3"};

	printf("%s", songs[0]);
	// while((entry = readdir(dir)) != NULL){
	// 	printf("%s\n", entry->d_name);
	// }

}
