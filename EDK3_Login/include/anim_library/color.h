/**
 * @file color.h
 * @author Luis Miguel Jiménez
 * @brief header file for the color class
 */
#ifndef _COLOR_H_
#define _COLOR_H_ 1

/**
 * @brief This class represents an RGBA Color
 * 
 */
class Color {
  public:
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
    unsigned char alpha_;

  public:
    Color();
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
    ~Color();
};

#endif