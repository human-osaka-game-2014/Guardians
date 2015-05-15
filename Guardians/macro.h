#ifndef _MACRO_H_
#define _MACRO_H_

#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(x) if(x) { delete[] x; x = NULL; }
//四捨五入用
#define ROUND_OFF(x) static_cast<float>(int(x + 0.5f)); 
// 技補正値用(float乱数)
#define RAND_FLOAT(LO, HI) LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
// 円周率
#define PI 3.141592653589793
// 度からラジアンに変換
#define DegreesToRadian(d) (d) * (PI / 180); 

#endif
