#include <stdio.h>

int main() {
  int grp_num = 1;
  const char *full_name = "Nikita Kliatskyi";
  const char *email = "nikitakliatskyi@gmail.com";
  const char *repo_link =
      "https://github.com/nikitakliatskyi/gl_embedded_tasks";
  const char *folder_link = "https://drive.google.com/drive/u/0/folders/"
                            "1FLC5xR5qWh6Gvv0KEkOKksEONlrEbbE8";
  printf("Group number: %d\n"
         "Full name: %s\n"
         "Email: %s\n"
         "Repository link: %s\n"
         "Folder link: %s\n",
         grp_num, full_name, email, repo_link, folder_link);
  return 0;
}
