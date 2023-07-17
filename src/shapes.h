#ifndef __SHAPESH__
#define __SHAPESH__

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <string>
#include <vector>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "tiny_obj_loader.h"

using namespace std;

class MaterialC
{
public:
	void SetKa(glm::vec3 amb) {ka=amb;}
	void SetKd(glm::vec3 diff){kd=diff;}
	void SetKs(glm::vec3 spec){ks=spec;}
	void SetSh(float sh){this->sh=sh;}
	virtual void SetKaToShader(GLuint uniform){kaParameter=uniform;}
	virtual void SetKdToShader(GLuint uniform){kdParameter=uniform;};
	virtual void SetKsToShader(GLuint uniform){ksParameter=uniform;};
	virtual void SetShToShader(GLuint uniform){shParameter=uniform;};

protected:
	glm::vec3 ka; //ambient
	glm::vec3 kd; //diffuse
	glm::vec3 ks; //specular
	float sh;	  //shineness
    GLuint	 kaParameter;	 //shader uniform variables
    GLuint	 kdParameter;	 
    GLuint	 ksParameter;	 
    GLuint	 shParameter;	 
};

//Base class for shapes
class ShapesC: public MaterialC
{
public:
	virtual void SetModelMatrixParamToShader(GLuint uniform);
	virtual void SetModelViewNMatrixParamToShader(GLuint uniform);
	virtual void SetModel(glm::mat4 tmp);
	virtual void SetModelViewN(glm::mat3 tmp); //3x3 matrix!
	virtual void SetColor(GLubyte r,GLubyte b,GLubyte g);
	virtual void Render();
	GLuint vaID;

protected:
  GLuint	 modelParameter;	 //shader uniform variables
  GLuint	 modelViewNParameter;	 
  glm::mat4  model;				 //modeling matrix
  glm::mat3  modelViewN;		 //model view normals matrix
  GLubyte    color[3];
  vector <GLfloat> *a;
  vector <GLfloat> vertex;
  vector <GLfloat> normal;
  GLuint vboHandles[2]; //vertices and normals
  GLuint buffer;
  GLuint points;
  GLuint normals;
};

class Cone : public ShapesC {
public:
	Cone();
	virtual void Render();
private:
	GLfloat rd, h;
	GLuint n;
	void Cone::Generate(glm::vec3 d, glm::vec3 a,
		float h, float rd, int n);
	void InitArrays();
};

//derived class from ShapesC
class SphereC: public ShapesC
{
public:
	SphereC();
	SphereC(int stacks, int slices, GLfloat r);
	virtual void Render();		

private:
	GLuint stacks, slices;
	GLfloat r;
	void SphereC::Generate(int stacks, int slices, GLfloat r);
    void InitArrays();
    void Generate();
};

//derived class from ShapesC
class CubeC: public ShapesC
{
public:
	CubeC();
	virtual void Render();		
private:
  void InitArrays();
  void Generate();
};


class ModelC : public ShapesC {
public:
	ModelC(string file);
	virtual void Render();
private:
	tinyobj::ObjReader reader;
	void InitArrays();
	void Generate(string file);
};


#endif