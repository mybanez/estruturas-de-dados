#ifdef _struct_BIN_PESQ

struct no {
	int inf;
	No * pai;
	No * esq;
	No * dir;
#ifdef ARVORE_INFO_EXT
	Info * inf_ext;
#endif
};

#endif