#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  // needed vars
  struct utsname os;
  uname(&os);
  char *user = getlogin();
  if(!user) {user = "uknown";}
  char *shell = getenv("SHELL");

  // Getting the OS
  char line[60];
  FILE* osfile = fopen("/etc/os-release", "r");
  fgets(line, 60, osfile);
  if(strstr(line, "PRETTY_NAME")) {
    strcpy(line, line + 13);
    strtok(line, "\"");
  } else {
    strcpy(line, line + 6); // Removing NAME="
    strtok(line, "\""); // Removing the last quote
  }
  fclose(osfile);

  // Getting the WM
  FILE *fp;
  char wm[25];

  fp = popen("ps -e | grep -m 1 -o -e '[s]owm' -e '[c]atwm' -e '[f]vwm' -e '[d]wm' -e '[2]bwm' -e '[m]onsterwm' -e '[t]inywm' -e '[x]11fs' -e '[x]monad'", "r");
  fgets(wm, sizeof(wm), fp);
  sscanf(wm, "Name: %s", wm);
  strcat(wm, "\n");
  if(WEXITSTATUS(pclose(fp)) != 0){ strcpy(wm, "TTY\n"); }
  // Printing.
  printf("            %s@%s\n", user, os.nodename);
  printf("  (\\_/)     os ~ %s\n", line);
  if(shell !=NULL){
    char *p = strrchr(shell, '/');
    printf("__(. .)__   sh ~ %s\n", p + 1);
  } else { // Fallback
    shell = getusershell();
    char *p = strrchr(shell, '/');
    printf("__(. .)__   sh ~ %s\n", p + 1);
  }
  printf("\\__|_|__/   wm ~ %s", wm);
  printf("   / \\ ");
  printf("     \033[31m● \033[33m● \033[36m● \033[34m●\033[0m\n\n");
}
