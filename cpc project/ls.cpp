#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[11];

    snprintf(perms, sizeof(perms), "%c%c%c%c%c%c%c%c%c%c",
             S_ISDIR(mode) ? 'd' : '-',
             mode & S_IRUSR ? 'r' : '-',
             mode & S_IWUSR ? 'w' : '-',
             mode & S_IXUSR ? 'x' : '-',
             mode & S_IRGRP ? 'r' : '-',
             mode & S_IWGRP ? 'w' : '-',
             mode & S_IXGRP ? 'x' : '-',
             mode & S_IROTH ? 'r' : '-',
             mode & S_IWOTH ? 'w' : '-',
             mode & S_IXOTH ? 'x' : '-');

    printf("%s ", perms);
}

void listdir(const char *name, int indent) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];

            if (entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || (entry->d_name[1] == '.' && entry->d_name[2] == '\0')))
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);

            listdir(path, indent + 2);
        } else {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            stat(path, &fileStat);

            pw = getpwuid(fileStat.st_uid);
            gr = getgrgid(fileStat.st_gid);

            print_permissions(fileStat.st_mode);
            printf("%s %s ", pw->pw_name, gr->gr_name);
            printf("%ld ", fileStat.st_size);
            printf("%s", ctime(&fileStat.st_mtime));
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(void) {
    // listdir(".", 0);
    listdir("/etc", 0);
    return 0;
}