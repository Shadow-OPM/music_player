#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <sys/wait.h>

GtkWidget *song_label;

void show_window() {
    gtk_init(NULL, NULL);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Music Player");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    song_label = gtk_label_new("Loading...");
    gtk_container_add(GTK_CONTAINER(window), song_label);
    gtk_widget_show_all(window);
}

void wait_and_update() {
    // keeps GTK alive while waiting
    while (gtk_events_pending()) gtk_main_iteration();
}

int main() {
    printf("Enter the name of the playlist: ");
    char playlist_name[256];
    char dir_path[512];
    scanf("%s", playlist_name);
    snprintf(dir_path, sizeof(dir_path), "./songs/%s", playlist_name);

    DIR *dir = opendir(dir_path);
    struct dirent *entry;

    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    int count = 0;
    char **songs = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) continue;
        count++;
        songs = realloc(songs, count * sizeof(char *));
        songs[count - 1] = strdup(entry->d_name);
    }
    closedir(dir);

    show_window();
    wait_and_update();  // let window render first

   for (int i = 0; i < count; i++) {
    gtk_label_set_text(GTK_LABEL(song_label), songs[i]);
    wait_and_update();

    // build path BEFORE fork
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "./songs/%s/%s", playlist_name, songs[i]);

    pid_t pid = fork();
    if (pid == 0) {
        // child: play song
        execlp("mpv", "mpv", "--no-video", "--really-quiet", full_path, NULL);
        exit(0);
    } else {
        // parent: wait for mpv
        int status;
        while (waitpid(pid, &status, WNOHANG) == 0) {
            wait_and_update();
            usleep(100000);
        }
    }

    // 5 second gap
    gtk_label_set_text(GTK_LABEL(song_label), "Waiting...");
    for (int s = 0; s < 50; s++) {
        wait_and_update();
        usleep(100000);
    }
}

gtk_label_set_text(GTK_LABEL(song_label), "Playlist finished!");
    gtk_main();
    return 0;
}