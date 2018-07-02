#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <alsa/asoundlib.h>

// In branch - test uploading

static void getALSADevices(int *count, char **devices)
{ 
  void **hints;
  const char *ifaces[] = {"card", "pcm", "rawmidi", "timer", "seq", "hwdep", 0}; 
  int index = 0; 
  void **str;
  char *name;
  char *desc;
  char *io; 
  char *name_tmp;
  char *desc_tmp;
  int devIdx = 0;
  int len; 
  snd_config_update();
  while (ifaces[index]) {
    printf(" --- Trying interface %s ---\n", ifaces[index]);
    if (snd_device_name_hint(-1, ifaces[index], &hints) < 0) {
      printf("Querying devices failed for %s.\n", ifaces[index]);
      index++; 
      continue; 
    }
    str = hints; 
    while (*str) { 
      name = snd_device_name_get_hint(*str,"NAME");
      desc = snd_device_name_get_hint(*str, "DESC");
      io = snd_device_name_get_hint(*str, "IOID");
      len = strlen(name)+1;
      name_tmp = (char*)malloc(len);
      devices[devIdx] = name_tmp;
      strcpy(name_tmp, name);
      devices[devIdx][len-1] = '\0';
      printf("\n-- %s --\n", name);
      printf("IO: %s\n", io); 
      desc_tmp = strtok(desc, "\n");
      while (desc_tmp != NULL) {
        printf("%s\n", desc_tmp);
        desc_tmp = strtok(NULL, "\n");
      } 
      free(name); 
      free(desc); 
      devIdx++;
      str++;
    } 
    index++; 
    snd_device_name_free_hint(hints); 
  }
  *count = devIdx;
  return;
}

int main()
{
  int count;
  char* devs[128];
  getALSADevices(&count,devs);
  return 0;
}
