#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

void __attribute__((section(".upx"))) hello_world()
{
  system("reboot");
}

extern char upx_end;
extern char upx_start;
int main(int argc, char *argv[])
{
  int page_size = sysconf(_SC_PAGE_SIZE);
  printf("page size: %d\n", page_size);
  printf("start = %p , end = %p\n", &upx_start, &upx_end); 
  void *ptr;
  ptr = &upx_start;
  ptr -= ((off_t)ptr) & (page_size - 1);
  if ((-1) == mprotect((void*)ptr , page_size , PROT_WRITE|PROT_EXEC)) {
    perror("mprotect");
    exit(-1);
  }
  unsigned char xorBytes[] = {0xFA, 0xA8, 0x52, 0x01, 0xBB};
  for (size_t i = 0; i < upx_start - upx_end; i++)
  {
    (&upx_start)[i] ^= xorBytes[i % sizeof(xorBytes)];;
  }
  
  
  hello_world();
	
  return 0;
}
