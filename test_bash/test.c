#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main()
{
    FILE *fp;
    struct dirent *dirst;
    struct stat buf;

    mkdir("test_dir_01", 0755);
    printf("stat()実行 : %d\n\n", stat("test_dir_01", &buf));
    printf("ディレクトリ[test_dir_01]に関する情報\n");
    printf("    st_mode : %#o\n", buf.st_mode);
    printf("    st_uid  : %ld\n", (long)buf.st_uid);
    printf("    st_gid  : %ld\n", (long)buf.st_gid);
    printf("    st_size : %ld\n", (long)buf.st_size);
    
    fp = fopen("test_dir_01/test_file_01.txt", "w");
    fclose(fp);
	chmod("test_dir_01/test_file_01.txt", 0755);     //test_file_01.txtは実行権限があるファイル
    fp = fopen("test_dir_01/test_file_02.txt", "w");
    fclose(fp);
	chmod("test_dir_01/test_file_02.txt", 0644);     //test_file_02.txtは実行権限がないファイル

    DIR *dp = opendir("test_dir_01");
    while((dirst = readdir(dp)) != NULL)
    {
        if ((strcmp(dirst->d_name, ".") != 0) & (strcmp(dirst->d_name, "..") != 0))
        {
            char s_file[100] = "test_dir_01/";
            strcat(s_file, dirst->d_name);
            stat(s_file, &buf);
            printf("ファイル[%s]に関する情報\n", s_file);
			//buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)は、ファイルに実行権限があると0以外が、ないと0になる
            printf("    st_mode : %#o\n", buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH));
            printf("    st_uid  : %ld\n", (long)buf.st_uid);
            printf("    st_gid  : %ld\n", (long)buf.st_gid);
            printf("    st_size : %ld\n", (long)buf.st_size);
        }
    }
    closedir(dp);

    remove("test_dir_01/test_file_01.txt");
    remove("test_dir_01/test_file_02.txt");
    remove("test_dir_01");

    return 0;
}