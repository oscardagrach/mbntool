#define IMG_MAX	26
#define MBN_HEADER_LEN	0x28
#define HW_ID_OFFSET	0x235
#define ELF_IMAGE	0x464C457F
#define SBL_IMAGE	0x844BDCD1

struct sbl_header {
	uint32_t offset;
	char* name;
};

struct mbn_header {
	uint32_t offset;
	char* name;
};

struct mbn_type {
	uint32_t image_id;
	char* image;
	char* name;
};

static struct sbl_header sbl[] = {
	{ 0, "Codeword" },
	{ 4, "Magic" },
	{ 8, "Image ID" },
	{ 20, "Header size" },
	{ 24, "Load address" },
	{ 28, "Image size" },
	{ 32, "Code size" },
	{ 36, "Signature pointer" },
	{ 40, "Signature size" },
	{ 44, "Certificate chain pointer" },
	{ 48, "Certificate chain size" },
	{ 52, "OEM Root Certificate Select" },
	{ 56, "OEM Root Certificates" }
};

static struct mbn_header mbn[] = {
	{ 0, "Image ID" },
	{ 4, "Flash Partition Version" },
	{ 8, "Image source" },
	{ 12, "Load address" },
	{ 16, "Image size" },
	{ 20, "Code size" },
	{ 24, "Signature pointer" },
	{ 28, "Signature size" },
	{ 32, "Certificate chain pointer" },
	{ 36, "Certificate chain size" }
}; 
	
static struct mbn_type type[] = {
	{ 0, "NONE_IMG", "No image" },
	{ 1, "OEM_SBL_IMG", "OEM SBL image" },
	{ 2, "AMSS_IMG", "AMSS image" },
	{ 3, "QCSBL_IMG", "Qualcomm SBL image" },
	{ 4, "HASH_IMG", "Hash image" },
	{ 5, "APPSBL_IMG", "ABOOT/Apps Bootloader image" },
	{ 6, "APPS_IMG", "Apps image" },
	{ 7, "HOSTDL_IMG", "Host DLOAD image" },
	{ 8, "DSP1_IMG", "DSP1 image" },
	{ 9, "FSBL_IMG", "FSBL image" },
	{ 10, "DBL_IMG", "DBL image" },
	{ 11, "OSBL_IMG", "OSBL image" },
	{ 12, "DSP2_IMG", "DSP2 image" },
	{ 13, "EHOSTDL_IMG", "Emergency Host DLOAD image" },
	{ 14, "NANDPRG_IMG", "NAND Programmer image" },
	{ 15, "NORPRG_IMG", "NOR Programmer image" },
	{ 16, "RAMFS1_IMG", "RAM Filesystem 1 image" },
	{ 17, "RAMFS2_IMG", "RAM Filesystem 2 image" },
	{ 18, "ADSP_Q5_IMG", "ADSP Q5 Hexagon image" },
	{ 19, "APPS_KERNEL_IMG", "Apps Kernel image" },
	{ 20, "BACKUP_RAMFS_IMG", "Backup RAM Filesystem image" },
	{ 21, "SBL1_IMG", "First stage Secondary Bootloader image" },
	{ 22, "SBL2_IMG", "Second stage Secondary Bootloader image" },
	{ 23, "RPM_IMG", "Resource and Power Management image" },
	{ 24, "SBL3_IMG", "Third stage Secondary Bootloader image" },
	{ 25, "TZ_IMG", "TrustZone image" }
};
