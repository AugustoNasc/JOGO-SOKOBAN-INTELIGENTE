#ifndef GUARDA_NIVEL_HPP
#define GUARDA_NIVEL_HPP

void salvar_nivel(int);

int ultimo_nivel_desbloqueado(void);

bool verifica_nivel_desbloqueado(int level);
bool ha_jogo_salvo();

void atualiza_mapas_acessados(bool []);

#endif