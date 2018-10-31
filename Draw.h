#ifndef draw___
#define draw___

#define DllImport __declspec(dllimport)

typedef struct
{
	float position[4];
	float direction[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float cutOff;
	float exponent;
}LIGHT;

#ifdef __cplusplus
extern "C" {
#endif

DllImport void drawTable();
DllImport int initializeTable();
DllImport void finalizeTable();

DllImport void drawLight(GLfloat Length, GLfloat Width, GLfloat Height, GLfloat Deep);

DllImport void drawLamp(GLfloat Length, GLfloat Height, GLfloat Deep, GLfloat WireLength);

DllImport void setLight(LIGHT spotLight);

DllImport void setScene(void);

DllImport void setGround(GLfloat Red, GLfloat Green, GLfloat Blue);

DllImport void setDefaultLight(LIGHT *light);

DllImport void castBallShadow(float ballPosition[3], float lightPosition[3], float radius);

DllImport void drawTableShadow(double lightPosition[], double surface[4]);

#ifdef __cplusplus
}
#endif

#endif
