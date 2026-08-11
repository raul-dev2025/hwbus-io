#include  "tst_test.h"

static int fd = -1;
static char *addr;
static size_t page_sz;

/* Asignación de recursos, apertura de FDs */
static void setup(void) {
  page_sz = getpagesize();
  fd = SAFE_OPEN("testfile", O_RDWR | O_CREAT, 0666);
  SAFE_FTRUNCATE(fd, page_sz);
}

/* Liberación de FDs, desmapeo de memoria */
static void cleanup(void) {
  if (addr && addr != MAP_FAILED)
    SAFE_MUNMAP(addr, page_sz);

  if (fd > 0)
    SAFE_CLOSE(fd);
}

/* 3. Lógica principal de la prueba */
static void run(unsigned int i) {
  addr = mmap(NULL, page_sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (addr == MAP_FAILED){
    tst_res(TFAIL | TERRNO, "mmap() fallo inesperadamente");
    return;
  }

  addr[0] = 'A';

  if (addr[0] == 'A') {
    tst_res(TPASS, "mmap() funciono y la memoria es accesible");  
  }

  else {
    tst_res(TFAIL, "Los datos escritos en la memoria mapeada no coinciden");    
  }
}

static struct tst_test test = {
  //.test_variants = 1,
  .tcnt = 1,
  .setup = setup,
  .cleanup = cleanup,
  .test = run,
  .needs_tmpdir = 1,
};