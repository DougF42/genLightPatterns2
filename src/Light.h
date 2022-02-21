/**
 * This defines a class for illuminating a picture.
 */
#ifndef L_I_G_H_T__H
#define L_I_G_H_T__H
#include <stdio.h>
#include <string>

 /*
  * For each element in a group of lights, indicate the position (x,y)
  * and relative brightness.
  *
  * This class has a 'next' pointer, allowing it to be part of a
  * singly linked list.
  */
  class Light
{
  public:
    Light(int r, int c, int _rgb=255);
    ~Light();

    int row;
    int col;
    unsigned int rgb;
    Light *next;
};



/**
 * This is a Singly linked list implementation, ordered.
 *
 * It takes a light, and adds it to itself.
 * it also provides for iterating thru the list
 */
class LightGroup
{

private:
  Light *first;
  Light *last;
  int len;
  std::string listName;
  int noOfRows;
  int noOfCols;
  size_t noOfLeds;

public:
  LightGroup(std::string lname, int _rowCount, int _colCount);
  ~LightGroup();
  /**
   * Define a new 'light', and add it to this list
   */
   void pushRGB(int row, uint8_t col, uint8_t r, uint8_t g, uint8_t b);
   void generate(FILE *outfile);
   void generate2(const char *outfile);

   inline int getRows()  { return(noOfRows); }
   inline int getCols()  { return(noOfCols); }
   inline const char *getName() { return(listName.c_str()); }
   inline size_t getNoOfLeds()  { return(noOfLeds); }
};

#endif
