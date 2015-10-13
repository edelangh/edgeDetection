
#ifndef __IMAGE_H__
# define __IMAGE_H__

#include <iostream>

class Image
{
public:

  static bool verbose;

  Image(const std::string& src, unsigned int width = 0, unsigned height = 0);
  Image(const Image& img);
  ~Image(void);
  Image&  operator=(const Image& img);

  void  load(const std::string& img, unsigned int width = 0, unsigned height = 0);

  unsigned int  get_width(void) const;
  unsigned int  get_height(void) const;
  std::string   get_src() const;
  char*         get_data() const;
  unsigned int  size() const;
protected:
  unsigned int  width_;
  unsigned int  height_;
  std::string   src_;
  char*         data_;
private:
};

#endif