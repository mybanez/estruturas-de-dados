#ifdef _struct_PESQ_AVL

#define FB_INDEF 99
#define INS_ESQ 0
#define INS_DIR 1
#define REM_ESQ 2
#define REM_DIR 3

struct no {
	int inf;
	int fb;
	No * esq;
	No * dir;
#ifdef ARVORE_INFO_EXT
	Info * inf_ext;
#endif
};

#endif