
#ifndef SMFLOADER_H
#define SMFLOADER_H

class SMFLoader
{
public:
	SMFLoader();
	void load(char* filename);
	void clear();
	float* getVertices();
	int* getFaces();
	float* getColors();


	float* getFace(int index);
	float* getFaceColor(int index);
	//float* getFacenormal(int index);
	float* tmp = new float[9];
	//float* tmp2 = new float[9];
	float* putin = new float[9];

	int getVertexSize();
	int getFaceSize();
	int getColorSize();
	//int getnormalSize();

private:
	float* vertex;
	int* face;
	float* color;
	//float* normal;

	int vertexSize;
	int faceSize;
	int colorSize;
	//int normalSize;
};

#endif