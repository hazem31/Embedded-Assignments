

#ifndef STATE_H_
#define STATE_H_



#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_) ST_##_statFUN_

//connections

void PressureVal(int p);
void SetTimer(int t);

#endif /* STATE_H_ */