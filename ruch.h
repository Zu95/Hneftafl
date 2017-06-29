int ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y);
void wczytaj_ruch(int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y);
int sprawdz_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y);
int wykonaj_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y);
int tonumber(char character);

extern char plansza[12][12];
