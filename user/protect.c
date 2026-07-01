#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Define page size if it isn't in user headers
#define PGSIZE 4096

int
main(int argc, char *argv[])
{
  printf("Starting mprotect tests...\n");

  char *raw = malloc(PGSIZE * 2);
  if (raw == 0) {
    printf("Test failed: malloc failed\n");
    exit(1);
  }

  // Align to the nearest page boundary
  char *page = (char *)(((uint64)raw + PGSIZE - 1) & ~(PGSIZE - 1));
  printf("Allocated page-aligned memory at: %p\n", page);

  // 2. Test standard read/write before protection
  printf("Step 1: Writing to normal page...\n");
  page[0] = 'A';
  if (page[0] != 'A') {
    printf("Test failed: Initial write didn't stick\n");
    exit(1);
  }
  printf("Initial write successful: value is %c\n", page[0]);

  // 3. Protect the page
  printf("Step 2: Calling mprotect...\n");
  if (mprotect(page, PGSIZE) < 0) {
    printf("Test failed: mprotect returned an error\n");
    exit(1);
  }
  printf("mprotect executed successfully.\n");

  // 4. Unprotect the page to ensure changewrite works both ways
  printf("Step 3: Calling munprotect to restore write permissions...\n");
  if (munprotect(page, PGSIZE) < 0) {
    printf("Test failed: munprotect returned an error\n");
    exit(1);
  }

  printf("Step 4: Writing after munprotect...\n");
  page[0] = 'B'; // This should succeed!
  printf("Write back allowed! value is now %c\n", page[0]);

  // 5. Re-protect the page and deliberately force a crash
  printf("Step 5: Re-protecting page to test hardware trap...\n");
  mprotect(page, PGSIZE);

  printf(
    "CRITICAL STEP: Attempting forbidden write. Program SHOULD crash with a segmentation fault now!\n");

  // THIS MUST TRIGGER YOUR USERTRAP OR COPYOUT SEGFAULT PRINT!
  page[0] = 'Z';

  // If the program reaches here, your mprotect failed to block the write!
  printf(
    "CRITICAL FAILURE: Program did not crash! mprotect bit modifications did not work.\n");
  exit(1);
}
