#ifdef _struct_PESQ_RB

struct no {
	int inf;
	int cor;
    No * pai; 
	No * esq;
	No * dir;
#ifdef ARVORE_INFO_EXT
	Info * inf_ext;
#endif
};

#endif
