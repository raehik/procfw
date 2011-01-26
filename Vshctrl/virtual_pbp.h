#ifndef VIRTUAL_PBP
#define VIRTUAL_PBP

typedef struct _PBPSection {
	u32 lba;
	u32 size;
} PBPSection;

typedef struct _VirtualPBP {
	u32 enabled;
	u32 total_size;
	u32 file_pointer;
	char name[128];
	u32 header[10];
	PBPSection sects[8];
	ScePspDateTime mtime;
} VirtualPBP;

#define CACHE_MAX_SIZE 32
#define MAGIC_ISOCACHE 0xC01DB15D
#define MAGIC_VPBP_FD 0x8000
#define MAX_VPBP 128
#define PTR_ALIGN_64(p) ((void*)((((u32)p)+64-1)&(~(64-1))))
#define ISOEBOOT(file) (strlen(file) == 39 && strncmp(file + 14, "ISOGAME", 7) == 0 && strcmp(file + strlen(file) - 9, "EBOOT.PBP") == 0)

#define PSP_CACHE_PATH "ms0:/PSP/SYSTEM/ISOCACHE.BIN"
#define PSPGO_CACHE_PATH "ef0:/PSP/SYSTEM/ISOCACHE.BIN"

int vpbp_init(void);
SceUID vpbp_open(const char * file, int flags, SceMode mode);
SceOff vpbp_lseek(SceUID fd, SceOff offset, int whence);
int vpbp_read(SceUID fd, void * data, SceSize size);
int vpbp_close(SceUID fd);
int vpbp_disable_all_caches(void);
int vpbp_remove(const char * file);
int vpbp_getstat(const char * file, SceIoStat * stat);
int vpbp_is_fd(SceUID fd);
int vpbp_loadexec(char * file, struct SceKernelLoadExecVSHParam * param);
SceUID vpbp_dopen(const char * dirname);
int vpbp_dread(SceUID fd, SceIoDirent * dir);
int vpbp_dclose(SceUID fd);
int vpbp_reset(void);

#endif
