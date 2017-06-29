void bicie(int end_x, int end_y, int gracz_aktywny);
int sprawdz_bicie_lewo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_prawo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_gora(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_dol(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
void zbij(int zbity_x, int zbity_y);

extern char plansza[12][12];
