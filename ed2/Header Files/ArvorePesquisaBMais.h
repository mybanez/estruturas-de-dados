#ifdef _struct_PESQ_BMAIS

#define ORDEM 5

struct no {
  int nfilhos;
  int chaves[ORDEM-1];
  No * filhos[ORDEM];
  No * prox_folha;
};

#endif